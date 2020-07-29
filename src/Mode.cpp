
#include "Mode.h"

Mode::Mode( string boardFile, string wallPic , string groundPic, int num, Pac* p)

{
	/* creating 2d dynamic arrays for the board / drawnRectangels / pellets and 
	then reading the board from an external file and getting textures and then setting the board */

	if (!backMusic.openFromFile("sounds/back.ogg"))
		cout << "error loading the music" << endl; // error
	backMusic.play();
	backMusic.setVolume(10.f);
	backMusic.setLoop(true);

	if (!gainLife.openFromFile("sounds/gainLife.ogg"))
		cout << "error loading the music" << endl; // error

	if (!Won.openFromFile("sounds/Won.ogg"))
		cout << "error loading the music" << endl; // error
	Won.setPlayingOffset(sf::seconds(9.f));

	if (!Lost.openFromFile("sounds/Lost.ogg"))
		cout << "error loading the music" << endl; // error


	numGhosts = num;

	boardNum = new int * [ROWS];
	for (int i = 0; i < COLUMNS; i++)
		*(boardNum + i) = new int[COLUMNS];

	board = new RectangleShape* [ROWS];
	for (int i = 0; i < COLUMNS; i++)
		*(board + i) = new	RectangleShape[COLUMNS];

	pellets = new Pellet ** [ROWS];
	for (int i = 0; i < COLUMNS; i++)
	{
		*(pellets + i) = new Pellet * [COLUMNS];
		for(int j = 0; j < COLUMNS; j++)
			*(*(pellets + i)+j) = new Pellet;
	}

	ifstream inputFile;
	inputFile.open(boardFile);
	if (inputFile.is_open())
	{
		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLUMNS; j++)
				if (!inputFile.eof())
					inputFile >> boardNum[i][j];
		inputFile.close();
	}
	else cout << "Error loading Board.txt ..." << endl;

	wallT.loadFromFile(wallPic);
	groundT.loadFromFile(groundPic);


	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
		{
			board[i][j].setSize(Vector2f(blockSize, blockSize));
			board[i][j].setPosition(blockSize * j, blackSpace + blockSize * i);
			if (boardNum[i][j] < 0)
			{
				board[i][j].setTexture(&wallT);
			}
			else
			{
				board[i][j].setTexture(&groundT);

				if ((i == 5 && (j == 1 || j == 18)) || (i == 16 && (j == 1 || j == 18)))
				{
					delete (*(*(pellets + i) + j));
					(*(*(pellets + i) + j)) = new Pellet(1, i, j);
				}
				else if ((i == 10 && (j == 8 || j == 9 || j == 10 || j == 11)) || (i == 11 && (j == 8 || j == 9 || j == 10 || j == 11))) continue;
				else
				{
					delete (*(*(pellets + i) + j));
					(*(*(pellets + i) + j)) = new Pellet(0, i, j);
				}
			}
		}

	p1 = p;


	Ghost* g1 = new Ghost("Images/Ghosts/ghost2.png", 11, 8, 0, 0);
	Ghost* g2 = new Ghost("Images/Ghosts/ghost3.png", 11, 9, 0, 0);
	Ghost* g3 = new Ghost("Images/Ghosts/ghost4.png", 11, 10, 0, 0);
	Ghost* g4 = new Ghost("Images/Ghosts/ghost5.png", 11, 11, 0, 0);

	ghosts.push_back(g1);
	ghosts.push_back(g2);
	ghosts.push_back(g3);
	ghosts.push_back(g4);

	vector<Fruit> fruits;
}

Mode::~Mode()
{
	// destructor for the dynamic arrays

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
			delete (*(*(pellets + i) + j));
		delete[] * (pellets + i);
	}
	delete [] pellets;

	for (int i = 0; i < ROWS; i++)
	{
		delete[] * (boardNum + i);
	}
	delete[] boardNum;

	for (int i = 0; i < ROWS; i++)
	{
		delete[] * (board + i);
	}
	delete[] board;

	for (int i = 0; i < ghosts.size(); i++)
	{
		delete ghosts[i];
	}
	ghosts.clear();
	ghosts.resize(0);
}

int** Mode::getBoardNum()
{
	// returns a reference to the board of numbers
	return boardNum;
}

Pellet*** Mode::getPellets() 
{
	// returns a reference to the pellets
	return pellets;
}

void Mode::checkAddLives()
{
	if ((p1->getScore() > 10000 * (p1->getAddedLives() + 1)))
	{
		gainLife.play();
		p1->gainedLife();
		p1->increaseAddedLives();
	}
}

