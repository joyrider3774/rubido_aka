#include "gamefuncs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assets.h"
#include "commonvars.h"
#include "gfx.h"
#include "input.h"
#include "platform.h"
#include "sound.h"

// the images, in the order of the Images enum
static const AssetSurface *const Images[NrOfImages] = {
    &ASSET_BACKGROUND, &ASSET_PEG, &ASSET_TITLESCREEN, &ASSET_NEWGAME1, &ASSET_NEWGAME2,
    &ASSET_CREDITS1, &ASSET_CREDITS2, &ASSET_QUIT1, &ASSET_QUIT2, &ASSET_INFOVERYEASY,
    &ASSET_INFOEASY, &ASSET_INFOHARD, &ASSET_INFOVERYHARD, &ASSET_VERYEASY1, &ASSET_EASY1,
    &ASSET_HARD1, &ASSET_VERYHARD1, &ASSET_CREDITS};
static_assert(sizeof(ASSET_IMAGE_NAMES) / sizeof(ASSET_IMAGE_NAMES[0]) == NrOfImages,
              "the Images enum does not match tools/convert_assets.py");

void LoadGraphics()
{
    for (int Teller = 0; Teller < NrOfImages; Teller++)
        IMG[Teller] = SurfaceFromAsset(*Images[Teller]);
}

// increase the volume with 8
void IncVolume()
{
	if (Volume < 128)
	{
		Volume += 8;
		SetVolume(Volume);
		SaveSettings();
	}
}

// decrease the volume with 8
void DecVolume()
{
	if (Volume > 0)
	{
		Volume-= 8;
		SetVolume(Volume);
		SaveSettings();
	}
}

// Load the settings, if there isn't a settings file, set some initial values
void LoadSettings()
{
 	FILE *SettingsFile;
    Volume = 128;
    BestPegsLeft[VeryEasy] = 0;
    BestPegsLeft[Easy] = 0;
    BestPegsLeft[Hard] = 0;
    BestPegsLeft[VeryHard] = 0;
 	SettingsFile = fopen(DATA_DIR "/settings.dat","r");
 	if(SettingsFile)
 	{
		if ((fscanf(SettingsFile,"Volume=%d\n",&Volume) != 1) || (Volume < 0) || (Volume > 128))
		    Volume = 128;
		fscanf(SettingsFile,"Best0=%d\n",&BestPegsLeft[VeryEasy]);
		fscanf(SettingsFile,"Best1=%d\n",&BestPegsLeft[Easy]);
		fscanf(SettingsFile,"Best2=%d\n",&BestPegsLeft[Hard]);
		fscanf(SettingsFile,"Best3=%d\n",&BestPegsLeft[VeryHard]);
		fclose(SettingsFile);
		// a damaged file: 0 is no best result yet, the board has 44 pegs at the start
		for (int Teller = 0; Teller < 4; Teller++)
		    if ((BestPegsLeft[Teller] < 0) || (BestPegsLeft[Teller] > 44))
		        BestPegsLeft[Teller] = 0;
 	}
    SetVolume(Volume);
}

// Save the settings
void SaveSettings()
{
 	FILE *SettingsFile;
 	SettingsFile = fopen(DATA_DIR "/settings.dat","w");
 	if(SettingsFile)
 	{
		fprintf(SettingsFile,"Volume=%d\n",Volume);
		fprintf(SettingsFile,"Best0=%d\n",BestPegsLeft[VeryEasy]);
		fprintf(SettingsFile,"Best1=%d\n",BestPegsLeft[Easy]);
		fprintf(SettingsFile,"Best2=%d\n",BestPegsLeft[Hard]);
		fprintf(SettingsFile,"Best3=%d\n",BestPegsLeft[VeryHard]);
		fclose(SettingsFile);
 	}
}

void KeepMusicPlaying()
{
    if (!MusicPlaying())
        PlayMusic(0);
}

void VolumeButtons()
{
    if (ButVolUp)
        IncVolume();
    if (ButVolDown)
        DecVolume();
}

