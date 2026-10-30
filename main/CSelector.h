#ifndef CSELECTOR_H
#define CSELECTOR_H

#include "Common.h"
#include "gfx.h"

// Class for the selector, it will hold the previous selected coordinate of a peg and the current position
// of the board selector (the light blue square ingame)
class CSelector
{
    private:
        SPoint SelectedPoint,CurrentPoint; //variables to hold the current position and the selected position

    public:
        bool HasSelection;
        // constructor, parameters define the starting position
        CSelector(const int PlayFieldXin,const int PlayFieldYin);
        // Will set the position only if it layes within the board boundary
        void SetPosition(const int PlayFieldXin,const int PlayFieldYin);
        // Select will set the current position as the selected position
        void Select();
        // return the selected position
        SPoint GetSelection() { return SelectedPoint; }
        // return the current position
        SPoint GetPosition() { return CurrentPoint; }
        void DeSelect() { HasSelection = false; }
        // Draw the blue box on the current position, with the offsets in mind
        void Draw(Surface &Dst);
};

#endif
