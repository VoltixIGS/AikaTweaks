#include "SettingsFlowCoordinator.hpp"
#include "AikaTweaks.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

DEFINE_TYPE(AikaTweaks, SettingsFlowCoordinator);

bool AikaTweaks::SettingsFlowCoordinator::requireRestart;

void AikaTweaks::SettingsFlowCoordinator::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace HMUI;
    
    if (firstActivation) {
        SetTitle(il2cpp_utils::createcsstr(ID), ViewController::AnimationType::Out);

        showBackButton = true;

        settingsViewController = QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::Views::SettingsViewController*>();
        settingsViewController->flowCoordinator = this;

        currentViewController = nullptr;

        ProvideInitialViewControllers(settingsViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void AikaTweaks::SettingsFlowCoordinator::BackButtonWasPressed(
    HMUI::ViewController* topViewController
) {
    using namespace GlobalNamespace;
    using namespace HMUI;
    using namespace UnityEngine;

    if (currentViewController) {
        SetTitle(il2cpp_utils::createcsstr(ID), ViewController::AnimationType::In);
        ReplaceTopViewController(settingsViewController, this, this, nullptr, ViewController::AnimationType::Out, ViewController::AnimationDirection::Horizontal);

        currentViewController = nullptr;
    } else {
        if (requireRestart) {
            AikaTweaks::Utils::GetFirstObjectOfType<MenuTransitionsHelper*>()->RestartGame(nullptr);

            requireRestart = false;

            AikaTweaks::Views::SettingsViewController::disableGraphicsButton = false;
            AikaTweaks::Views::SettingsViewController::disableAdvancedButton = false;
        } else {
            parentFlowCoordinator->DismissFlowCoordinator(this, ViewController::AnimationDirection::Horizontal, nullptr, false);
        }
    }
}
