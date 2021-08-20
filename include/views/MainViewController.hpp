#pragma once

#include "main.hpp"

// Tells our MainViewController to disable the "Graphics" and "Advanced" buttons until the next soft-restart, whenever necessary.
inline bool disableGraphics;
inline bool disableAdvanced;

DECLARE_CLASS_CODEGEN(AikaTweaks, MainViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, flowCoordinator);

    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, graphicsButton);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, advancedButton);
    
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

public:
    UnityEngine::UI::Button* CreateUIViewControllerButton(UnityEngine::Transform* parent, std::string title, HMUI::ViewController* viewController);
)