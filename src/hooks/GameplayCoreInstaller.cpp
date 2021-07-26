#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/FPSCounter.hpp"
#include "GlobalNamespace/FPSCounterUIController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "UnityEngine/Resources.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

template <typename T>
T GetFirstObjectOfType() {
    auto objects = Resources::FindObjectsOfTypeAll<T>();
    if (objects) {
        return objects->values[0];
    } else {
        return nullptr;
    }
}

MAKE_HOOK_MATCH(
    GameplayCoreInstaller_InstallBindings,
    &GameplayCoreInstaller::InstallBindings,
    void,
    GameplayCoreInstaller* self
) {
    GameplayCoreInstaller_InstallBindings(self);

    if (getAikaTweaksConfig().FpsCounter.GetValue()) {
        Object::Instantiate(GetFirstObjectOfType<GlobalNamespace::FPSCounterUIController*>())->fpsCounter->set_enabled(true);
    }
}

void AikaTweaks::Hooks::GameplayCoreInstaller() {
    INSTALL_HOOK(getLogger(), GameplayCoreInstaller_InstallBindings);
}