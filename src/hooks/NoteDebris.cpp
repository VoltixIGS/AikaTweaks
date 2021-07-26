#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/ColorType.hpp"
#include "GlobalNamespace/NoteDebris.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

MAKE_HOOK_MATCH(
    NoteDebris_Init,
    &NoteDebris::Init,
    void,
    NoteDebris* self,
    ColorType colorType,
    Vector3 notePos,
    Quaternion noteRot,
    Vector3 noteMoveVec,
    Vector3 noteScale,
    Vector3 positionOffset,
    Quaternion rotationOffset,
    Vector3 cutPoint,
    Vector3 cutNormal,
    Vector3 force,
    Vector3 torque,
    float lifeTime
) {
    if (getAikaTweaksConfig().DebrisOldschool.GetValue()) {
        force.z = 0;
    }

    NoteDebris_Init(self, colorType, notePos, noteRot, noteMoveVec, noteScale, positionOffset, rotationOffset, cutPoint, cutNormal, force, torque, lifeTime);
}

void AikaTweaks::Hooks::NoteDebris() {
    INSTALL_HOOK(getLogger(), NoteDebris_Init);
}