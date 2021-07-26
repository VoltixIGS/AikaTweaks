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
    self->soloButton->get_gameObject()->SetActive(!getAikaTweaksConfig().HideSolo.GetValue());
    self->partyButton->get_gameObject()->SetActive(!getAikaTweaksConfig().HideParty.GetValue());
    self->campaignButton->get_gameObject()->SetActive(!getAikaTweaksConfig().HideCampaign.GetValue());
    self->quitButton->get_gameObject()->SetActive(!getAikaTweaksConfig().HideQuit.GetValue());
    self->multiplayerButton->get_gameObject()->SetActive(!getAikaTweaksConfig().HideMultiplayer.GetValue());
    self->howToPlayButton->get_gameObject()->SetActive(!getAikaTweaksConfig().HideHowToPlay.GetValue());
    self->musicPackPromoBanner->get_gameObject()->SetActive(!getAikaTweaksConfig().HidePromo.GetValue());

    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

void AikaTweaks::Hooks::MainMenuViewController() {
    INSTALL_HOOK(getLogger(), MainMenuViewController_DidActivate);
}