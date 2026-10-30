#include "commonvars.h"
#include "gamefuncs.h"
#include "gfx.h"
#include "input.h"
#include "platform.h"
#include "states.h"

//Main Credits loop, will just show an image and wait for a button to be pressed
void Credits()
{
    while (GameState == GSCredits)
    {
        KeepMusicPlaying();
        // any button but the volume ones goes back to the title screen
        if (ReadButtons())
        {
            if (ButVolUp || ButVolDown)
                VolumeButtons();
            else
                GameState = GSTitleScreen;
        }
        BlitSurface(IMG[IMGCredits],NULL,Buffer,0,0);
        PresentBuffer(255);
        FramerateDelay();
    }
}
