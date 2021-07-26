#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(AikaTweaksConfig,
    CONFIG_VALUE(Resolution, float, "Resolution", 1.0f);
    CONFIG_VALUE(RefreshRate, float, "RefreshRate", -1.0f); // We don't know the Refresh Rate, at this time.
    CONFIG_VALUE(Smoke, bool, "Smoke", false);
    CONFIG_VALUE(BurnMarks, bool, "BurnMarks", true);
    CONFIG_VALUE(FpsCounter, bool, "FpsCounter", true);
    CONFIG_VALUE(BloomFogIntensity, float, "BloomFogIntensity", 1.0f);
    CONFIG_VALUE(DebrisOldschool, bool, "DebrisOldschool", true);
    CONFIG_VALUE(FeetSaber, bool, "FeetSaber", false);
    CONFIG_VALUE(HideSolo, bool, "HideSolo", false);
    CONFIG_VALUE(HideParty, bool, "HideParty", false);
    CONFIG_VALUE(HideCampaign, bool, "HideCampaign", false);
    CONFIG_VALUE(HideQuit, bool, "HideQuit", false);
    CONFIG_VALUE(HideMultiplayer, bool, "HideMultiplayer", false);
    CONFIG_VALUE(HideHowToPlay, bool, "HideHowToPlay", false);
    CONFIG_VALUE(HidePromo, bool, "HidePromo", true);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(Resolution);
        CONFIG_INIT_VALUE(RefreshRate);
        CONFIG_INIT_VALUE(Smoke);
        CONFIG_INIT_VALUE(BurnMarks);
        CONFIG_INIT_VALUE(FpsCounter);
        CONFIG_INIT_VALUE(BloomFogIntensity);
        CONFIG_INIT_VALUE(DebrisOldschool);
        CONFIG_INIT_VALUE(FeetSaber);
        CONFIG_INIT_VALUE(HideSolo);
        CONFIG_INIT_VALUE(HideParty);
        CONFIG_INIT_VALUE(HideCampaign);
        CONFIG_INIT_VALUE(HideQuit);
        CONFIG_INIT_VALUE(HideMultiplayer);
        CONFIG_INIT_VALUE(HideHowToPlay);
        CONFIG_INIT_VALUE(HidePromo);
    )
)