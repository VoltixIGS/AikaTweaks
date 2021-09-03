#pragma once

#include "main.hpp"

#include "UnityEngine/Resources.hpp"

namespace AikaTweaks {
    namespace Utils {
        template <typename T>
        T GetFirstObjectOfType() {
            auto objects = UnityEngine::Resources::FindObjectsOfTypeAll<T>();
            if (objects) {
                return objects->values[0];
            } else {
                return nullptr;
            }
        }
        
        void CopyTexture(UnityEngine::Texture* src, int srcElement, int srcMip, int srcX, int srcY, int srcWidth, int srcHeight, UnityEngine::Texture* dst, int dstElement, int dstMip, int dstX, int dstY);

        UnityEngine::Matrix4x4 GetGPUProjectionMatrix(UnityEngine::Matrix4x4 proj, bool renderIntoTexture);
    }

    namespace Hooks {
        void GameplayCoreInstaller();
        void KawaseBloomMainEffectSO();
        void MainSettingsModelSO();
        void MainSystemInit();
        void ParametricBoxFakeGlowController();
        void PyramidBloomMainEffectSO();
        void StretchableObstacle();
        void TubeBloomPrePassLight();
        void VRRenderingParamsSetup();
    }

    namespace VRRenderingParamsSetup {
        void Refresh(std::optional<float> vrResolutionScale = std::nullopt);
    }

    void Install();
}