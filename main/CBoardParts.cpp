#include <stdlib.h>

#include "CBoardParts.h"
#include "commonvars.h"

// ---------------------------------------------------------------------------- CBoardPart

CBoardPart::CBoardPart(const int PlayFieldXin,const int PlayFieldYin)
{
    PlayFieldX=PlayFieldXin; // Set the current playfield position
    PlayFieldY=PlayFieldYin;
    X=XOffSet + PlayFieldXin*TileWidth; //set the screen position (for drawing)
    Y=YOffSet + PlayFieldYin*TileHeight;
    Type=0; // type is 0
    Image = NULL;
    ParentList = 0;
    AnimPhase=0;
}

void CBoardPart::SetPosition(const int PlayFieldXin,const int PlayFieldYin)
{
    if ((PlayFieldXin >= 0) && (PlayFieldXin < NrOfCols) && (PlayFieldYin >= 0) && (PlayFieldYin < NrOfRows))
    {
        PlayFieldX=PlayFieldXin;
        PlayFieldY=PlayFieldYin;
        X=XOffSet + PlayFieldXin*TileWidth;
        Y=YOffSet + PlayFieldYin*TileHeight;
    }
}

void CBoardPart::Draw(Surface &Dst)
{
    if (Image)
    {
        Rect SrcRect;
        SrcRect.x = AnimPhase * TileWidth; // current frame * tilewidth is
        SrcRect.y = 0;
        SrcRect.w = TileWidth;
        SrcRect.h = TileHeight;
        BlitSurface(*Image,&SrcRect,Dst,X,Y); // blit it to the specified surface
    }
}

// ---------------------------------------------------------------------------- CPeg

CPeg::CPeg(const int PlayFieldXin,const int PlayFieldYin) : CBoardPart(PlayFieldXin,PlayFieldYin)
{
    Type = IDPeg; // Id, isn't actually used in the game but if u have diffrent boardparts, u can identify it by this
    Image = &IMG[IMGPeg]; // set the image
    AnimPhase = 0; // current frame = 0 (a red dot)
}

bool CPeg::CanMoveTo(const int PlayFieldXin,const int PlayFieldYin,bool erase)
{
    bool temp;
    temp = true;
    float Xi,Yi;
    int LowX,LowY;
    // if there isn't a boardpart on the specified location
    if (!(ParentList->GetPart(PlayFieldXin,PlayFieldYin)))
        return false;
    else
    // if the current frame isn't either a red peg or a blue peg
    if (!(AnimPhase <2))
        return false;
    else
    //if the place we wan't to move to is an empty peg (animphase = 6)
    if (ParentList->GetPart(PlayFieldXin,PlayFieldYin)->GetAnimPhase() == 6)
    {
        //calculate the diffrence between the 2 points as a float
        Xi = (float)abs(PlayFieldXin - PlayFieldX)/2;
        Yi = (float)abs(PlayFieldYin - PlayFieldY)/2;

        if((Difficulty == VeryHard ) || (Difficulty == Hard))
            // here we see if xi, or yi quals 1 io movement is vertical or horintal and
            // xi or yi is 1. if it isn't 1 this means the new position isn't
            // exactly 2 pegs further away
            temp = temp &&  (((Xi == 0) && (Yi == 1)) || ((Xi ==1) && (Yi == 0)));
        else
            // same as above except we add a diagonal
            temp = temp && (((Xi == 0) && (Yi == 1)) || ((Xi ==1) && (Yi == 0)) || ((Xi==1) && (Yi == 1)));
        if (temp)
        {
            // calculate the lowest X & Y coordinate
            // will be used to find the middle peg (io the one we jumped over)
            if (PlayFieldXin <= PlayFieldX)
                LowX = PlayFieldXin;
            else
                LowX = PlayFieldX;
            if (PlayFieldYin <= PlayFieldY)
                LowY = PlayFieldYin;
            else
                LowY = PlayFieldY;
            // if the middle peg doesn't exists
             if (!(ParentList->GetPart(LowX+(int)Xi,LowY+(int)Yi)))
                return false;
            else
            // If the middle peg is either a blue (will never happen) or a red peg
            if (ParentList->GetPart(LowX+(int)Xi,LowY+(int)Yi)->GetAnimPhase() < 2)
            {
                // simple hack to specify we want the middle peg to be emptied (animpahse = 6)
                // i did this so i didn't need to do the above calcultions again in Game()
                if (erase)
                    ParentList->GetPart(LowX+(int)Xi,LowY+(int)Yi)->SetAnimPhase(6);
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

// ---------------------------------------------------------------------------- CBoardParts

//constructor of boardparts, we start with 0 items
CBoardParts::CBoardParts()
{
	ItemCount = 0;
}

// returns a boardpart if it's found with the same coordinate otherwise return null
CBoardPart* CBoardParts::GetPart(const int PlayFieldXin,const int PlayFieldYin)
{
    int Teller;
    for (Teller=0;Teller < ItemCount;Teller++)
        if((Items[Teller]->GetPlayFieldX() == PlayFieldXin) && (Items[Teller]->GetPlayFieldY() == PlayFieldYin))
            return Items[Teller];
    return NULL;
}

// Remove all board parts
void CBoardParts::RemoveAll()
{
	int Teller;
	for (Teller=0;Teller<ItemCount;Teller++)
	{
		delete Items[Teller];
		Items[Teller] = NULL;
	}
	ItemCount=0;
}

// Add a partboart, and set the boardparts parentlist to this (class/instance)
void CBoardParts::Add(CBoardPart *BoardPart)
{
	if( ItemCount < NrOfRows*NrOfCols*3 )
	{
		BoardPart->ParentList = this;
		Items[ItemCount] = BoardPart;
		ItemCount++;
	}
}

// draw all boarparts
void CBoardParts::Draw(Surface &Dst)
{
	int Teller;
	for (Teller=0;Teller<ItemCount;Teller++)
		Items[Teller]->Draw(Dst);
}

// destuctor does the same as remove all
CBoardParts::~CBoardParts()
{
	RemoveAll();
}
