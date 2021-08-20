#include "views/AdvancedViewController.hpp"
#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

DEFINE_TYPE(AikaTweaks, AdvancedViewController);

void AikaTweaks::AdvancedViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "CPU Level", 0, 1, getAikaTweaksConfig().CpuLevel.GetValue(), 0, 4,
            [](float value) {
                getAikaTweaksConfig().CpuLevel.SetValue(static_cast<int>(value));

                AikaTweaks::VRRenderingParamsSetup::Refresh();
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "GPU Level", 0, 1, getAikaTweaksConfig().GpuLevel.GetValue(), 0, 4,
            [](float value) {
                getAikaTweaksConfig().GpuLevel.SetValue(static_cast<int>(value));
                
                AikaTweaks::VRRenderingParamsSetup::Refresh();
            }
        );
    }
}