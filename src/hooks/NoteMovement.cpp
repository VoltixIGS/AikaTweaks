#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/NoteMovement.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

MAKE_HOOK_MATCH(
    NoteMovement_Init,
    &NoteMovement::Init,
    void,
    NoteMovement* self,
    float beatTime,
    float worldRotation,
    Vector3 moveStartPos,
    Vector3 moveEndPos,
    Vector3 jumpEndPos,
    float moveDuration,
    float jumpDuration,
    float jumpGravity,
    float flipYSide,
    float endRotation
) {
    if (getAikaTweaksConfig().FeetSaber.GetValue()) {
        // TODO: Allow these values to be changed in the future.
        moveStartPos.y = 0.12f;
        moveEndPos.y = 0.12f;
        jumpEndPos.y = 0.12f;
    }

    NoteMovement_Init(self, beatTime, worldRotation, moveStartPos, moveEndPos, jumpEndPos, moveDuration, jumpDuration, jumpGravity, flipYSide, endRotation);
}

void AikaTweaks::Hooks::NoteMovement() {
    INSTALL_HOOK(getLogger(), NoteMovement_Init);
}