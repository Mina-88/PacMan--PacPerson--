#include "Character.h"


void Character::drawOnWindow(RenderWindow& window)
{
	window.draw(character);
}

bool Character::getState()
{
	return state;
}

Time Character::StartInvincible(Clock c)
{
	Time t = c.getElapsedTime();
	t = c.restart();
	return t;
}

void Character::invState()
{
	state = 1;
}

void Character::endInvincible()
{
	state = 0;
}

int Character::getRow() const
{
	return row;
}

int Character::getColumn() const
{
	return column;
}

void Character::setRow(int r)
{
	if(r >= 0 && r <= 19 ) row = r;
}

void Character::setColumn(int c)
{
	if (c >= 0 && c <= 19) column = c;
}

void Character::setPosition(int r, int c)
{
	if (c >= 0 && c <= 19 && r >= 0 && r <= 19)
	character.setPosition(blockSize * c, blackSpace + blockSize * r);
}
