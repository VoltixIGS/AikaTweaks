#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/NoteJump.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

MAKE_HOOK_MATCH(
    NoteJump_ManualUpdate,
    &NoteJump::ManualUpdate,
    Vector3,
    NoteJump* self
) {
    Vector3 result = NoteJump_ManualUpdate(self);

    if (getAikaTweaksConfig().FeetSaber.GetValue()) {
        self->localPosition.y = 0.12f; // TODO: Allow this value to be changed in the future.
        result = self->worldRotation * self->localPosition;
        self->get_transform()->set_position(result);
    }

    return result;
}

void AikaTweaks::Hooks::NoteJump() {
    INSTALL_HOOK(getLogger(), NoteJump_ManualUpdate);
}