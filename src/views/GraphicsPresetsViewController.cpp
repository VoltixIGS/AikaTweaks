#include "views/GraphicsPresetsViewController.hpp"
#include "AikaTweaksConfig.hpp"
#include "SettingsFlowCoordinator.hpp"
#include "views/SettingsViewController.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"

DEFINE_TYPE(AikaTweaks::Views, GraphicsPresetsViewController);

void AikaTweaks::Views::GraphicsPresetsViewController::DidActivate(
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    using namespace GlobalNamespace;
    using namespace UnityEngine;

    if (firstActivation) {
        GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        QuestUI::BeatSaberUI::CreateText(container->get_transform(), "<color=yellow>Graphics changes will apply upon the next soft-restart.");

        OVRPlugin::SystemHeadset systemHeadsetType = OVRPlugin::GetSystemHeadsetType();
        if (systemHeadsetType == OVRPlugin::SystemHeadset::Oculus_Quest_2) {
            CreateUIGraphicsPresetButton(container->get_transform(), "Default",
                std::make_optional(1.f),
                std::make_optional(2),
                std::make_optional(120.f),
                std::make_optional(0),
                std::make_optional(false),
                std::make_optional(4),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Quality",
                std::make_optional(1.f),
                std::make_optional(2),
                std::make_optional(90.f),
                std::make_optional(0),
                std::make_optional(true),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Bloom",
                std::make_optional(.8f),
                std::make_optional(2),
                std::make_optional(72.f),
                std::make_optional(1),
                std::make_optional(false),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Power Saving",
                std::make_optional(.7f),
                std::make_optional(1),
                std::make_optional(72.f),
                std::make_optional(0),
                std::make_optional(false),
                std::make_optional(0),
                std::make_optional(0)
            );
        } else if (systemHeadsetType == OVRPlugin::SystemHeadset::Oculus_Quest) {
            CreateUIGraphicsPresetButton(container->get_transform(), "Default",
                std::make_optional(1.f),
                std::make_optional(2),
                std::make_optional(72.f),
                std::make_optional(0),
                std::make_optional(false),
                std::make_optional(4),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Quality",
                std::make_optional(1.2f),
                std::make_optional(1),
                std::make_optional(72.f),
                std::make_optional(0),
                std::make_optional(true),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Bloom",
                std::make_optional(.7f),
                std::make_optional(1),
                std::make_optional(72.f),
                std::make_optional(1),
                std::make_optional(false),
                std::make_optional(2),
                std::make_optional(4)
            );

            CreateUIGraphicsPresetButton(container->get_transform(), "Power Saving",
                std::make_optional(.7f),
                std::make_optional(1),
                std::make_optional(60.f),
                std::make_optional(0),
                std::make_optional(false),
                std::make_optional(0),
                std::make_optional(0)
            );
        }
    }
}

UnityEngine::UI::Button* AikaTweaks::Views::GraphicsPresetsViewController::CreateUIGraphicsPresetButton(
    UnityEngine::Transform* parent,
    std::string buttonText,
    std::optional<float> resolution,
    std::optional<int> antiAliasing,
    std::optional<float> refreshRate,
    std::optional<int> bloom,
    std::optional<bool> smoke,
    std::optional<int> cpuLevel,
    std::optional<int> gpuLevel
) {
    using namespace UnityEngine;

    return QuestUI::BeatSaberUI::CreateUIButton(parent, buttonText,
        [this, resolution, antiAliasing, refreshRate, bloom, smoke, cpuLevel, gpuLevel]() {
            AikaTweaks::Views::SettingsViewController::disableGraphicsButton = resolution.has_value() || antiAliasing.has_value() || refreshRate.has_value() || bloom.has_value() || smoke.has_value();
            AikaTweaks::Views::SettingsViewController::disableAdvancedButton = cpuLevel.has_value() || gpuLevel.has_value();

            AikaTweaks::SettingsFlowCoordinator::requireRestart = AikaTweaks::Views::SettingsViewController::disableGraphicsButton || AikaTweaks::Views::SettingsViewController::disableAdvancedButton;

            if (resolution.has_value()) {
                getAikaTweaksConfig().Resolution.SetValue(resolution.value());
            }
            if (antiAliasing.has_value()) {
                getAikaTweaksConfig().AntiAliasing.SetValue(antiAliasing.value());
            }
            if (refreshRate.has_value()) {
                getAikaTweaksConfig().RefreshRate.SetValue(refreshRate.value());
            }
            if (bloom.has_value()) {
                getAikaTweaksConfig().Bloom.SetValue(bloom.value());
            }
            if (smoke.has_value()) {
                getAikaTweaksConfig().Smoke.SetValue(smoke.value());
            }
            if (cpuLevel.has_value()) {
                getAikaTweaksConfig().CpuLevel.SetValue(cpuLevel.value());
            }
            if (gpuLevel.has_value()) {
                getAikaTweaksConfig().GpuLevel.SetValue(gpuLevel.value());
            }

            getAikaTweaksConfig().UsedGraphicsPresetBefore.SetValue(true);
        }
    );
}