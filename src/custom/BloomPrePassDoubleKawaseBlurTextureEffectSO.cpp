#include "custom/BloomPrePassDoubleKawaseBlurTextureEffectSO.hpp"
#include "AikaTweaks.hpp"

#include "GlobalNamespace/KawaseBlurRendererSO.hpp"

DEFINE_TYPE(AikaTweaks::Custom, BloomPrePassDoubleKawaseBlurTextureEffectSO);

void AikaTweaks::Custom::BloomPrePassDoubleKawaseBlurTextureEffectSO::OnEnable() {
    using namespace GlobalNamespace;

    kawaseBlurRenderer = AikaTweaks::Utils::GetFirstObjectOfType<KawaseBlurRendererSO*>();

    il2cpp_utils::RunMethod(this, il2cpp_utils::FindMethodUnsafe("", "PersistentScriptableObject", "OnEnable", 0));
}