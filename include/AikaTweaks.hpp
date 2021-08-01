#pragma once

#include "main.hpp"

#include "HMUI/ViewController.hpp"

namespace AikaTweaks {
    namespace Hooks {
        void GameplayCoreInstaller();
        void MainFlowCoordinator();
        void MainMenuViewController();
        void MainSettingsModelSO();
        void MainSystemInit();
        void ParametricBoxFakeGlowController();
        void TubeBloomPrePassLight();
        void VRRenderingParamsSetup();
    }

    namespace VRRenderingParamsSetup {
        void Refresh(std::optional<float> vrResolutionScale = std::nullopt);
    }

    void Install();
}

DECLARE_CLASS_CODEGEN(AikaTweaks, MainViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(bool, _requireRestart); // Used to tell our ViewController when DidDeactivate is run to soft-restart our game.

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 2), bool removedFromHierarchy, bool screenSystemDisabling);
)