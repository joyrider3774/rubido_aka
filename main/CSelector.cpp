#include "CSelector.h"

CSelector::CSelector(const int PlayFieldXin,const int PlayFieldYin)
{
    SelectedPoint.X = 0; // there's no selection set it 0
    SelectedPoint.Y = 0;
    CurrentPoint.X = PlayFieldXin; // set current position
    CurrentPoint.Y = PlayFieldYin;
    HasSelection = false; // No selection when it's created
}

void CSelector::SetPosition(const int PlayFieldXin,const int PlayFieldYin)
{
    // check if the new position is inside the board, if so set the new position as the currentposition
    if (((PlayFieldYin>=0) && (PlayFieldYin < 3) && (PlayFieldXin > 2) && (PlayFieldXin < 6)) ||
        ((PlayFieldYin > 2) && (PlayFieldYin<6) && (PlayFieldXin >=0) && (PlayFieldXin <NrOfCols)) ||
        ((PlayFieldYin > 5)&& (PlayFieldYin < NrOfRows) && (PlayFieldXin > 2) && (PlayFieldXin <6)))
        {
            CurrentPoint.X = PlayFieldXin;
            CurrentPoint.Y = PlayFieldYin;
        }
}

void CSelector::Select()
{
    SelectedPoint.X = CurrentPoint.X;
    SelectedPoint.Y = CurrentPoint.Y;
    HasSelection = true;
}

void CSelector::Draw(Surface &Dst)
{
    BoxRGBA(Dst, XOffSet + CurrentPoint.X * (TileWidth), YOffSet+ CurrentPoint.Y * (TileHeight), XOffSet-1 + (CurrentPoint.X +1)* (TileWidth ), YOffSet-1+ (CurrentPoint.Y+1) * (TileHeight), 0, 0, 200, 125);
}
