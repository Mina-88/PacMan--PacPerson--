#include "Pac.h"

Pac::Pac(string texteure_file, int r, int c, int gender)
{

	AtePPB.loadFromFile("sounds/AtePP.ogg");
	AtePP.setBuffer(AtePPB);

	


	if(gender == 0) texture.loadFromFile("Images/PAC/pac2hm.png");
	else texture.loadFromFile("Images/PAC/pac2hg.png");

	character.setRadius(blockSize / 2);
	character.setPosition(blockSize * c, blackSpace + blockSize * r);
	character.setTexture(&texture);

	hearts.loadFromFile("Images/heart/heart1.png");
	heart.setSize(Vector2f(blockSize, blockSize));
	heart.setTexture(&hearts);


	row = r;
	column = c;

	this->gender = gender;

	score = 000000;
	lives = 3;
	

	addedLives = 0;

}

void Pac::moveChar(Event e, int** arr, Pellet*** arr2, bool OpCl)
{

	switch (e.key.code)
	{
	case Keyboard::Up:

		if (arr[row - 1][column] >= 0)
		{
			if ((arr2[row - 1][column])->getAvailability())
			{
				int res = (arr2[row - 1][column])->eaten();
				if ( res == 1)
				{
					AtePP.play();
					Character::invState();
					score += 50;

				}
				else if (res == 2)
				{
					AtePP.play();
					score += 1000;
				}
				else score += 10;
			}


			character.move(0, -blockSize);
			if (gender == 0)
			{
				if (OpCl) texture.loadFromFile("Images/PAC/pac2hmu.png");
				else texture.loadFromFile("Images/PAC/pac2hmu_c.png");
			}
			else
			{
				if (OpCl) texture.loadFromFile("Images/PAC/pac2hgu.png");
				else texture.loadFromFile("Images/PAC/pac2hgu_c.png");
			}
			row--;
		}
		break;
	case Keyboard::Down:
		if (arr[row + 1][column] >= 0)
		{
			if ((arr2[row + 1][column])->getAvailability())
			{
				int res = (arr2[row + 1][column])->eaten();
				if (res == 1)
				{
					AtePP.play();
					Character::invState();
					score += 50;
				}
				else if (res == 2)
				{
					AtePP.play();
					score += 1000;
				}
				else score += 10;
			}
			character.move(0, blockSize);
			if (gender == 0)
			{
				if (OpCl) texture.loadFromFile("Images/PAC/pac2hmd.png");
				else texture.loadFromFile("Images/PAC/pac2hmd_c.png");
			}
			else
			{
				if (OpCl) texture.loadFromFile("Images/PAC/pac2hgd.png");
				else texture.loadFromFile("Images/PAC/pac2hgd_c.png");
			}
			row++;
		}
		break;
	case Keyboard::Right:
		if (arr[row][column + 1] >= 0)
		{
			if ((arr2[row][column + 1])->getAvailability())
			{
				int res = (arr2[row][column + 1])->eaten();
				if (res == 1)
				{
					AtePP.play();
					Character::invState();
					score += 50;
				}
				else if (res == 2)
				{
					AtePP.play();
					score += 1000;
				}
				score += 10;
			}
			character.move(blockSize, 0);
			if (gender == 0)
			{
				if (OpCl) texture.loadFromFile("Images/PAC/pac2hm.png");
				else texture.loadFromFile("Images/PAC/pac2hm_c.png");
			}
			else
			{
				if (OpCl) texture.loadFromFile("Images/PAC/pac2hg.png");
				else texture.loadFromFile("Images/PAC/pac2hg_c.png");
			}

			column++;
		}

		if (this->getRow() == 8 && this->getColumn() == 19)
		{
			row = 8;
			column = 0;
			character.setPosition(0, blackSpace + blockSize * 8);

			if ((arr2[8][0])->getAvailability())
			{
				(arr2[8][0])->eaten();
				score += 100;
			}
		}
		break;
	case Keyboard::Left:
		if (arr[row][column - 1] >= 0)
		{
			if ((arr2[row][column - 1])->getAvailability())
			{
				int res = (arr2[row][column - 1])->eaten();
				if (res == 1)
				{
					AtePP.play();
					Character::invState();
					score += 50;
				}
				else if (res == 2)
				{
					AtePP.play();
					score += 1000;
				}
				else score += 10;
			}

			character.move(-blockSize, 0);

			if (gender == 0)
			{
				if (OpCl) texture.loadFromFile("Images/PAC/pac2hml.png");
				else texture.loadFromFile("Images/PAC/pac2hml_c.png");
			}
			else
			{
				if (OpCl) texture.loadFromFile("Images/PAC/pac2hgl.png");
				else texture.loadFromFile("Images/PAC/pac2hgl_c.png");
			}

			column--;
		}

		if (this->getRow() == 8 && this->getColumn() == 0)
		{
			row = 8;
			column = 19;
			character.setPosition(blockSize * 19, blackSpace + blockSize * 8);

			if ((arr2[8][19])->getAvailability())
			{
				(arr2[8][19])->eaten();
				score += 100;
			}
		}
		break;
	}
}

void Pac::lostLife()
{
	lives--;
}

void Pac::gainedLife()
{
	lives++;
}

void Pac::ateAGhost()
{
	score += 500;
}

void Pac::drawLives(RenderWindow & window)
{
	for (int i = 0; i < lives; i++)
	{
		heart.setPosition(WinWidth * 0.42 + i * 1.2 * blockSize, blackSpace * 0.3);
		window.draw(heart);
	}
}

void Pac::increaseAddedLives()
{
	addedLives++;
}

int Pac::getAddedLives() const
{
	return addedLives;
}

int Pac::getScore() const
{
	return score;
}

int Pac::getLives() const
{
	return lives;
}
