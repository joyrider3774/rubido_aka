#include "CMainMenu.h"
#include "Common.h"
#include "sound.h"

// constructor of main menu will set the current selection to 1 (io newgame)
CMainMenu::CMainMenu()
{
    Selection = 1;
}

// Increase the selection if it goes to far set i to the first selection
void CMainMenu::NextItem()
{
    Selection++;
    if (Selection == 4)
        Selection = 1;
    PlaySound(SND_SELECT);
}

// decrease the selection if it goes to low set it to the last selection
void CMainMenu::PreviousItem()
{
    Selection--;
    if (Selection == 0)
        Selection = 3;
    PlaySound(SND_SELECT);
}

// Draw the main menu
void CMainMenu::Draw(Surface &Dst)
{
    // draw the title screen background
    BlitSurface(IMG[IMGTitle],NULL,Dst,0,0);
    // the selected entry purple, the others blue, in the middle of the screen
    const Surface &NewGame = IMG[Selection == 1 ? IMGNewGame1 : IMGNewGame2];
    BlitSurface(NewGame,NULL,Dst,Dst.w/2 - NewGame.w/2,77);
    const Surface &Credits = IMG[Selection == 2 ? IMGCredits1 : IMGCredits2];
    BlitSurface(Credits,NULL,Dst,Dst.w/2 - Credits.w/2,115);
    const Surface &Quit = IMG[Selection == 3 ? IMGQuit1 : IMGQuit2];
    BlitSurface(Quit,NULL,Dst,Dst.w/2 - Quit.w/2,155);
}
