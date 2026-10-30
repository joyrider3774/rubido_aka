# Rubido for the Gamebuino AKA

A port of the GP2X version of Rubido to the Gamebuino AKA. Rubido is peg solitaire: jump a peg
over its neighbour into an empty hole to take the neighbour off the board, until only one peg is
left. Four difficulties:

| Difficulty | Moves | The last peg |
|---|---|---|
| Very easy | horizontal, vertical and diagonal | anywhere |
| Easy | horizontal, vertical and diagonal | in the middle |
| Hard | horizontal and vertical | anywhere |
| Very hard | horizontal and vertical | in the middle |

The game remembers the fewest pegs you were left with on each difficulty. The graphics, sounds
and music are the GP2X version's, at the same 320x240 the AKA's screen has.

## Controls

| AKA | Action |
|---|---|
| D-pad / joystick | move in the menus, move the cursor; left / right change the difficulty |
| A | select; pick up a peg, then jump it to an empty hole |
| B | put the peg you picked up back down |
| MENU | back |
| L1 / R1 | volume down / up |

**Quit** in the main menu, or **RUN + MENU** held for half a second anywhere in the game, goes back
to the launcher; RUN on its own switches the AKA off as in every game.

## Installing

Copy the `SD_files/RUBIDO` folder to the root of the SD card and start Rubido from the launcher.
The folder holds `firmware.bin`, `meta.json`, `screen.bmp`, the music and the `LICENSE`. The game
writes its volume and best results to `settings.dat` there.

## Building

ESP-IDF 5.5 and the official [Gamebuino AKA library](https://github.com/jmp42/Gamebuino_AKA_lib),
which is used where it is checked out (`C:/github/Gamebuino_AKA_lib` by default, or set
`AKA_LIB_DIR`):

```
idf.py set-target esp32s3
idf.py build
```

`build/rubido.bin` is copied to `SD_files/RUBIDO/firmware.bin` by the build.

The graphics, font, sounds and music are the GP2X version's original files in `assets/`,
converted by `tools/convert_assets.py` (Pillow, and ffmpeg for the music):

```
python tools/convert_assets.py <ffmpeg>
```

It writes `main/assets/assets.bin` (the images, the font and the sounds, built into the firmware)
and the SD card folder's music and `screen.bmp`.

## Source layout

The GP2X version was a single `main.cpp`, split up here:

| File | What it is |
|---|---|
| `main/main.cpp` | start up and the state loop |
| `main/titlescreen.cpp`, `difficultyselect.cpp`, `credits.cpp`, `game.cpp` | one file per game state |
| `main/CBoardParts.cpp` | the pegs and the rules of a jump |
| `main/CSelector.cpp`, `CMainMenu.cpp` | the cursor and the main menu |
| `main/gamefuncs.cpp`, `commonvars.cpp` | what the states share: volume, settings, music, the board, the globals |
| `main/gfx.cpp`, `sound.cpp`, `input.cpp`, `platform.cpp` | what SDL did on the GP2X, on the AKA library |

## Credits

Rubido by Willems Davy (Willems Soft).

## License

MIT, see [LICENSE](LICENSE).
