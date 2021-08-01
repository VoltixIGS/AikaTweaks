#include "AikaTweaks.hpp"
#include "AikaTweaksConfig.hpp"

#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/MusicPackPromoBanner.hpp"

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(
    MainMenuViewController_DidActivate,
    &MainMenuViewController::DidActivate,
    void,
    MainMenuViewController* self,
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    self->musicPackPromoBanner->get_gameObject()->SetActive(!getAikaTweaksConfig().HidePromo.GetValue());

    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

void AikaTweaks::Hooks::MainMenuViewController() {
    INSTALL_HOOK(getLogger(), MainMenuViewController_DidActivate);
}