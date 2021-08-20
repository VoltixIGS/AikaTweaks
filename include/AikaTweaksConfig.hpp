#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(AikaTweaksConfig,
    CONFIG_VALUE(Resolution, float, "Resolution", 1);
    CONFIG_VALUE(AntiAliasing, int, "AntiAliasing", 2);
    CONFIG_VALUE(RefreshRate, float, "RefreshRate", -1); // We don't know the Refresh Rate, at this time.
    CONFIG_VALUE(Bloom, bool, "Bloom", false);
    CONFIG_VALUE(Smoke, bool, "Smoke", false);
    CONFIG_VALUE(FpsCounter, bool, "FpsCounter", false);
    CONFIG_VALUE(BloomFogIntensity, float, "BloomFogIntensity", 1);
    CONFIG_VALUE(CpuLevel, int, "CpuLevel", 2);
    CONFIG_VALUE(GpuLevel, int, "GpuLevel", 2);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(Resolution);
        CONFIG_INIT_VALUE(AntiAliasing);
        CONFIG_INIT_VALUE(RefreshRate);
        CONFIG_INIT_VALUE(Bloom);
        CONFIG_INIT_VALUE(Smoke);
        CONFIG_INIT_VALUE(FpsCounter);
        CONFIG_INIT_VALUE(BloomFogIntensity);
        CONFIG_INIT_VALUE(CpuLevel);
        CONFIG_INIT_VALUE(GpuLevel);
    )
)