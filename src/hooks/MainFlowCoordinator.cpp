#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "hooks/MainFlowCoordinator.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(
    MainFlowCoordinator_DidActivate,
    &MainFlowCoordinator::DidActivate,
    void,
    MainFlowCoordinator* self,
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    menuTransitionsHelper = self->menuTransitionsHelper;

    MainFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

void AikaTweaks::Hooks::MainFlowCoordinator() {
    INSTALL_HOOK(getLogger(), MainFlowCoordinator_DidActivate);
}