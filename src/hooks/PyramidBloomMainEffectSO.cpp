#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/PyramidBloomMainEffectSO.hpp"
#include "GlobalNamespace/PyramidBloomRendererSO.hpp"
#include "GlobalNamespace/PyramidBloomRendererSO_Pass.hpp"
#include "UnityEngine/Graphics.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Rendering/TextureDimension.hpp"
#include "UnityEngine/RenderTexture.hpp"
#include "UnityEngine/Shader.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace UnityEngine::Rendering;

Matrix4x4 GetGPUProjectionMatrix(Matrix4x4 proj, bool renderIntoTexture) {
    static auto GetGPUProjectionMatrix_Injected = reinterpret_cast<function_ptr_t<void, ByRef<Matrix4x4>, bool, ByRef<Matrix4x4>>>(il2cpp_functions::resolve_icall("UnityEngine.GL::GetGPUProjectionMatrix_Injected"));

    Matrix4x4 result;
    GetGPUProjectionMatrix_Injected(proj, renderIntoTexture, result);
    return result;
}

MAKE_HOOK_MATCH(
    PyramidBloomMainEffectSO_Render,
    &PyramidBloomMainEffectSO::Render,
    void,
    PyramidBloomMainEffectSO* self,
    RenderTexture* src,
    RenderTexture* dest,
    float fade
) {
    static auto CopyTexture_Region = reinterpret_cast<function_ptr_t<void, UnityEngine::Texture*, int, int, int, int, int, int, UnityEngine::Texture*, int, int, int, int>>(il2cpp_functions::resolve_icall("UnityEngine.Graphics::CopyTexture_Region"));
    
    // Describe the double wide texture
    RenderTextureDescriptor doubleWideDesc = src->get_descriptor();
    doubleWideDesc.dimension = TextureDimension::Tex2D;
    doubleWideDesc.vrUsage = VRTextureUsage::OneEye;
    doubleWideDesc.width *= 2;

    RenderTexture* doubleWideSrc = RenderTexture::GetTemporary(doubleWideDesc);
    CopyTexture_Region(src, 0, 0, 0, 0, src->get_width(), src->get_height(), doubleWideSrc, 0, 0, 0, 0); // Copy left eye
    CopyTexture_Region(src, 1, 0, 0, 0, src->get_width(), src->get_height(), doubleWideSrc, 0, 0, src->get_width(), 0); // Copy right eye

    RenderTexture* doubleWideDst = RenderTexture::GetTemporary(doubleWideDesc);

    self->LazyInitializeMaterials();

    int width = self->bloomTextureWidth * ((doubleWideSrc->get_vrUsage() == VRTextureUsage::TwoEyes) ? 2 : 1);
    int height = (int)((float)(self->bloomTextureWidth * doubleWideSrc->get_height()) / (float)doubleWideSrc->get_width()) * ((doubleWideSrc->get_vrUsage() == VRTextureUsage::TwoEyes) ? 2 : 1);

    RenderTexture* temporary = RenderTexture::GetTemporary(width, height, 0, RenderTextureFormat::RGB111110Float, RenderTextureReadWrite::Linear);

    // Fix our projection matrix.
    Matrix4x4 projectionMatrix = GetGPUProjectionMatrix(Matrix4x4::Ortho(0, 1, 0, 1, -1, 100), true);
    Shader::SetGlobalMatrix(il2cpp_utils::newcsstr("unity_StereoMatrixVP"), projectionMatrix);

    self->bloomRenderer->RenderBloom(doubleWideSrc, temporary, self->bloomRadius, self->bloomIntensity, self->downBloomIntensityOffset, false, false, self->pyramidWeightsParam, self->alphaWeights, 1.0f, 1.0f, self->preFilterPass, self->downsamplePass, self->upsamplePass, self->finalUpsamplePass);

    self->mainEffectMaterial->SetFloat(PyramidBloomMainEffectSO::_get__bloomIntensityID(), self->bloomBlendFactor);
    self->mainEffectMaterial->SetTexture(PyramidBloomMainEffectSO::_get__bloomTexID(), temporary);

    Graphics::Blit(doubleWideSrc, doubleWideDst, self->mainEffectMaterial, 0);

    RenderTexture::ReleaseTemporary(temporary);

    if (fade < 0.99f)
    {
        self->fadeMaterial->set_color(Color(0, 0, 0, 1 - fade));

        Graphics::Blit(nullptr, doubleWideDst, self->fadeMaterial);
    }

    // Now our doubleWideDst has had the bloom applied to it, so now we need to copy it into the dst texture array.
    CopyTexture_Region(doubleWideDst, 0, 0, 0, 0, src->get_width(), src->get_height(), dest, 0, 0, 0, 0); // Copy left eye
    CopyTexture_Region(doubleWideDst, 0, 0, src->get_width(), 0, src->get_width(), src->get_height(), dest, 1, 0, 0, 0); // Copy right eye

    RenderTexture::ReleaseTemporary(doubleWideSrc);
    RenderTexture::ReleaseTemporary(doubleWideDst);
}

void AikaTweaks::Hooks::PyramidBloomMainEffectSO() {
    INSTALL_HOOK(getLogger(), PyramidBloomMainEffectSO_Render);
}