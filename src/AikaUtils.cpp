#include "AikaUtils.hpp"

#include "UnityEngine/Resources.hpp"

void AikaUtils::CopyTexture(UnityEngine::Texture* src, int srcElement, int srcMip, int srcX, int srcY, int srcWidth, int srcHeight, UnityEngine::Texture* dst, int dstElement, int dstMip, int dstX, int dstY) {
    using namespace UnityEngine;
    
    static auto CopyTexture_Region = reinterpret_cast<function_ptr_t<void, Texture*, int, int, int, int, int, int, Texture*, int, int, int, int>>(il2cpp_functions::resolve_icall("UnityEngine.Graphics::CopyTexture_Region"));
    
    CopyTexture_Region(src, srcElement, srcMip, srcX, srcY, srcWidth, srcHeight, dst, dstElement, dstMip, dstX, dstY);
}

UnityEngine::Matrix4x4 AikaUtils::GetGPUProjectionMatrix(UnityEngine::Matrix4x4 proj, bool renderIntoTexture) {
    using namespace UnityEngine;

    static auto GetGPUProjectionMatrix_Injected = reinterpret_cast<function_ptr_t<void, ByRef<Matrix4x4>, bool, ByRef<Matrix4x4>>>(il2cpp_functions::resolve_icall("UnityEngine.GL::GetGPUProjectionMatrix_Injected"));

    Matrix4x4 result;
    GetGPUProjectionMatrix_Injected(proj, renderIntoTexture, result);
    return result;
}