bool Mode::onKeyMove(bool mouth, Event event, RenderWindow& window, int score, AVLTree& scores, bool& s, Clock& t)
{
	p1->moveChar(event, getBoardNum(), pellets, mouth);

	if (crash(Character::getState()))
	{
		resetInitial(s, t);
		// check if the player has lost
		if (p1->getLives() < 1)
		{
			lostWon(window, 0, score, scores);
			return 0;
		}
	}
	return 1;
}

vector<Ghost*>* Mode::getGhosts()
{
	return &ghosts;
}

Pac* Mode::getPlayer()
{
	return p1;
}

void Mode::drawOnWindow(RenderWindow& win)
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			win.draw(board[i][j]);

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++)
			if(boardNum[i][j] >= 0) (*(*(pellets + i) + j))->drawOnWindow(win);
}

void Mode::drawGhosts(RenderWindow& window)
{
	for (int i = 0; i < ghosts.size(); i++)
	{
		(ghosts[i])->drawOnWindow(window);
	}
}


bool Mode::crash(bool state)
{
	// a function to check for collisions and its state then taking the required action
	for (int i = 0; i < Mode::ghosts.size() ; i++)
	{
		if ((p1->getRow() == (ghosts[i])->getRow()) && (p1->getColumn() == (ghosts[i])->getColumn()) && !state)
		{
			p1->lostLife();
			return true;
		}
		else if ((p1->getRow() == (ghosts[i])->getRow()) && (p1->getColumn() == (ghosts[i])->getColumn()) && state)
		{
			p1->ateAGhost();
			ghosts[i]->eaten();
			return false;
		}
	}
	return false;
}

void Mode::resetInitial(bool& s, Clock& t)
{

	// a function invoked after normal collisions to reset the places of the characters
	sleep(milliseconds(1000));
	p1->setPosition(1, 1);
	p1->setRow(1);
	p1->setColumn(1);

	int r = 10;
	int c = 8;

	for (int i = 0; i < ghosts.size(); i++)
	{
		if (c == 11)
		{
			r++;
			c = 8;
		}

		ghosts[i]->setPosition(r, c);
		ghosts[i]->setRow(r);
		ghosts[i]->setColumn(c);

		c++;
	}

	s = 1;
	t.restart();

	sleep(milliseconds(1000));
}

void Mode::addFruit(int curr)
{
	for (int i = 2; i < COLUMNS; i = (i*2))
		if ( !pellets[i][i - 1]->getAvailability() && i == curr)
		{
			delete (*(*(pellets + i) + (i - 1)));
			pellets[i][i - 1] = new Fruit(1, i, i - 1, 200, "Images/fruits/fruit1.png");
			return;
			/*
			switch (curr)
			{
			case 2:

			case 4:
				delete (*(*(pellets + i) + (i - 1)));
				pellets[i][i - 1] = new Fruit(1, i, i - 1, 200, "Images/fruits/fruit1.png");
				return;
			case 8:
				delete (*(*(pellets + i) + (i - 1)));
				pellets[i][i - 1] = new Fruit(1, i, i - 1, 200, "Images/fruits/fruit1.png");
				return;
			case 16:
				delete (*(*(pellets + i) + (i - 1)));
				pellets[i][i - 1] = new Fruit(1, i, i - 1, 200, "Images/fruits/fruit1.png");
				return;
			}*/
			
		}
				
}

void Mode::movePlayer(int speed, Event event, bool& mouth, Time& t, Clock& c)
{
	if (t.asMilliseconds() > speed)
	{
		p1->moveChar(event, boardNum, pellets, mouth);

		mouth = !mouth;

		t = c.restart();
	}
}

void Mode::moveGhost(int initNum, int speed, Time& g, Clock& c, vector<vector<int>>& mat)
{
	if (g.asMilliseconds() > speed)
	{
		for (int i = 0; i < ghosts.size() - initNum; i++)
		{
			// there is an error here check first
			int GhostNode = (boardNum[(ghosts[i]->getRow())][(ghosts[i]->getColumn())]);
			int PacNode = (boardNum[p1->getRow()][p1->getColumn()]);

			ghosts[i]->moveChar(boardNum, Dijkstra(mat, GhostNode), GhostNode, PacNode);
		}

		g = c.restart();
	}

}

void Mode::handleInv(bool& ft, Clock& invC, Time* inv)
{
	if (Character::getState())
	{
		if (ft)
		{
			invC.restart();
			*inv = Character::StartInvincible(invC);
			ft = 0;
		}

		*inv = invC.getElapsedTime();

		if (inv->asSeconds() > 10)
		{
			Character::endInvincible();
			ft = 1;
		}

	}
}

