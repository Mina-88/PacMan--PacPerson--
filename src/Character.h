
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Header.h"

// base class for both player and ghost
class Character
{
protected:

	CircleShape character;
	Texture texture;
	int row;
	int column;
	// the state of the game whether it is invincible or not
	static bool state;
	

public:

	// a function to draw the specific character on the window
	virtual void drawOnWindow(RenderWindow&);

	// returns whether characters are in invincible mode or not
	static bool getState();
	// a function which starts counting time for invincible mode
	static Time StartInvincible(Clock);
	// a function which sets the state to invincible
	static void invState();
	// a function which ends the invinciblee mode
	static void endInvincible();

	// get the row of the character
	int getRow() const;
	// get the column of the character
	int getColumn() const;

	// change the row of the character
	void setRow(int r);
	// changes the column of the character
	void setColumn(int c);
	// a function that sets the position of the character on the sfml board
	void setPosition(int r, int c);


};

#endif

