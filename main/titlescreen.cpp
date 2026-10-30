#include "CMainMenu.h"
#include "commonvars.h"
#include "gamefuncs.h"
#include "gfx.h"
#include "input.h"
#include "platform.h"
#include "sound.h"
#include "states.h"

// main title screen loop
void TitleScreen()
{
    CMainMenu *Menu = new CMainMenu();
    while (GameState == GSTitleScreen)
    {
        // the music plays in an endless loop
        KeepMusicPlaying();
        ReadButtons();
        VolumeButtons();
        if (ButDown)
            Menu->NextItem();
        if (ButUp)
            Menu->PreviousItem();
        if (ButA)
        {
            // set the gamestate according to the menu selection
            PlaySound(SND_GOOD);
            switch(Menu->GetSelection())
            {
                case 1:
                    GameState = GSDifficultySelect;
                    break;
                case 2:
                    GameState = GSCredits;
                    break;
                case 3:
                    GameState = GSQuit;
            }
        }
        Menu->Draw(Buffer);
        PresentBuffer(255);
        FramerateDelay();
    }
    delete Menu;
}
