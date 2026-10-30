#ifndef COMMON_H
#define COMMON_H

#include "gfx.h"

//the constants used in the game
const int NrOfRows = 9, // how many rows and columns of board parts (pegs) there could be, it's
		  NrOfCols = 9, // acutally to much but it's easier to use this as u'll see in the code
		  TileWidth = 24, // height and with af the board peg tile
		  TileHeight =24,
		  IDPeg = 1,
          XOffSet = 10, //offset where to start drawing the board tiles
          YOffSet = 11,
		  NrOfSounds=6, // Nr of sounds and sound identifiers.
		  SND_SELECT=0,
		  SND_GOOD=1,
		  SND_WRONG=2,
		  SND_START=3,
		  SND_WINNER=4,
		  SND_LOSER=5;

// The diffrent gameStates possible in the game
enum GameStates {GSQuit,GSGame,GSTitleScreen,GSDifficultySelect,GSCredits};

// The diffrent difficultys
enum SDifficulty {VeryEasy=0,Easy=1,Hard=2,VeryHard=3};

// the images, in the order of ASSET_IMAGE_NAMES (tools/convert_assets.py)
enum Images {
    IMGBackground, IMGPeg, IMGTitle, IMGNewGame1, IMGNewGame2, IMGCredits1, IMGCredits2,
    IMGQuit1, IMGQuit2, IMGVeryEasyInfo, IMGEasyInfo, IMGHardInfo, IMGVeryHardInfo,
    IMGVeryEasy1, IMGEasy1, IMGHard1, IMGVeryHard1, IMGCredits, NrOfImages
};

// the images, built into the firmware
extern Surface IMG[NrOfImages];

// A struct that holds x & y coordinate
struct SPoint
{
    int X,Y;
};

#endif
