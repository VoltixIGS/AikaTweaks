#include "views/SettingsViewController.hpp"
#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "SettingsFlowCoordinator.hpp"
#include "views/AdvancedViewController.hpp"
#include "views/GraphicsPresetsViewController.hpp"
#include "views/GraphicsViewController.hpp"
#include "views/LightingViewController.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

DEFINE_TYPE(AikaTweaks::Views, SettingsViewController);

bool AikaTweaks::Views::SettingsViewController::disableGraphicsButton;
bool AikaTweaks::Views::SettingsViewController::disableAdvancedButton;

void AikaTweaks::Views::SettingsViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        graphicsButton = CreateUIViewControllerButton(container->get_transform(), "Graphics", QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::Views::GraphicsViewController*>());
        OVRPlugin::SystemHeadset systemHeadsetType = OVRPlugin::GetSystemHeadsetType();
        if (systemHeadsetType == OVRPlugin::SystemHeadset::Oculus_Quest_2 ||
            systemHeadsetType == OVRPlugin::SystemHeadset::Oculus_Quest) {
            graphicsPresetsButton = CreateUIViewControllerButton(container->get_transform(), "Graphics Presets", QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::Views::GraphicsPresetsViewController*>());
        }
        lightingButton = CreateUIViewControllerButton(container->get_transform(), "Lighting", QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::Views::LightingViewController*>());
        advancedButton = CreateUIViewControllerButton(container->get_transform(), "Advanced", QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::Views::AdvancedViewController*>());
    }

    if (graphicsButton) {
        graphicsButton->set_interactable(!disableGraphicsButton);
    }
    if (advancedButton) {
        advancedButton->set_interactable(!disableAdvancedButton);
    }
}

UnityEngine::UI::Button* AikaTweaks::Views::SettingsViewController::CreateUIViewControllerButton(
    UnityEngine::Transform* parent,
    std::string title,
    HMUI::ViewController* viewController
) {
    using namespace UnityEngine;

    return QuestUI::BeatSaberUI::CreateUIButton(parent, title, Vector2(), Vector2(36, 8),
        [this, title, viewController]() {
            flowCoordinator->SetTitle(il2cpp_utils::createcsstr(title), ViewController::AnimationType::In);
            flowCoordinator->ReplaceTopViewController(viewController, flowCoordinator, flowCoordinator, nullptr, ViewController::AnimationType::In, ViewController::AnimationDirection::Horizontal);

            reinterpret_cast<AikaTweaks::SettingsFlowCoordinator*>(flowCoordinator)->currentViewController = viewController;
        }
    );
}