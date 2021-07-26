#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include <map>

#include "GlobalNamespace/TubeBloomPrePassLight.hpp"

using namespace GlobalNamespace;

inline std::map<TubeBloomPrePassLight*, float> originalBloomFogIntensityMultipliers;

MAKE_HOOK_MATCH(
    TubeBloomPrePassLight_OnEnable,
    &TubeBloomPrePassLight::OnEnable,
    void,
    TubeBloomPrePassLight* self
) {
    if (originalBloomFogIntensityMultipliers.find(self) == originalBloomFogIntensityMultipliers.end()) {
        originalBloomFogIntensityMultipliers[self] = self->bloomFogIntensityMultiplier;
    }

    self->bloomFogIntensityMultiplier = originalBloomFogIntensityMultipliers[self] * getAikaTweaksConfig().BloomFogIntensity.GetValue();

    TubeBloomPrePassLight_OnEnable(self);
}

void AikaTweaks::Hooks::TubeBloomPrePassLight() {
    INSTALL_HOOK(getLogger(), TubeBloomPrePassLight_OnEnable);
}