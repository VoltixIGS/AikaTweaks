#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/TubeBloomPrePassLight.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp"

SafePtr<System::Collections::Generic::Dictionary_2<GlobalNamespace::TubeBloomPrePassLight*, float>> originalBloomFogIntensityMultipliers;

MAKE_HOOK_MATCH(
    TubeBloomPrePassLight_OnEnable,
    &GlobalNamespace::TubeBloomPrePassLight::OnEnable,
    void,
    GlobalNamespace::TubeBloomPrePassLight* self
) {
    using namespace System::Collections::Generic;

    if (!originalBloomFogIntensityMultipliers) {
        originalBloomFogIntensityMultipliers = Dictionary_2<GlobalNamespace::TubeBloomPrePassLight*, float>::New_ctor();
    }
    if (!originalBloomFogIntensityMultipliers->ContainsKey(self)) {
        originalBloomFogIntensityMultipliers->set_Item(self, self->bloomFogIntensityMultiplier);
    }

    self->bloomFogIntensityMultiplier = originalBloomFogIntensityMultipliers->get_Item(self) * getAikaTweaksConfig().BloomFogIntensity.GetValue();

    TubeBloomPrePassLight_OnEnable(self);
}

void AikaTweaks::Hooks::TubeBloomPrePassLight() {
    INSTALL_HOOK(getLogger(), TubeBloomPrePassLight_OnEnable);
}