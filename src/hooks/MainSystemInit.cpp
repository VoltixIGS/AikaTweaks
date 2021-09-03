#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "custom/BloomPrePassDoubleKawaseBlurTextureEffectSO.hpp"
#include "custom/KawaseBloomMainEffectSO.hpp"

#include "GlobalNamespace/BloomPrePassEffectContainerSO.hpp"
#include "GlobalNamespace/MainEffectContainerSO.hpp"
#include "GlobalNamespace/MainSystemInit.hpp"

MAKE_HOOK_MATCH(
    MainSystemInit_Init,
    &GlobalNamespace::MainSystemInit::Init,
    void,
    GlobalNamespace::MainSystemInit* self
) {
    using namespace UnityEngine;

    MainSystemInit_Init(self);

    if (getAikaTweaksConfig().Bloom.GetValue() == 2) {
        self->bloomPrePassEffectContainer->Init(ScriptableObject::CreateInstance<AikaTweaks::Custom::BloomPrePassDoubleKawaseBlurTextureEffectSO*>());
        self->mainEffectContainer->Init(ScriptableObject::CreateInstance<AikaTweaks::Custom::KawaseBloomMainEffectSO*>());
    }
}

void AikaTweaks::Hooks::MainSystemInit() {
    INSTALL_HOOK(getLogger(), MainSystemInit_Init);
}