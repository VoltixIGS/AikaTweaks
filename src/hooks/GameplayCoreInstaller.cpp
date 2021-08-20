#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "AikaUtils.hpp"

#include "GlobalNamespace/FPSCounter.hpp"
#include "GlobalNamespace/FPSCounterUIController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"

MAKE_HOOK_MATCH(
    GameplayCoreInstaller_InstallBindings,
    &GlobalNamespace::GameplayCoreInstaller::InstallBindings,
    void,
    GlobalNamespace::GameplayCoreInstaller* self
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    GameplayCoreInstaller_InstallBindings(self);

    if (getAikaTweaksConfig().FpsCounter.GetValue()) {
        FPSCounterUIController* fpsCounterUIController = Object::Instantiate(AikaUtils::GetFirstObjectOfType<FPSCounterUIController*>());
        fpsCounterUIController->fpsCounter->set_enabled(true);
    }
}

void AikaTweaks::Hooks::GameplayCoreInstaller() {
    INSTALL_HOOK(getLogger(), GameplayCoreInstaller_InstallBindings);
}