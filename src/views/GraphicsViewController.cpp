#include "views/GraphicsViewController.hpp"
#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "SettingsFlowCoordinator.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"

DEFINE_TYPE(AikaTweaks::Views, GraphicsViewController);

void AikaTweaks::Views::GraphicsViewController::DidActivate(
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
        std::vector<std::u16string> antiAliasingValues = { u"Off", u"2x", u"4x" };
        std::u16string antiAliasingValue = antiAliasingValues[0];
        if (getAikaTweaksConfig().AntiAliasing.GetValue() == 2) {
            antiAliasingValue = antiAliasingValues[1];
        } else if (getAikaTweaksConfig().AntiAliasing.GetValue() == 4) {
            antiAliasingValue = antiAliasingValues[2];
        }
        QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Anti-Aliasing", antiAliasingValue, antiAliasingValues,
            [antiAliasingValues](std::u16string_view value) {
                AikaTweaks::SettingsFlowCoordinator::requireRestart = true;
                
                if (value == antiAliasingValues[0]) {
                    getAikaTweaksConfig().AntiAliasing.SetValue(1);
                } else if (value == antiAliasingValues[1]) {
                    getAikaTweaksConfig().AntiAliasing.SetValue(2);
                } else if (value == antiAliasingValues[2]) {
                    getAikaTweaksConfig().AntiAliasing.SetValue(4);
                }
            }
        );

        ::Array<float>* systemDisplayFrequenciesAvailable = OVRPlugin::get_systemDisplayFrequenciesAvailable();
        if (systemDisplayFrequenciesAvailable->Length() > 1) {
            // This is a bit terrible, but oh well...
            std::vector<std::u16string> systemDisplayFrequencyValues;
            for (int i = 0; i < systemDisplayFrequenciesAvailable->Length(); i++) {
                systemDisplayFrequencyValues.push_back(to_utf16(string_format("%d", (int)systemDisplayFrequenciesAvailable->values[i])));
            }

            QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Refresh Rate", to_utf16(string_format("%d", (int)getAikaTweaksConfig().RefreshRate.GetValue())), systemDisplayFrequencyValues,
                [](std::u16string_view value) {
                    getAikaTweaksConfig().RefreshRate.SetValue(std::stof(to_utf8(value)));

                    AikaTweaks::VRRenderingParamsSetup::Refresh();
                }
            );
        }
        
        if (getAikaTweaksConfig().UsedGraphicsPresetBefore.GetValue()) {
            // I fucking hate this shit, again.
            std::vector<std::u16string> bloomValues = { u"Off", u"Default", u"Bright" };
            std::u16string bloomValue = bloomValues[getAikaTweaksConfig().Bloom.GetValue()];
            QuestUI::BeatSaberUI::CreateDropdown(container->get_transform(), "Bloom", bloomValue, bloomValues,
                [bloomValues](std::u16string_view value) {
                    AikaTweaks::SettingsFlowCoordinator::requireRestart = true;
                    
                    if (value == bloomValues[0]) {
                        getAikaTweaksConfig().Bloom.SetValue(0);
                    } else if (value == bloomValues[1]) {
                        getAikaTweaksConfig().Bloom.SetValue(1);
                    } else if (value == bloomValues[2]) {
                        getAikaTweaksConfig().Bloom.SetValue(2);
                    }
                }
            );
        }

        QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "Smoke", getAikaTweaksConfig().Smoke.GetValue(), 
            [](bool value) {
                AikaTweaks::SettingsFlowCoordinator::requireRestart = true;

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