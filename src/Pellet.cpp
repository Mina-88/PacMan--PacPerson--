#include "Pellet.h"

Pellet::Pellet()
{
	row = 0;
	column = 0;
	available = 0;
	state = false;
}

Pellet::Pellet( bool state, int row, int column)
{
	available = 1;
	
	pellet.setFillColor(Color::Yellow);

	// setting size according to the type (power or not)
	if (state == 0)
	{
		pellet.setRadius(blockSize / 8);
		pellet.setPosition(blockSize * column + (0.5 * blockSize - blockSize / 8), blackSpace + blockSize * row + (0.5 * blockSize - blockSize / 8));
	}
	else
	{
		pellet.setRadius(blockSize / 4);
		pellet.setPosition(blockSize * column + (0.5 * blockSize - blockSize / 4), blackSpace + blockSize * row + (0.5 * blockSize - blockSize / 4));
	}

	availablePellets++;

	this->state = state;
	this->row = row;
	this->column = column;
}

int Pellet::eaten()
{
	pellet.setFillColor(Color::Transparent);
	available = 0;
	availablePellets--;
	return state;
}

bool Pellet::getAvailability()
{
	return available;
}

bool Pellet::getState() const
{
	return state;
}

int Pellet::getRow() const
{
	return row;
}

int Pellet::getColumn() const
{
	return column;
}

int Pellet::availablePell()
{
	return availablePellets;
}

void Pellet::decrementPell()
{
	availablePellets--;
}


void Pellet::drawOnWindow(RenderWindow& window)
{
	window.draw(pellet);
}

void Pellet::changeTexture(Texture& tex)
{
	pellet.setTexture(&tex);
}

void Pellet::setAvailability(bool av)
{
	available = av;
}

void Pellet::setColor(Color c)
{
	pellet.setFillColor(c);
}
