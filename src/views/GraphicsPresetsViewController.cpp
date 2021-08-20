#include "views/GraphicsPresetsViewController.hpp"
#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"
#include "views/MainViewController.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"

DEFINE_TYPE(AikaTweaks, GraphicsPresetsViewController);

void AikaTweaks::GraphicsPresetsViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        QuestUI::BeatSaberUI::CreateText(container->get_transform(), "<color=yellow>Graphics changes will apply upon the next soft-restart.");
        
        if (OVRPlugin::GetSystemHeadsetType() == OVRPlugin::SystemHeadset::Oculus_Quest_2) {
            QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "Performance",
                []() {
                    requireRestart = true;

                    disableGraphics = true;
                    disableAdvanced = true;

                    getAikaTweaksConfig().Resolution.SetValue(1);
                    getAikaTweaksConfig().AntiAliasing.SetValue(2);
                    getAikaTweaksConfig().RefreshRate.SetValue(120);
                    getAikaTweaksConfig().Bloom.SetValue(false);
                    getAikaTweaksConfig().Smoke.SetValue(false);
                    getAikaTweaksConfig().CpuLevel.SetValue(4);
                    getAikaTweaksConfig().GpuLevel.SetValue(4);
                }
            );

            QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "Quality",
                []() {
                    requireRestart = true;
                    
                    disableGraphics = true;
                    disableAdvanced = true;

                    getAikaTweaksConfig().Resolution.SetValue(1.2f);
                    getAikaTweaksConfig().AntiAliasing.SetValue(2);
                    getAikaTweaksConfig().RefreshRate.SetValue(90);
                    getAikaTweaksConfig().Bloom.SetValue(false);
                    getAikaTweaksConfig().Smoke.SetValue(true);
                    getAikaTweaksConfig().CpuLevel.SetValue(2);
                    getAikaTweaksConfig().GpuLevel.SetValue(2);
                }
            );

            QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "Bloom",
                []() {
                    requireRestart = true;
                    
                    disableGraphics = true;
                    disableAdvanced = true;

                    getAikaTweaksConfig().Resolution.SetValue(.7f);
                    getAikaTweaksConfig().AntiAliasing.SetValue(2);
                    getAikaTweaksConfig().RefreshRate.SetValue(80);
                    getAikaTweaksConfig().Bloom.SetValue(true);
                    getAikaTweaksConfig().Smoke.SetValue(false);
                    getAikaTweaksConfig().CpuLevel.SetValue(4);
                    getAikaTweaksConfig().GpuLevel.SetValue(4);
                }
            );

            QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "Power Saving",
                []() {
                    requireRestart = true;
                    
                    disableGraphics = true;
                    disableAdvanced = true;

                    getAikaTweaksConfig().Resolution.SetValue(.7f);
                    getAikaTweaksConfig().AntiAliasing.SetValue(1);
                    getAikaTweaksConfig().RefreshRate.SetValue(72);
                    getAikaTweaksConfig().Bloom.SetValue(false);
                    getAikaTweaksConfig().Smoke.SetValue(false);
                    getAikaTweaksConfig().CpuLevel.SetValue(0);
                    getAikaTweaksConfig().GpuLevel.SetValue(0);
                }
            );
        }
    }
}