void Mode::lostWon(RenderWindow& window, bool finishingStatus, int cScore, AVLTree& tree)
{
	// a function to draw lose win messages
	Font fonte;
	fonte.loadFromFile("freshman.ttf");

	Clock c;
	Time tc = c.getElapsedTime();

	vector<int> sc;

	ofstream score;
	score.open("scores.txt", fstream::app);
	if (score.is_open())
		score << cScore << endl;
	else
		cout << "error appending the score" << endl;
	score.close();

	tree.insert(cScore);
	tree.traverse(sc);
	reverse(sc.begin(), sc.end());

	Text scText;
	scText.setFont(fonte);
	scText.setFillColor(Color::Black);
	scText.setStyle(Text::Regular);
	scText.setCharacterSize(25);

	Text order;
	order.setFont(fonte);
	order.setFillColor(Color::Black);
	order.setStyle(Text::Regular);
	order.setCharacterSize(25);

	RectangleShape Lb;
	Lb.setSize(Vector2f(WinWidth, WinLength));
	Lb.setPosition(0, 0);
	Texture B;
	B.loadFromFile("Images/Backgrounds/leaderBoard.jpg");
	Lb.setTexture(&B);


	if (finishingStatus)
	{
		backMusic.pause();
		Won.play();

		Text End;
		End.setFont(fonte);
		End.setFillColor(Color::Black);
		End.setStyle(Text::Regular);
		End.setCharacterSize(40);
		End.setPosition(WinWidth * 0.05, WinLength * 0.4);
		End.setString("Congratulations, You've won!!");

		sleep(milliseconds(400));

		RectangleShape backW;
		backW.setSize(Vector2f(WinWidth, WinLength));
		backW.setPosition(0, 0);
		Texture W;
		W.loadFromFile("Images/Backgrounds/won.jpg");
		backW.setTexture(&W);

		while (tc.asSeconds() < 2)
		{
			tc = c.getElapsedTime();
			window.clear();
			window.draw(backW);
			window.draw(End);
			window.display();
		}

		window.clear();
		window.draw(Lb);

		for (int i = 0; i < sc.size(); i++)
		{
			if (sc[i] == cScore)
			{
				scText.setPosition(WinWidth * 0.50, (WinLength * 0.1) + (WinLength * 0.05 * i));
				scText.setFillColor(Color::Red);
				scText.setString(to_string(sc[i]));
				order.setPosition(WinWidth * 0.40, (WinLength * 0.1) + (WinLength * 0.05 * i));
				order.setFillColor(Color::Red);
				order.setString(to_string(i + 1) + "-");
				window.draw(order);
				window.draw(scText);
				order.setFillColor(Color::Black);
				scText.setFillColor(Color::Black);

			}
			else
			{
				scText.setPosition(WinWidth * 0.50, (WinLength * 0.1) + (WinLength * 0.05 * i));
				scText.setString(to_string(sc[i]));
				order.setPosition(WinWidth * 0.40, (WinLength * 0.1) + (WinLength * 0.05 * i));
				order.setString(to_string(i + 1) + "-");
				window.draw(order);
				window.draw(scText);
			}
		}

		window.display();
		sleep(seconds(7));

	}
	else
	{
		backMusic.pause();
		Lost.play();

		Text End;
		End.setFont(fonte);
		End.setFillColor(Color::Red);
		End.setStyle(Text::Regular);
		End.setCharacterSize(40);
		End.setPosition(WinWidth * 0.2, WinLength * 0.4);
		End.setString("Sorry, you've lost!!");

		sleep(milliseconds(400));

		RectangleShape backL;
		backL.setSize(Vector2f(WinWidth, WinLength));
		backL.setPosition(0, 0);
		Texture L;
		L.loadFromFile("Images/Backgrounds/lose.jpg");
		backL.setTexture(&L);

		while (tc.asSeconds() < 3)
		{
			tc = c.getElapsedTime();
			window.clear();
			window.draw(backL);
			window.draw(End);
			window.display();
		}

		window.clear();
		window.draw(Lb);

		for (int i = 0; i < sc.size(); i++)
		{
			if (sc[i] == cScore)
			{
				scText.setFillColor(Color::Red);
				scText.setString(to_string(sc[i]));
				scText.setPosition(WinWidth * 0.50, WinLength * 0.1 + (WinLength * 0.05 * i));
				order.setPosition(WinWidth * 0.40, (WinLength * 0.1) + (WinLength * 0.05 * i));
				order.setFillColor(Color::Red);
				order.setString(to_string(i + 1) + "-");
				window.draw(order);
				window.draw(scText);
				order.setFillColor(Color::Black);
				scText.setFillColor(Color::Black);

			}
			else
			{
				scText.setString(to_string(sc[i]));
				scText.setPosition(WinWidth * 0.50, WinLength * 0.1 + (WinLength * 0.05 * i));
				order.setPosition(WinWidth * 0.40, (WinLength * 0.1) + (WinLength * 0.05 * i));
				order.setString(to_string(i + 1) + "-");
				window.draw(order);
				window.draw(scText);
			}
		}

		window.display();
		sleep(seconds(7));
	}

}