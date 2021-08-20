#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/BoolSO.hpp"
#include "GlobalNamespace/FloatSO.hpp"
#include "GlobalNamespace/IntSO.hpp"
#include "GlobalNamespace/MainSettingsModelSO.hpp"

MAKE_HOOK_MATCH(
    MainSettingsModelSO_Load,
    &GlobalNamespace::MainSettingsModelSO::Load,
    void,
    GlobalNamespace::MainSettingsModelSO* self,
    bool forced
) {
    MainSettingsModelSO_Load(self, forced);
    
    self->vrResolutionScale->set_value(getAikaTweaksConfig().Resolution.GetValue());
    self->antiAliasingLevel->set_value(getAikaTweaksConfig().AntiAliasing.GetValue());
    self->smokeGraphicsSettings->set_value(getAikaTweaksConfig().Smoke.GetValue());
    self->mainEffectGraphicsSettings->set_value(getAikaTweaksConfig().Bloom.GetValue() ? 1 : 0);
    self->depthTextureEnabled->set_value(false); // We never want the depth texture enabled, anyways.
}

void AikaTweaks::Hooks::MainSettingsModelSO() {
    INSTALL_HOOK(getLogger(), MainSettingsModelSO_Load);
}