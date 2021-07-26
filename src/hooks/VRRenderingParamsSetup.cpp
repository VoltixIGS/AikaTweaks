#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/BoolSO.hpp"
#include "GlobalNamespace/FloatSO.hpp"
#include "GlobalNamespace/IVRPlatformHelper.hpp"
#include "GlobalNamespace/OVRManager.hpp"
#include "GlobalNamespace/OVRManager_FixedFoveatedRenderingLevel.hpp"
#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_ColorSpace.hpp"
#include "GlobalNamespace/VRPlatformSDK.hpp"
#include "GlobalNamespace/VRRenderingParamsSetup.hpp"
#include "UnityEngine/Mathf.hpp"
#include "UnityEngine/XR/XRSettings.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace UnityEngine::XR;

inline VRRenderingParamsSetup* vrRenderingParamsSetup;

MAKE_HOOK_MATCH(
    VRRenderingParamsSetup_OnEnable,
    &VRRenderingParamsSetup::OnEnable,
    void,
    VRRenderingParamsSetup* self
) {
    vrRenderingParamsSetup = self;

    AikaTweaks::VRRenderingParamsSetup::Refresh();
}

void AikaTweaks::VRRenderingParamsSetup::Refresh() {
    if (vrRenderingParamsSetup->vrResolutionScale->get_value() == 0.0f) {
        vrRenderingParamsSetup->vrResolutionScale->set_value(1.0f);
    }

    if (vrRenderingParamsSetup->menuVRResolutionScaleMultiplier->get_value() == 0.0f) {
        vrRenderingParamsSetup->menuVRResolutionScaleMultiplier->set_value(1.0f);
    }

    XRSettings::set_eyeTextureResolutionScale(vrRenderingParamsSetup->vrResolutionScale->get_value() * (vrRenderingParamsSetup->sceneType == GlobalNamespace::VRRenderingParamsSetup::SceneType::Menu ? vrRenderingParamsSetup->menuVRResolutionScaleMultiplier->get_value() : 1.0f));

    if (vrRenderingParamsSetup->vrPlatformHelper->get_vrPlatformSDK() != VRPlatformSDK::Oculus) {
        return;
    }

    if (OVRManager::get_fixedFoveatedRenderingSupported()) {
        OVRManager::set_fixedFoveatedRenderingLevel(!vrRenderingParamsSetup->useFixedFoveatedRenderingDuringGameplay->get_value() ||
            vrRenderingParamsSetup->sceneType != GlobalNamespace::VRRenderingParamsSetup::SceneType::Game ? OVRManager_FixedFoveatedRenderingLevel::Off : OVRManager_FixedFoveatedRenderingLevel::HighTop);
    }

    OVRPlugin::SetClientColorDesc(OVRPlugin::ColorSpace::Rift_CV1);

    // Check if our (default) refresh rate has been set.
    float refreshRate = getAikaTweaksConfig().RefreshRate.GetValue();
    if (refreshRate == -1.0f) {
        refreshRate = Mathf::Max(OVRPlugin::get_systemDisplayFrequenciesAvailable());
        getAikaTweaksConfig().RefreshRate.SetValue(refreshRate);
    }

    OVRPlugin::set_systemDisplayFrequency(refreshRate);
}

void AikaTweaks::Hooks::VRRenderingParamsSetup() {
    INSTALL_HOOK(getLogger(), VRRenderingParamsSetup_OnEnable);
}