#include "views/GraphicsViewController.hpp"
#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"

DEFINE_TYPE(AikaTweaks, GraphicsViewController);

void AikaTweaks::GraphicsViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        float resolutionMaxValue = 1.2f;
        if (OVRPlugin::GetSystemHeadsetType() == OVRPlugin::SystemHeadset::Oculus_Quest_2) {
            resolutionMaxValue = 1.4f;
        }
        
        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Resolution", 2, .05f, getAikaTweaksConfig().Resolution.GetValue(), .4f, resolutionMaxValue,
            [](float value) {
                getAikaTweaksConfig().Resolution.SetValue(value);

                AikaTweaks::VRRenderingParamsSetup::Refresh(std::make_optional(value));
            }
        );

        // I fucking hate this shit.
        std::vector<std::string> antiAliasingValues{"Off", "2x", "4x"};
        std::string antiAliasingValue(antiAliasingValues[0]);
        if (getAikaTweaksConfig().AntiAliasing.GetValue() == 2) {
            antiAliasingValue = antiAliasingValues[1];
        } else if (getAikaTweaksConfig().AntiAliasing.GetValue() == 4) {
            antiAliasingValue = antiAliasingValues[2];
        }

        QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Anti-Aliasing", antiAliasingValue, antiAliasingValues,
            [](const std::string& value) {
                requireRestart = true;
                
                if (value == "Off") {
                    getAikaTweaksConfig().AntiAliasing.SetValue(1);
                } else if (value == "2x") {
                    getAikaTweaksConfig().AntiAliasing.SetValue(2);
                } else if (value == "4x") {
                    getAikaTweaksConfig().AntiAliasing.SetValue(4);
                }
            }
        );

        ::Array<float>* systemDisplayFrequenciesAvailable = OVRPlugin::get_systemDisplayFrequenciesAvailable();
        if (systemDisplayFrequenciesAvailable->Length() > 1) {
            // This is a bit terrible, but oh well...
            std::vector<std::string> systemDisplayFrequencyValues;
            for (int i = 0; i < systemDisplayFrequenciesAvailable->Length(); i++) {
                systemDisplayFrequencyValues.push_back(string_format("%d", (int)systemDisplayFrequenciesAvailable->values[i]));
            }

            QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Refresh Rate", string_format("%d", (int)getAikaTweaksConfig().RefreshRate.GetValue()), systemDisplayFrequencyValues,
                [](const std::string& value) {
                    getAikaTweaksConfig().RefreshRate.SetValue(std::stof(value));

                    AikaTweaks::VRRenderingParamsSetup::Refresh();
                }
            );
        }

        QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "Bloom", getAikaTweaksConfig().Bloom.GetValue(), 
            [](bool value) {
                requireRestart = true;

                getAikaTweaksConfig().Bloom.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "Smoke", getAikaTweaksConfig().Smoke.GetValue(), 
            [](bool value) {
                requireRestart = true;

                getAikaTweaksConfig().Smoke.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "FPS Counter", getAikaTweaksConfig().FpsCounter.GetValue(), 
            [](bool value) {
                getAikaTweaksConfig().FpsCounter.SetValue(value);
            }
        );
    }
}