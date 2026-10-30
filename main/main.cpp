// Rubido for the Gamebuino AKA, ported from Willems Davy's GP2X version (main.cpp there).
//
// The game is the GP2X one at its own 320x240, the size of the AKA's screen: the same title
// screen, difficulties, board and credits. What sat under it changed: SDL is gfx.*, SDL_mixer is
// sound.*, the GP2X buttons are input.*, and the files live in the RUBIDO folder on the SD card.
// The TV out screen position of the GP2X is gone. main.cpp is split up: its classes are a file
// each, its states are a file each and what they share is in gamefuncs.*.
//
// Keys: d-pad or joystick, A select / pick up and jump a peg, B drop the peg that is picked up,
// MENU back, L1/R1 the volume down and up. RUN + MENU held goes back to the launcher.

#include <stdlib.h>

#include "commonvars.h"
#include "gamefuncs.h"
#include "gfx.h"
#include "platform.h"
#include "sound.h"
#include "states.h"

static void Quit()
{
    HaltMusic();
    SaveSettings();
    ReturnToLoader();
}

static void Run()
{
    PlatformInit();
    GfxInit();
    MakeDataDirs();
    SoundInit();
    srand(GetTicks());
    LoadGraphics();
    LoadSettings();
    // Main game loop that loops untile the gamestate = GSQuit
    // and calls the procedure according to the gamestate.
    while (GameState != GSQuit)
    {
        switch(GameState)
        {
            case GSGame :
                Game();
                break;
            case GSTitleScreen:
                TitleScreen();
                break;
            case GSDifficultySelect:
                DifficultySelect();
                break;
            case GSCredits:
                Credits();
                break;
            default:
                break;
        }
    }
    Quit();
}

extern "C" void app_main(void)
{
    Run();
}
