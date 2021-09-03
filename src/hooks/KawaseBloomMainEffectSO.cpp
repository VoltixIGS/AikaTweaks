#include "AikaTweaks.hpp"

#include "GlobalNamespace/KawaseBloomMainEffectSO.hpp"
#include "GlobalNamespace/KawaseBlurRendererSO.hpp"
#include "GlobalNamespace/KawaseBlurRendererSO_WeightsType.hpp"
#include "UnityEngine/Graphics.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Rendering/TextureDimension.hpp"
#include "UnityEngine/RenderTexture.hpp"
#include "UnityEngine/Shader.hpp"

MAKE_HOOK_MATCH(
    KawaseBloomMainEffectSO_Render,
    &GlobalNamespace::KawaseBloomMainEffectSO::Render,
    void,
    GlobalNamespace::KawaseBloomMainEffectSO* self,
    UnityEngine::RenderTexture* src,
    UnityEngine::RenderTexture* dest,
    float fade
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;
    using namespace UnityEngine::Rendering;

    // Describe the double wide texture.
    RenderTextureDescriptor doubleWideDesc = src->get_descriptor();
    doubleWideDesc.dimension = TextureDimension::Tex2D;
    doubleWideDesc.vrUsage = VRTextureUsage::OneEye;
    doubleWideDesc.width *= 2;

    RenderTexture* doubleWideSrc = RenderTexture::GetTemporary(doubleWideDesc);

    // Copy both our left and right eye.
    AikaTweaks::Utils::CopyTexture(src, 0, 0, 0, 0, src->get_width(), src->get_height(), doubleWideSrc, 0, 0, 0, 0);
    AikaTweaks::Utils::CopyTexture(src, 1, 0, 0, 0, src->get_width(), src->get_height(), doubleWideSrc, 0, 0, src->get_width(), 0);

    RenderTexture* doubleWideDst = RenderTexture::GetTemporary(doubleWideDesc);

    self->LazyInitializeMaterials();

    int width = self->bloomTextureWidth * ((doubleWideSrc->get_vrUsage() == VRTextureUsage::TwoEyes) ? 2 : 1);
    int height = static_cast<int>(static_cast<float>(self->bloomTextureWidth * doubleWideSrc->get_height()) / static_cast<float>(doubleWideSrc->get_width())) * ((doubleWideSrc->get_vrUsage() == VRTextureUsage::TwoEyes) ? 2 : 1);

    RenderTexture* temporary = RenderTexture::GetTemporary(width, height, 0, RenderTextureFormat::RGB111110Float, RenderTextureReadWrite::Linear);

    // Fix our projection matrix, before rendering bloom.
    Matrix4x4 projectionMatrix = AikaTweaks::Utils::GetGPUProjectionMatrix(Matrix4x4::Ortho(0, 1, 0, 1, -1, 100), true);
    static ::Il2CppString* name = il2cpp_utils::newcsstr("unity_StereoMatrixVP");
    Shader::SetGlobalMatrix(name, projectionMatrix);

    self->kawaseBlurRenderer->Bloom(doubleWideSrc, temporary, 0, self->bloomIterations, self->bloomBoost, self->bloomAlphaWeights, KawaseBlurRendererSO::WeightsType::AlphaWeights, nullptr);

    self->mainEffectMaterial->SetFloat(KawaseBloomMainEffectSO::_get__bloomIntensityID(), self->bloomIntensity);
    self->mainEffectMaterial->SetTexture(KawaseBloomMainEffectSO::_get__bloomTexID(), temporary);

    Graphics::Blit(doubleWideSrc, doubleWideDst, self->mainEffectMaterial, 0);

    RenderTexture::ReleaseTemporary(temporary);

    if (fade < .99f) {
        self->fadeMaterial->set_color(Color(0, 0, 0, 1 - fade));

        Graphics::Blit(nullptr, doubleWideDst, self->fadeMaterial);
    }

    // Now our doubleWideDst has had the bloom applied to it, so now we need to copy it into the dst texture array.
    // Also, copy both our left and right eye again.
    AikaTweaks::Utils::CopyTexture(doubleWideDst, 0, 0, 0, 0, src->get_width(), src->get_height(), dest, 0, 0, 0, 0);
    AikaTweaks::Utils::CopyTexture(doubleWideDst, 0, 0, src->get_width(), 0, src->get_width(), src->get_height(), dest, 1, 0, 0, 0);

    RenderTexture::ReleaseTemporary(doubleWideSrc);
    RenderTexture::ReleaseTemporary(doubleWideDst);
}

void AikaTweaks::Hooks::KawaseBloomMainEffectSO() {
    INSTALL_HOOK(getLogger(), KawaseBloomMainEffectSO_Render);
}