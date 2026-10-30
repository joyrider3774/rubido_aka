#include "commonvars.h"
#include "gamefuncs.h"
#include "gfx.h"
#include "input.h"
#include "platform.h"
#include "states.h"

// Main difficulty select loop
void DifficultySelect()
{
    while (GameState == GSDifficultySelect)
    {
        KeepMusicPlaying();
        ReadButtons();
        VolumeButtons();
        if (ButSelect)
            GameState = GSTitleScreen;
        if (ButA)
            GameState = GSGame;
        if (ButLeft) // Change difficluly one lower if we pressed left
        {
            if(Difficulty == VeryHard)
                Difficulty = Hard;
            else if(Difficulty == Hard)
                Difficulty = Easy;
            else if(Difficulty == Easy)
                Difficulty = VeryEasy;
            else if(Difficulty == VeryEasy)
                Difficulty = VeryHard;
        }
        if (ButRight) // change difficulty one higher
        {
            if(Difficulty == VeryEasy)
                Difficulty = Easy;
            else if(Difficulty == Easy)
                Difficulty = Hard;
            else if(Difficulty == Hard)
                Difficulty = VeryHard;
            else if(Difficulty == VeryHard)
                Difficulty = VeryEasy;
        }

        // decide what we draw to the buffer based on the difficuly: its information and its name
        // in the middle at the top
        static const int Info[4] = {IMGVeryEasyInfo, IMGEasyInfo, IMGHardInfo, IMGVeryHardInfo};
        static const int Name[4] = {IMGVeryEasy1, IMGEasy1, IMGHard1, IMGVeryHard1};
        BlitSurface(IMG[Info[Difficulty]],NULL,Buffer,0,0);
        BlitSurface(IMG[Name[Difficulty]],NULL,Buffer,Buffer.w/2 - IMG[Name[Difficulty]].w/2,35);
        PresentBuffer(255);
        FramerateDelay();
    }
}
