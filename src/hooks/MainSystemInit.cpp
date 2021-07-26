#include "AikaTweaks.hpp"
#include "hooks/MainSystemInit.hpp"

#include "GlobalNamespace/MainSystemInit.hpp"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(
    MainSystemInit_Init,
    &MainSystemInit::Init,
    void,
    MainSystemInit* self
) {
    mainSettingsModel = self->mainSettingsModel;

    MainSystemInit_Init(self);
}

void AikaTweaks::Hooks::MainSystemInit() {
    INSTALL_HOOK(getLogger(), MainSystemInit_Init);
}