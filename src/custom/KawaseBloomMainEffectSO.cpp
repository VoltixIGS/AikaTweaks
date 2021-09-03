#include "custom/KawaseBloomMainEffectSO.hpp"
#include "AikaTweaks.hpp"

#include "GlobalNamespace/KawaseBlurRendererSO.hpp"
#include "GlobalNamespace/PyramidBloomMainEffectSO.hpp"

DEFINE_TYPE(AikaTweaks::Custom, KawaseBloomMainEffectSO);

void AikaTweaks::Custom::KawaseBloomMainEffectSO::OnEnable() {
    using namespace GlobalNamespace;

    kawaseBlurRenderer = AikaTweaks::Utils::GetFirstObjectOfType<KawaseBlurRendererSO*>();

    PyramidBloomMainEffectSO* pyramidBloomMainEffectSO = AikaTweaks::Utils::GetFirstObjectOfType<PyramidBloomMainEffectSO*>();

    fadeShader = pyramidBloomMainEffectSO->fadeShader;
    mainEffectShader = pyramidBloomMainEffectSO->mainEffectShader;

    il2cpp_utils::RunMethod(this, il2cpp_utils::FindMethodUnsafe("", "KawaseBloomMainEffectSO", "OnEnable", 0));
}