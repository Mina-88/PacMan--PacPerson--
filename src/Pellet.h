#ifndef PELLET_H
#define PELLET_H

#include "Header.h"

class Pellet
{
private:

	CircleShape pellet;
	bool state;
	int row;
	int column;
	bool available;
	static int availablePellets;

public:

	Pellet();
	// overloaded constructor for pellet
	Pellet(bool state, int row, int column);

	// changes the availabilty of the pellet and makes it transparent then returns whether it was a power pellet or not
	virtual int eaten();

	// gets whether the pellet was not eaten or not
	bool getAvailability();
	// returns whether the pellet is power pellet or not
	bool getState() const;
	// returns the row number
	int getRow() const;
	// returns the column number
	int getColumn() const;

	// changes the texture of the pellet
	void changeTexture(Texture&);
	// sets the availability of the pellet to a given one
	void setAvailability(bool);
	// sets the color of the pellet to a given one
	void setColor(Color);

	//returns the number of available pellets
	static int availablePell();
	//decrements the number of available pellets by one
	static void decrementPell();

	// draws the pellet on the window
	void drawOnWindow(RenderWindow&);
};

#endif

