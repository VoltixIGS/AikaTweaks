#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(AikaTweaksConfig,
    CONFIG_VALUE(Resolution, float, "Resolution", 1.0f);
    CONFIG_VALUE(RefreshRate, float, "RefreshRate", -1.0f); // We don't know the Refresh Rate, at this time.
    CONFIG_VALUE(EnhancedFakeGlow, bool, "EnhancedFakeGlow", true);
    CONFIG_VALUE(Smoke, bool, "Smoke", false);
    CONFIG_VALUE(FpsCounter, bool, "FpsCounter", true);
    CONFIG_VALUE(BloomFogIntensity, float, "BloomFogIntensity", 1.0f);
    CONFIG_VALUE(HideHowToPlay, bool, "HideHowToPlay", false);
    CONFIG_VALUE(HidePromo, bool, "HidePromo", true);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(Resolution);
        CONFIG_INIT_VALUE(RefreshRate);
        CONFIG_INIT_VALUE(EnhancedFakeGlow);
        CONFIG_INIT_VALUE(Smoke);
        CONFIG_INIT_VALUE(FpsCounter);
        CONFIG_INIT_VALUE(BloomFogIntensity);
        CONFIG_INIT_VALUE(HideHowToPlay);
        CONFIG_INIT_VALUE(HidePromo);
    )
)