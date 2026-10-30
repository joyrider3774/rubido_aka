// The pegs on the board: CBoardPart, CPeg (the only board part there is) and CBoardParts, the
// list that holds them
#ifndef CBOARDPARTS_H
#define CBOARDPARTS_H

#include "Common.h"
#include "gfx.h"

//define the Cboardpart class already since it will be used in the CBoardparts class, we will complete it later
class CBoardPart;

//Class that will hold all the current objects (pegs) on the board
class CBoardParts
{
 public:
 	CBoardPart *Items[NrOfRows*NrOfCols*3]; // array of Cboardparts
 	int ItemCount; //how many objects (pegs)
 	CBoardParts(); // constructor
 	void Add(CBoardPart *BoardPart); // Add a boardpart
 	void Draw(Surface &Dst); // Draw all boardparts
 	CBoardPart *GetPart(const int PlayFieldXin,const int PlayFieldYin); // return a boardpart given the coordinates
 	void RemoveAll(); // remove (free) all boardparts
	~CBoardParts();
};

//Base Class that defines a Cboardpart, it's only a peg
class CBoardPart
{
 protected:
 	int Type,X,Y,PlayFieldX,PlayFieldY,AnimPhase; //Animphase holds the current selected frame of the tile
 	Surface *Image;

 public:
 	CBoardParts *ParentList; // the parentlist, points to a CBoardParts class
 	CBoardPart(const int PlayFieldXin,const int PlayFieldYin); //Constructor, create a boardpart with the given location
 	int GetType() {return Type;}; // return the type
 	int GetX() {return X;} // get the screen x coordiante
 	int GetY() {return Y;} // get the screen y coordinate
 	int GetPlayFieldX() {return PlayFieldX;} // Get the playfield X coordinate
 	int GetPlayFieldY() {return PlayFieldY;} // Get The playfield Y Coordinate
 	int GetAnimPhase() {return AnimPhase;} // returns the current frame of the tile
 	void SetAnimPhase(int AnimPhaseIn) { AnimPhase = AnimPhaseIn;} // sets the current frame of the tile
 	void SetPosition(const int PlayFieldXin,const int PlayFieldYin); // change the position of the tile, it isn't used in this game but i left it in
 	virtual bool CanMoveTo(const int PlayFieldXin,const int PlayFieldYin,bool erase) {return false;} // can we move to a certain point, base always returns false, must be redeclared in inherited classes
 	virtual void Draw(Surface &Dst); // drawing
 	virtual ~CBoardPart() {}
};

// Cpeg is a class based on CBpoartPart
class CPeg : public CBoardPart
{
    public:
    // Constructor, just calls the base constructor of the base class with the same parameters
    // and sets some other parameters that are specific to CPeg
    CPeg(const int PlayFieldXin,const int PlayFieldYin);
    // can we move to the new playfield Coordinate
    bool CanMoveTo(const int PlayFieldXin,const int PlayFieldYin,bool erase);
};

#endif
