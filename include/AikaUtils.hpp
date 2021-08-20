#pragma once

#include "main.hpp"

#include "UnityEngine/Resources.hpp"

namespace AikaUtils {
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