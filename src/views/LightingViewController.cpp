#include "views/LightingViewController.hpp"
#include "AikaTweaksConfig.hpp"
#include "SettingsFlowCoordinator.hpp"

DEFINE_TYPE(AikaTweaks::Views, LightingViewController);

void AikaTweaks::Views::LightingViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Obstacle Color Multiplier", 1, .1f, getAikaTweaksConfig().ObstacleColorMultiplier.GetValue(), 0, 1,
            [](float value) {
                getAikaTweaksConfig().ObstacleColorMultiplier.SetValue(value);
            }
        );

        QuestUI::BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Bloom Fog Intensity", 1, .1f, getAikaTweaksConfig().BloomFogIntensity.GetValue(), 0, 4,
            [](float value) {
                AikaTweaks::SettingsFlowCoordinator::requireRestart = true;

                getAikaTweaksConfig().BloomFogIntensity.SetValue(value);
            }
        );
    }
}