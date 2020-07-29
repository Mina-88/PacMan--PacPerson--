#include "Ghost.h"

Ghost::Ghost()
{
	// default constructor for ghost object
	row = 0;
	column = 0;

}

Ghost::Ghost(string texteure_file, int r, int c, int gender, int intelligence)
{
	//overloaded constructor for ghost object

	texture.loadFromFile(texteure_file);
	character.setRadius(blockSize / 2);
	character.setPosition(blockSize * c, blackSpace + blockSize * r);
	character.setTexture(&texture);

	row = r;
	column = c;


}

void Ghost::moveChar(int** arr, vector<vector<int>> path, int currNode, int pNode)
{

	// these conditions were put to avoid a run time error accessing invalid palce in the memory when the palyer and many ghosts are in a crash or near in the invincible mode
	int nextStep;
	if (path[pNode].size() > 1)
		nextStep = path[pNode][path[pNode].size() - 2];
	else
		nextStep = path[pNode][path[pNode].size() - 1];


	if (this->getRow() == 8 && this->getColumn() == 19)
	{
		row = 8;
		column = 0;
		character.setPosition(0, blackSpace + blockSize * 8);
	
		character.move(blockSize, 0);
		column++;
	
	}
	else if (this->getRow() == 8 && this->getColumn() == 0)
	{
		row = 8;
		column = 19;
		character.setPosition(blockSize * 19, blackSpace + blockSize * 8);
	
		character.move(-blockSize, 0);
		column--;
	}
	else if( nextStep - currNode < -1 )
	{
		character.move(0, -blockSize);
		row--;
	}
	else if ( nextStep - currNode > 1)
	{
		character.move(0, blockSize);
		row++;
	}
	else if (nextStep - currNode == -1)
	{
		character.move(-blockSize, 0);
		column--;
	}
	else if (nextStep - currNode == 1)
	{
		character.move(blockSize, 0);
		column++;
	}
}

void Ghost::eaten()
{

	int r = rand() % 2 + 10;
	int c = rand() % 4 + 8;


	this->setPosition(r, c);
	this->setRow(r);
	this->setColumn(c);

	sleep(milliseconds(200));
}

