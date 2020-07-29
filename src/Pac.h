#ifndef PAC_H
#define PAC_H

#include "Character.h"
#include "Pellet.h"
#include "Header.h"

class Pac : public Character
{
private:

	unsigned int score;
	int lives;
	int gender;
	RectangleShape heart;
	Texture hearts;
	int addedLives;
	SoundBuffer AtePPB;
	Sound AtePP;
	


public:

	Pac(string, int, int, int);

	// moves the character
	void moveChar(Event, int** , Pellet***, bool);
	
	// decreases the lives
	void lostLife();

	// increases the lives
	void gainedLife();

	//increases the score after eating a ghost
	void ateAGhost();

	//draw the lives on the screen
	void drawLives(RenderWindow&);

	//increase the counter of the lives added after gainning a certain score
	void increaseAddedLives();

	// a getter for the counter of the lives gained after a certain score
	int getAddedLives() const;

	// a getter for the score of the player
	int getScore() const;

	// a getter for the lives of the player
	int getLives() const;
};

#endif

