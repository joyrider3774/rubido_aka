// The game's globals, the ones every state of main.cpp shared
#ifndef COMMONVARS_H
#define COMMONVARS_H

#include "CBoardParts.h"
#include "Common.h"

extern SDifficulty Difficulty;
extern CBoardParts BoardParts; // boardparts instance that will hold all the boardparts
extern GameStates GameState; // the game state
extern int Moves,Volume;
extern int BestPegsLeft[4]; // array that holds the best amount of pegs left for each difficulty

#endif
