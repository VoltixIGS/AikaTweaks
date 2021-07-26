#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/BoolSO.hpp"
#include "GlobalNamespace/FloatSO.hpp"
#include "GlobalNamespace/MainSettingsModelSO.hpp"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(
    MainSettingsModelSO_Load,
    &MainSettingsModelSO::Load,
    void,
    MainSettingsModelSO* self,
    bool forced
) {
    MainSettingsModelSO_Load(self, forced);
    
    self->vrResolutionScale->set_value(getAikaTweaksConfig().Resolution.GetValue());
    self->smokeGraphicsSettings->set_value(getAikaTweaksConfig().Smoke.GetValue());
    self->burnMarkTrailsEnabled->set_value(getAikaTweaksConfig().BurnMarks.GetValue());
    self->depthTextureEnabled->set_value(false); // We never want the depth texture enabled, anyways.
}

void AikaTweaks::Hooks::MainSettingsModelSO() {
    INSTALL_HOOK(getLogger(), MainSettingsModelSO_Load);
}