// procedure that calculates how many moves are possible in the current board state
// we can simply do this by checking all parts and see if they can move to all directions
// the canmoveto method in CPegs is does all the checking
int MovesLeft()
{
    CBoardPart *BoardPart ;
    int TmpMoves=0,Y,X;
    for (Y=0;Y<NrOfRows;Y++)
        for (X=0;X<NrOfCols;X++)
        {
            BoardPart = BoardParts.GetPart(X,Y);
            // if there is a boardpart on that X,Y Coordinate
            // check all direction if we can move to that if so increases the movesleft
            if (BoardPart)
            {
                if (BoardPart->CanMoveTo(X+2,Y,false))
                    TmpMoves++;
                if (BoardPart->CanMoveTo(X-2,Y,false))
                    TmpMoves++;
                if (BoardPart->CanMoveTo(X,Y-2,false))
                    TmpMoves++;
                if (BoardPart->CanMoveTo(X,Y+2,false))
                    TmpMoves++;
                if (BoardPart->CanMoveTo(X+2,Y-2,false))
                    TmpMoves++;
                if (BoardPart->CanMoveTo(X+2,Y+2,false))
                    TmpMoves++;
                if (BoardPart->CanMoveTo(X-2,Y+2,false))
                    TmpMoves++;
                if (BoardPart->CanMoveTo(X-2,Y-2,false))
                    TmpMoves++;
            }
        }
    return TmpMoves;
}

// Procedure that counts how many pegs are left on the board (animphase must be lower then 2 io a red or blue peg)
int PegsLeft()
{
    CBoardPart *BoardPart ;
    int Pegs=0,Y,X;
    for (Y=0;Y<NrOfRows;Y++)
        for (X=0;X<NrOfCols;X++)
        {
            BoardPart = BoardParts.GetPart(X,Y);
            if (BoardPart)
                if ((BoardPart->GetType() == IDPeg) && (BoardPart->GetAnimPhase() < 2))
                    Pegs++;
        }
    return Pegs;
}

// this will ceate the initial board state, io a cross of pegs, with the middle on being empty (=animphase 6)
void InitBoard()
{
    int X,Y;
    for (Y=0;Y < NrOfRows;Y++)
        for (X=0;X < NrOfCols;X++)
        {
            if ((Y < 3) && (X > 2) && (X < 6))
                BoardParts.Add(new CPeg(X,Y));
             if ((Y > 2) && (Y <6))
                BoardParts.Add(new CPeg(X,Y));
            if ((Y > 5) && (X > 2) && (X <6))
                BoardParts.Add(new CPeg(X,Y));
        }
     BoardParts.GetPart(4,4)->SetAnimPhase(6);
}

// Checks if we won the game
bool IsWinningGame()
{
    if (PegsLeft() == 1) //must be 1 peg left
    {
        if ((Difficulty == VeryHard) || (Difficulty == Easy))
        {
            if(BoardParts.GetPart(4,4)->GetAnimPhase() < 2) // must be in the middle with veryhard or easy
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

// procedure that draws the board, boardparts info and a boxed message over the playfield
// and waits till the A button is pressed
void PrintForm(const char *msg)
{
    char Msg[300];
    Color TextColor = {50,50,250};
    Color Color1 = {0,0,0};
	BlitSurface(IMG[IMGBackground],NULL,Buffer,0,0);
    snprintf(Msg,sizeof(Msg),"Moves Left:%d",MovesLeft());
    WriteText(Buffer,font,Msg,242,37,0,Color1);
    snprintf(Msg,sizeof(Msg),"Moves:%d",Moves);
    WriteText(Buffer,font,Msg,242,53,0,Color1);
    snprintf(Msg,sizeof(Msg),"Pegs Left:%d",PegsLeft());
    WriteText(Buffer,font,Msg,242,69,0,Color1);
    if (BestPegsLeft[Difficulty] != 0)
    {
        snprintf(Msg,sizeof(Msg),"Best Pegs:%d",BestPegsLeft[Difficulty]);
        WriteText(Buffer,font,Msg,242,85,0,Color1);
    }
	BoardParts.Draw(Buffer);
	BoxRGBA(Buffer,16,80,221,160,152,152,255,255);
	RectangleRGBA(Buffer,16,80,221,160,50,50,255,255);
	RectangleRGBA(Buffer,17,81,220,159,50,50,255,255);
	WriteText(Buffer,font,msg,21,85,2,TextColor);
    PresentBuffer(255);
    ReadButtons();
    do
    {
        KeepMusicPlaying();
        FramerateDelay();
        ReadButtons();
        VolumeButtons();
    } while (!ButA);
}
