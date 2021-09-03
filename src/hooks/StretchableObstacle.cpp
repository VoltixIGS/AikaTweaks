#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/StretchableObstacle.hpp"

MAKE_HOOK_MATCH(
    StretchableObstacle_SetSizeAndColor,
    &GlobalNamespace::StretchableObstacle::SetSizeAndColor,
    void,
    GlobalNamespace::StretchableObstacle* self,
    float width,
    float height,
    float length,
    UnityEngine::Color color
) {
    self->addColorMultiplier = getAikaTweaksConfig().ObstacleColorMultiplier.GetValue();

    StretchableObstacle_SetSizeAndColor(self, width, height, length, color);
}

void AikaTweaks::Hooks::StretchableObstacle() {
    INSTALL_HOOK(getLogger(), StretchableObstacle_SetSizeAndColor);
}