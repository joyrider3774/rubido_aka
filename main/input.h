// The GP2X buttons of the game on the AKA's keys.
//
// The game acted on a button when it went down (SDL_JOYBUTTONDOWN). ReadButtons sets one But*
// flag for each key that went down since the last call, keeping the GP2X layout:
//   d-pad / joystick  ButLeft, ButRight, ButUp, ButDown
//   A                 ButA         select, pick up and jump a peg (the GP2X's A and START)
//   B                 ButX         drop the peg that is picked up (the GP2X's X)
//   MENU              ButSelect    back (the GP2X's SELECT)
//   L1 / R1           ButVolDown, ButVolUp
#ifndef INPUT_H
#define INPUT_H

extern bool ButLeft, ButRight, ButUp, ButDown, ButA, ButX, ButSelect, ButVolDown, ButVolUp;

// sets the But* flags of the keys that went down since the last call, true when any did
bool ReadButtons();

#endif
