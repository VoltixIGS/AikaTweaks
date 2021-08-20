#include "views/LightingViewController.hpp"
#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

DEFINE_TYPE(AikaTweaks, LightingViewController);

void AikaTweaks::LightingViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Bloom Fog Intensity", 1, .1f, getAikaTweaksConfig().BloomFogIntensity.GetValue(), 0, 4,
            [](float value) {
                requireRestart = true;

                getAikaTweaksConfig().BloomFogIntensity.SetValue(value);
            }
        );
    }
}