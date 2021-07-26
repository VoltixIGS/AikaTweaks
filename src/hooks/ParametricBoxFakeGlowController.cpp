#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/ParametricBoxFakeGlowController.hpp"

#include <cmath>
#include <vector>

using namespace GlobalNamespace;

#define MIN 0.5f
#define X 13.5f

// Reimplementation of UnityEngine::Mathf::Min(float[]), isn't ideal but it works.
float Mathf_Min(std::vector<float> values) {
    float value = values[0];

    for (int i = 1; i < values.size(); i++) {
        value = fmin(value, values[i]);
    }

    return value;
}

MAKE_HOOK_MATCH(
    ParametricBoxFakeGlowController_Refresh,
    &ParametricBoxFakeGlowController::Refresh,
    void,
    ParametricBoxFakeGlowController* self
) {
    if (getAikaTweaksConfig().EnhancedFakeGlow.GetValue()) {
        float value = Mathf_Min({ self->width, self->height, self->length });

        self->edgeSizeMultiplier = fmin(self->edgeSizeMultiplier, fmax(MIN, value * X));
    }

    ParametricBoxFakeGlowController_Refresh(self);
}

void AikaTweaks::Hooks::ParametricBoxFakeGlowController() {
    INSTALL_HOOK(getLogger(), ParametricBoxFakeGlowController_Refresh);
}