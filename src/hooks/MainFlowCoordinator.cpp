#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "hooks/MainFlowCoordinator.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "GlobalNamespace/PlayerStatisticsViewController.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

using namespace GlobalNamespace;
using namespace HMUI;
using namespace QuestUI;

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
    
    if (getAikaTweaksConfig().HideHowToPlay.GetValue() && firstActivation) {
        self->SetRightScreenViewController(self->playerStatisticsViewController, ViewController::AnimationType::None);
    }
}

MAKE_HOOK_MATCH(
    MainFlowCoordinator_TopViewControllerWillChange,
    &MainFlowCoordinator::TopViewControllerWillChange,
    void,
    MainFlowCoordinator* self,
    ViewController* oldViewController,
    ViewController* newViewController,
    ViewController::AnimationType animationType
) {
    MainFlowCoordinator_TopViewControllerWillChange(self, oldViewController, newViewController, animationType);

    if (getAikaTweaksConfig().HideHowToPlay.GetValue() && newViewController == self->mainMenuViewController) {
        self->SetRightScreenViewController(self->playerStatisticsViewController, ViewController::AnimationType::None);
    }
}

MAKE_HOOK_MATCH(
    MainFlowCoordinator_InitialViewControllerWasPresented,
    &MainFlowCoordinator::InitialViewControllerWasPresented,
    void,
    MainFlowCoordinator* self
) {
    if (getAikaTweaksConfig().HideHowToPlay.GetValue()) {
        self->SetRightScreenViewController(self->playerStatisticsViewController, ViewController::AnimationType::None);
    }

    MainFlowCoordinator_InitialViewControllerWasPresented(self);
}

void AikaTweaks::Hooks::MainFlowCoordinator() {
    INSTALL_HOOK(getLogger(), MainFlowCoordinator_DidActivate);
    INSTALL_HOOK(getLogger(), MainFlowCoordinator_TopViewControllerWillChange);
    INSTALL_HOOK(getLogger(), MainFlowCoordinator_InitialViewControllerWasPresented);
}