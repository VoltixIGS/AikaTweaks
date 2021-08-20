#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "AikaUtils.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

DEFINE_TYPE(AikaTweaks, MainFlowCoordinator);

void AikaTweaks::Install() {
    custom_types::Register::AutoRegister();
    
    QuestUI::Init();
    QuestUI::Register::RegisterModSettingsFlowCoordinator<AikaTweaks::MainFlowCoordinator*>(modInfo);
    
    Hooks::GameplayCoreInstaller();
    Hooks::MainSettingsModelSO();
    Hooks::ParametricBoxFakeGlowController();
    Hooks::PyramidBloomMainEffectSO();
    Hooks::TubeBloomPrePassLight();
    Hooks::VRRenderingParamsSetup();
}

void AikaTweaks::MainFlowCoordinator::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace HMUI;
    
    if (firstActivation) {
        SetTitle(il2cpp_utils::createcsstr(ID), ViewController::AnimationType::Out);

        showBackButton = true;

        mainViewController = QuestUI::BeatSaberUI::CreateViewController<AikaTweaks::MainViewController*>();
        mainViewController->flowCoordinator = this;

        currentViewController = nullptr;

        ProvideInitialViewControllers(mainViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void AikaTweaks::MainFlowCoordinator::BackButtonWasPressed(
    HMUI::ViewController* topViewController
) {
    using namespace GlobalNamespace;
    using namespace HMUI;
    using namespace UnityEngine;

    if (currentViewController) {
        SetTitle(il2cpp_utils::createcsstr(ID), ViewController::AnimationType::In);
        ReplaceTopViewController(mainViewController, this, this, nullptr, ViewController::AnimationType::Out, ViewController::AnimationDirection::Horizontal);

        currentViewController = nullptr;
    } else {
        if (requireRestart) {
            AikaUtils::GetFirstObjectOfType<MenuTransitionsHelper*>()->RestartGame(nullptr);

            requireRestart = false;

            disableGraphics = false;
            disableAdvanced = false;
        } else {
            parentFlowCoordinator->DismissFlowCoordinator(this, ViewController::AnimationDirection::Horizontal, nullptr, false);
        }
    }
}
