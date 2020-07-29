#include "Fruit.h"

Fruit::Fruit(bool state, int row, int column, int score, string TexF)
	:Pellet(state, row, column)
{
	decrementPell();
	type.loadFromFile(TexF);
	changeTexture(type);


}

int Fruit::eaten()
{
	this->setColor(Color::Transparent);
	this->setAvailability(0);
	return 2;
}
