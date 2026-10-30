// What the states have in common: the images, volume, settings, music and the board's rules
#ifndef GAMEFUNCS_H
#define GAMEFUNCS_H

// the images, from the firmware
void LoadGraphics();
void IncVolume();
void DecVolume();
// the volume and the best pegs left of each difficulty, in DATA_DIR/settings.dat
void LoadSettings();
void SaveSettings();
// the music plays all the time, over and over (Mix_PlayMusic(Music,-1))
void KeepMusicPlaying();
// the volume buttons every screen had
void VolumeButtons();
// how many moves are possible in the current board state
int MovesLeft();
// how many pegs are left on the board
int PegsLeft();
// the initial board state, a cross of pegs with the middle one empty
void InitBoard();
// whether we won the game
bool IsWinningGame();
// draws the board, its info and a boxed message over the playfield and waits till A is pressed
void PrintForm(const char *msg);

#endif
