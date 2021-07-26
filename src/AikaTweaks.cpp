#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "hooks/MainFlowCoordinator.hpp"
#include "hooks/MainSystemInit.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"

using namespace GlobalNamespace;
using namespace HMUI;
using namespace QuestUI;
using namespace UnityEngine;

DEFINE_TYPE(AikaTweaks, MainViewController);

void AikaTweaks::Install() {
    custom_types::Register::AutoRegister();
    
    QuestUI::Init();
    QuestUI::Register::RegisterModSettingsViewController<AikaTweaks::MainViewController*>(ModInfo{"AikaTweaks", VERSION});
    
    Hooks::GameplayCoreInstaller();
    Hooks::MainFlowCoordinator();
    Hooks::MainMenuViewController();
    Hooks::MainSettingsModelSO();
    Hooks::MainSystemInit();
    Hooks::NoteDebris();
    Hooks::NoteJump();
    Hooks::NoteMovement();
    Hooks::TubeBloomPrePassLight();
    Hooks::VRRenderingParamsSetup();
}

void AikaTweaks::MainViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    if (firstActivation) {
        GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        BeatSaberUI::CreateText(container->get_transform(), "<color=yellow>Warning: Modifying certain tweaks *may* require a soft-restart.");

        if (OVRPlugin::GetSystemHeadsetType() == OVRPlugin::SystemHeadset::Oculus_Quest) {
            BeatSaberUI::CreateText(container->get_transform(), "<color=red>Detected Oculus Quest (1), certain tweaks *may* be unavailable.");
        }

        BeatSaberUI::CreateText(container->get_transform(), "<size=200%>Graphics");

        float resolutionMaxValue = 1.2f;
        if (OVRPlugin::GetSystemHeadsetType() == OVRPlugin::SystemHeadset::Oculus_Quest_2) {
            resolutionMaxValue = 1.4f;
        }
        
        BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Resolution", 1, 0.1f, getAikaTweaksConfig().Resolution.GetValue(), 0.4f, resolutionMaxValue,
            [this](float value) {
                _requireRestart = true;
                getAikaTweaksConfig().Resolution.SetValue(value);
            }
        );

        Array<float>* systemDisplayFrequenciesAvailable = OVRPlugin::get_systemDisplayFrequenciesAvailable();
        if (systemDisplayFrequenciesAvailable->Length() > 1) {
            // This is a bit terrible, but oh well...
            std::vector<std::string> refreshRates;
            for (int i = 0; i < systemDisplayFrequenciesAvailable->Length(); i++) {
                refreshRates.push_back(std::to_string(systemDisplayFrequenciesAvailable->values[i]));
            }

            BeatSaberUI::CreateDropdown(container->get_transform(), "Refresh Rate", std::to_string(getAikaTweaksConfig().RefreshRate.GetValue()), refreshRates,
                [](const std::string& value) {
                    getAikaTweaksConfig().RefreshRate.SetValue(std::stof(value));
                    VRRenderingParamsSetup::Refresh();
                }
            );
        }

        BeatSaberUI::CreateToggle(container->get_transform(), "Smoke", getAikaTweaksConfig().Smoke.GetValue(), 
            [this](bool value) {
                _requireRestart = true;
                getAikaTweaksConfig().Smoke.SetValue(value);
            }
        );

        BeatSaberUI::CreateToggle(container->get_transform(), "Burn Marks", getAikaTweaksConfig().BurnMarks.GetValue(), 
            [this](bool value) {
                _requireRestart = true;
                getAikaTweaksConfig().BurnMarks.SetValue(value);
            }
        );

        BeatSaberUI::CreateToggle(container->get_transform(), "FPS Counter", getAikaTweaksConfig().FpsCounter.GetValue(), 
            [](bool value) {
                getAikaTweaksConfig().FpsCounter.SetValue(value);
            }
        );

        BeatSaberUI::CreateText(container->get_transform(), "<size=200%>Lighting");

        BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Bloom Fog Intensity", 1, 0.1f, getAikaTweaksConfig().BloomFogIntensity.GetValue(), 0.0f, 4.0f,
            [this](float value) {
                _requireRestart = true;
                getAikaTweaksConfig().BloomFogIntensity.SetValue(value);
            }
        );

        BeatSaberUI::CreateText(container->get_transform(), "<size=200%>Debris");

        BeatSaberUI::CreateToggle(container->get_transform(), "Oldschool", getAikaTweaksConfig().DebrisOldschool.GetValue(), 
            [](bool value) { 
                getAikaTweaksConfig().DebrisOldschool.SetValue(value);
            }
        );

        BeatSaberUI::CreateText(container->get_transform(), "<size=200%>Misc.");

        BeatSaberUI::CreateToggle(container->get_transform(), "Feet Saber (Experimental)", getAikaTweaksConfig().FeetSaber.GetValue(), 
            [](bool value) { 
                getAikaTweaksConfig().FeetSaber.SetValue(value);
            }
        );

        BeatSaberUI::CreateText(container->get_transform(), "<size=200%>Main Menu");

        BeatSaberUI::CreateToggle(container->get_transform(), "Hide Solo", getAikaTweaksConfig().HideSolo.GetValue(), 
            [](bool value) { 
                getAikaTweaksConfig().HideSolo.SetValue(value);
            }
        );

        BeatSaberUI::CreateToggle(container->get_transform(), "Hide Party", getAikaTweaksConfig().HideParty.GetValue(), 
            [](bool value) { 
                getAikaTweaksConfig().HideParty.SetValue(value);
            }
        );

        BeatSaberUI::CreateToggle(container->get_transform(), "Hide Campaign", getAikaTweaksConfig().HideCampaign.GetValue(), 
            [](bool value) { 
                getAikaTweaksConfig().HideCampaign.SetValue(value);
            }
        );

        BeatSaberUI::CreateToggle(container->get_transform(), "Hide Quit", getAikaTweaksConfig().HideQuit.GetValue(), 
            [](bool value) { 
                getAikaTweaksConfig().HideQuit.SetValue(value);
            }
        );

        BeatSaberUI::CreateToggle(container->get_transform(), "Hide Multiplayer", getAikaTweaksConfig().HideMultiplayer.GetValue(), 
            [](bool value) { 
                getAikaTweaksConfig().HideMultiplayer.SetValue(value);
            }
        );

        BeatSaberUI::CreateToggle(container->get_transform(), "Hide How To Play", getAikaTweaksConfig().HideHowToPlay.GetValue(), 
            [](bool value) { 
                getAikaTweaksConfig().HideHowToPlay.SetValue(value);
            }
        );

        BeatSaberUI::CreateToggle(container->get_transform(), "Hide Promo", getAikaTweaksConfig().HidePromo.GetValue(), 
            [](bool value) { 
                getAikaTweaksConfig().HidePromo.SetValue(value);
            }
        );
    }
}

void AikaTweaks::MainViewController::DidDeactivate(
    bool removedFromHierarchy,
    bool screenSystemDisabling
) {
    if (_requireRestart && mainSettingsModel && menuTransitionsHelper) {
        mainSettingsModel->Load(true);
        menuTransitionsHelper->RestartGame(nullptr);
    }
}