#include "views/MainViewController.hpp"
#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "views/AdvancedViewController.hpp"
#include "views/GraphicsPresetsViewController.hpp"
#include "views/GraphicsViewController.hpp"
#include "views/LightingViewController.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

DEFINE_TYPE(AikaTweaks, MainViewController);

void AikaTweaks::MainViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        graphicsButton = CreateUIViewControllerButton(container->get_transform(), "Graphics", QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::GraphicsViewController*>());

        if (OVRPlugin::GetSystemHeadsetType() == OVRPlugin::SystemHeadset::Oculus_Quest_2) {
            CreateUIViewControllerButton(container->get_transform(), "Graphics Presets", QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::GraphicsPresetsViewController*>());
        }

        CreateUIViewControllerButton(container->get_transform(), "Lighting", QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::LightingViewController*>());

        advancedButton = CreateUIViewControllerButton(container->get_transform(), "Advanced", QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::AdvancedViewController*>());
    }

    if (graphicsButton) {
        graphicsButton->set_interactable(!disableGraphics);
    }
    
    if (advancedButton) {
        advancedButton->set_interactable(!disableAdvanced);
    }
}

UnityEngine::UI::Button* AikaTweaks::MainViewController::CreateUIViewControllerButton(
    UnityEngine::Transform* parent,
    std::string title,
    HMUI::ViewController* viewController
) {
    using namespace UnityEngine;

    return QuestUI::BeatSaberUI::CreateUIButton(parent, title, Vector2(), Vector2(36, 8),
        [this, title, viewController]() {
            flowCoordinator->SetTitle(il2cpp_utils::createcsstr(title), ViewController::AnimationType::In);
            flowCoordinator->ReplaceTopViewController(viewController, flowCoordinator, flowCoordinator, nullptr, ViewController::AnimationType::In, ViewController::AnimationDirection::Horizontal);

            reinterpret_cast<MainFlowCoordinator*>(flowCoordinator)->currentViewController = viewController;
        }
    );
}