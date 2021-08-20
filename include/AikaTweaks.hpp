#pragma once

#include "main.hpp"
#include "views/MainViewController.hpp"

namespace AikaTweaks {
    namespace Hooks {
        void GameplayCoreInstaller();
        void MainSettingsModelSO();
        void ParametricBoxFakeGlowController();
        void PyramidBloomMainEffectSO();
        void TubeBloomPrePassLight();
        void VRRenderingParamsSetup();
    }

    namespace VRRenderingParamsSetup {
        void Refresh(std::optional<float> vrResolutionScale = std::nullopt);
    }

    void Install();
}

inline bool requireRestart; // Tells our FlowCoordinator to soft-restart our game, whenever necessary.

DECLARE_CLASS_CODEGEN(AikaTweaks, MainFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INSTANCE_FIELD(AikaTweaks::MainViewController*, mainViewController);
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, currentViewController);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);
)