#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(AikaTweaksConfig,
    CONFIG_VALUE(Resolution, float, "Resolution", 1);
    CONFIG_VALUE(AntiAliasing, int, "AntiAliasing", 2);
    CONFIG_VALUE(RefreshRate, float, "RefreshRate", -1); // We don't know the Refresh Rate, at this time.
    CONFIG_VALUE(Bloom, int, "Bloom", 0); // 0 = Off, 1 = Default (Pyramid), 2 = Bright (Kawase)
    CONFIG_VALUE(Smoke, bool, "Smoke", false);
    CONFIG_VALUE(FpsCounter, bool, "FpsCounter", true);
    CONFIG_VALUE(ObstacleColorMultiplier, float, "ObstacleColorMultiplier", .2f);
    CONFIG_VALUE(BloomFogIntensity, float, "BloomFogIntensity", 1);
    CONFIG_VALUE(CpuLevel, int, "CpuLevel", 4);
    CONFIG_VALUE(GpuLevel, int, "GpuLevel", 4);
    CONFIG_VALUE(UsedGraphicsPresetBefore, bool, "UsedGraphicsPresetBefore", false);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(Resolution);
        CONFIG_INIT_VALUE(AntiAliasing);
        CONFIG_INIT_VALUE(RefreshRate);
        CONFIG_INIT_VALUE(Bloom);
        CONFIG_INIT_VALUE(Smoke);
        CONFIG_INIT_VALUE(FpsCounter);
        CONFIG_INIT_VALUE(ObstacleColorMultiplier);
        CONFIG_INIT_VALUE(BloomFogIntensity);
        CONFIG_INIT_VALUE(CpuLevel);
        CONFIG_INIT_VALUE(GpuLevel);
        CONFIG_INIT_VALUE(UsedGraphicsPresetBefore);
    )
)