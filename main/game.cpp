#include <stdio.h>

#include "CSelector.h"
#include "commonvars.h"
#include "gamefuncs.h"
#include "gfx.h"
#include "input.h"
#include "platform.h"
#include "sound.h"
#include "states.h"

// The main Game Loop
void Game()
{
    Color Color1 = {0,0,0};
    CSelector *Selector;
    Selector = new CSelector(4,4);
    char Msg[300];
    InitBoard();
    Moves = 0;
    PlaySound(SND_START);
    while (GameState == GSGame)
    {
        KeepMusicPlaying();
        BlitSurface(IMG[IMGBackground],NULL,Buffer,0,0);

        // Write some info to the screen
        snprintf(Msg,sizeof(Msg),"Moves Left:%d",MovesLeft());
        WriteText(Buffer,font,Msg,242,37,0,Color1);
        snprintf(Msg,sizeof(Msg),"Moves:%d",Moves);
        WriteText(Buffer,font,Msg,242,53,0,Color1);
        snprintf(Msg,sizeof(Msg),"Pegs Left:%d",PegsLeft());
        WriteText(Buffer,font,Msg,242,69,0,Color1);
        // Only show best pegs if it isn't 0
        if (BestPegsLeft[Difficulty] != 0)
        {
            snprintf(Msg,sizeof(Msg),"Best Pegs:%d",BestPegsLeft[Difficulty]);
            WriteText(Buffer,font,Msg,242,85,0,Color1);
        }
        BoardParts.Draw(Buffer);
        Selector->Draw(Buffer);
        PresentBuffer(255);
        FramerateDelay();

        ReadButtons();
        VolumeButtons();
        if (ButLeft) // move the selector to the left io currentposition.x - 1
            Selector->SetPosition(Selector->GetPosition().X -1,Selector->GetPosition().Y);
        if (ButRight)
            Selector->SetPosition(Selector->GetPosition().X +1,Selector->GetPosition().Y);
        if (ButUp)
            Selector->SetPosition(Selector->GetPosition().X,Selector->GetPosition().Y-1);
        if (ButDown)
            Selector->SetPosition(Selector->GetPosition().X,Selector->GetPosition().Y+1);
        if (ButX) // deselect selection
        {
            if (Selector->HasSelection)
            {
                BoardParts.GetPart(Selector->GetSelection().X,Selector->GetSelection().Y)->SetAnimPhase(0);
                Selector->DeSelect();
            }
        }
        if (ButSelect) // select = quit to title
        {
            HaltSounds();
            GameState = GSTitleScreen;
        }
        if (ButA)
        {
            if (Selector->HasSelection) // if we have a selection
            {
                // see if the selected boardpart can move to the current position
                if (BoardParts.GetPart(Selector->GetSelection().X,Selector->GetSelection().Y)->CanMoveTo(Selector->GetPosition().X,Selector->GetPosition().Y,true))
                {
                    PlaySound(SND_GOOD);
                    //if so play a sound, increase the moves, set the selected part to empty and the current part to red
                    Moves++;
                    BoardParts.GetPart(Selector->GetSelection().X,Selector->GetSelection().Y)->SetAnimPhase(6);
                    BoardParts.GetPart(Selector->GetPosition().X,Selector->GetPosition().Y)->SetAnimPhase(0);
                    // if no moves are left see if the best pegs left value for the current difficulty is
                    // greater if so set te new value
                    if (MovesLeft() == 0)
                    {
                        if (BestPegsLeft[Difficulty] != 0)
                        {
                            if (PegsLeft() < BestPegsLeft[Difficulty])
                                BestPegsLeft[Difficulty] = PegsLeft();
                        }
                        else
                            BestPegsLeft[Difficulty] = PegsLeft();
                        // the GP2X wrote this when it quit, the AKA is just switched off
                        SaveSettings();
                        // if it's the winning game play the winning sound and show the form with the winning message
                        if (IsWinningGame())
                        {
                            PlaySound(SND_WINNER);
                            PrintForm("Congratulations you have solved\nthe puzzle! Try a new difficulty!\n\nPress (A) to continue");// this will not return until A has been pressed
                            GameState=GSTitleScreen;
                        }
                        else // show the loser messager, play loser sound
                        {
                            PlaySound(SND_LOSER);
                            PrintForm("You couldn't solve the puzzle!\nDon't give up, try it again!\n\nPress (A) to continue"); // this will not return until A has been pressed
                            GameState=GSTitleScreen;
                        }
                        // stop the sounds
                        HaltSounds();
                    }
                }
                else // if we can't move to the spot, play the wrong move sound, and reset the selection to a red peg (instead of blue / selected)
                {
                    BoardParts.GetPart(Selector->GetSelection().X,Selector->GetSelection().Y)->SetAnimPhase(0);
                    PlaySound(SND_WRONG);
                }
                Selector->DeSelect(); // deselect the selection
            }
            else // we didn't have a selection, set the new selection
            {
                if (BoardParts.GetPart(Selector->GetPosition().X,Selector->GetPosition().Y)->GetAnimPhase() == 0)
                {
                    PlaySound(SND_SELECT);
                    BoardParts.GetPart(Selector->GetPosition().X,Selector->GetPosition().Y)->SetAnimPhase(1);
                    Selector->Select();
                }
            }
        }
    }
    // when the game has finished we remove all board parts
    BoardParts.RemoveAll();
    delete Selector;
}
