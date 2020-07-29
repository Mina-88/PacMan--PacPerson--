#include "Header.h"
#include "Pac.h"
#include "Ghost.h"
#include "Mode.h"

bool Character::state = 0;
int Pellet::availablePellets = 0;


int main()
{
	//initializing the required variables

	// clocks to control movements
	Clock clock;
	Clock clockG;
	Clock ClockInit;
	Clock ClockF;

	Clock InvincibleC;
	Time* Invincible = new Time;
	Time* init = new Time;
	Time* fruitT = new Time;

	// position of the fruit
	int currF = 2;

	// layer to create an effect in the invincible mode
	RectangleShape InvLayer;
	InvLayer.setPosition(0, blackSpace);
	InvLayer.setSize(Vector2f(WinWidth, WinLength - blackSpace));
	InvLayer.setFillColor(Color(0, 0, 0, 60));
	
	// the header that the game numbers are displayed on
	Texture header;
	header.loadFromFile("Images/Headers/header11.png");
	RectangleShape head;
	head.setSize(Vector2f(WinWidth, blackSpace));
	head.setPosition(0, 0);
	head.setTexture(&header);

	// check first time to invoke invincible state constructor
	bool firstTime = 1;

	// randomness
	srand(time(0));

	// setting some flags ( openning mouth/welcome screen/whether player is ready/whether player entered gender/gender)
	bool p_mouth = 1;
	bool begin = 1;
	bool ready = 0;
	bool isGetGender = 0;
	bool gender = 0;

	// creating some texts to be displayed in various places in the game
	Font fontH;
	fontH.loadFromFile("freshman.ttf");

	Text scoreCurrent;
	scoreCurrent.setFont(fontH);
	scoreCurrent.setFillColor(Color::Black);
	scoreCurrent.setStyle(Text::Regular);
	scoreCurrent.setCharacterSize(40);
	scoreCurrent.setPosition(WinWidth * 0.06, blackSpace * 0.5);

	Text invinc;
	invinc.setFont(fontH);
	invinc.setFillColor(Color::Black);
	invinc.setStyle(Text::Regular);
	invinc.setCharacterSize(15);
	invinc.setPosition(WinWidth * 0.45, blackSpace * 0.75);
	invinc.setString("Invincible");

	Text Hello;
	Hello.setFont(fontH);
	Hello.setFillColor(Color::White);
	Hello.setStyle(Text::Regular);
	Hello.setCharacterSize(200);
	Hello.setPosition(WinWidth * 0.12, WinLength * 0.3);
	Hello.setString("Hello");
	

	Text Second;
	Second.setFont(fontH);
	Second.setFillColor(Color::White);
	Second.setStyle(Text::Regular);
	Second.setCharacterSize(18);
	Second.setPosition(WinWidth * 0.12, WinLength * 0.4);
	Second.setString("Hello");

	Text highT;
	highT.setFont(fontH);
	highT.setFillColor(Color::Black);
	highT.setStyle(Text::Regular);
	highT.setCharacterSize(30);
	highT.setPosition(WinWidth * 0.75, WinLength * 0.07);
	

	Text higherT;
	higherT.setFont(fontH);
	higherT.setFillColor(Color::Black);
	higherT.setStyle(Text::Regular);
	higherT.setCharacterSize(30);
	higherT.setPosition(WinWidth * 0.75, WinLength * 0.03);

	// creating the window
	RenderWindow window(VideoMode(WinWidth, WinLength), "The game");
	
	// creating a clock for the welcoming screen and then displaying it
	Clock beginC;
	Time beg = beginC.getElapsedTime();





	/*
	// welcoming window
	while (window.isOpen() && begin)
	{

		Event ev;
		while(window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
				window.close();
			else if (ev.type == Event::KeyPressed)
			{
				if (ev.key.code == Keyboard::Space)
				{
					ready = 1;
				}
				else if (ev.key.code == Keyboard::M)
				{
					isGetGender = 1;
					gender = 0;
				}
				else if (ev.key.code == Keyboard::F)
				{
					isGetGender = 1;
					gender = 1;
				}
			}
		}


		beg = beginC.getElapsedTime();

		Hello.setCharacterSize(200);
		Hello.setPosition(WinWidth * 0.12, WinLength * 0.3);
		Hello.setString("Hello");

		if (beg.asSeconds() < 1.5)
		{
			window.clear();
			window.draw(Hello);
			window.display();
		}

		Hello.setCharacterSize(50);
		Hello.setPosition(WinWidth * 0.12, WinLength * 0.4);
		Hello.setString("Welcome to PacMan");

		Second.setPosition(WinWidth * 0.02, WinLength * 0.5);
		Second.setString("but you can play with different genders because we do not love discrimination");

		if (beg.asSeconds() < 6 && beg.asSeconds() > 2)
		{
			window.clear();
			window.draw(Hello);
			window.draw(Second);
			window.display();
		}

		Hello.setCharacterSize(30);
		Hello.setPosition(WinWidth * 0.06, WinLength * 0.4);
		Hello.setString("what gender do you want to play with");

		Second.setPosition(WinWidth * 0.2, WinLength * 0.5);
		Second.setString("for pacman press 'm' for for pacwoman press 'f'");

		if (beg.asSeconds() > 6 && !isGetGender)
		{
			window.clear();
			window.draw(Hello);
			window.draw(Second);
			window.display();
		}

		Hello.setCharacterSize(40);
		Hello.setPosition(WinWidth * 0.05, WinLength * 0.4);
		Hello.setString("If you are ready press spacebar");

		Second.setPosition(WinWidth * 0.1, WinLength * 0.5);
		Second.setString("warning :enter the realm of the ghosts only if you are brave enough");

		if ( !ready && isGetGender)
		{
			window.clear();
			window.draw(Hello);
			window.draw(Second);
			window.display();
		}

		if (isGetGender && ready)
		{
			begin = 0;
		}
	}
	*/

	bool s = 1;

	// creating the player and the game
	Pac p1("Images/PAC/pac2hm.png", 1, 1, gender);

	Mode game("Board.txt", "brick2.png", "Images/Allowed/stars.jpg", 2, &p1);

	// creating the adjacency matrix
	string fName = "AdjacencyMatrix.txt";

	if (!Exists(fName))
	{
		adjMatrix(game.getBoardNum(), fName);
	}

	vector<vector<int>> mat;
	mat = createAdjMatrix(fName);

	ClockInit.restart();

	// creating the scores tree
	AVLTree scores;
	int count = 0;
	int* val = new int;
	ifstream scoreF;
	scoreF.open("scores.txt");
	if (scoreF.is_open())
	{
		while (!scoreF.eof())
		{
			scoreF >> *val;
			scores.insert(*val);
			count++;
		}
	}
	else
		cout << "error reading the scores" << endl;
	delete val;

	scoreF.close();

	vector<int> scs;
	scores.traverse(scs);

	int high = 0;
	int higher = 0;

	// starting the game
	while (window.isOpen())
	{


		// getting the time for clocks responsible for the movement of ghosts and the player
		Time t = clock.getElapsedTime();
		Time g = clockG.getElapsedTime();

		// getting the current score to display it
		int score = p1.getScore();
		scoreCurrent.setString(to_string(score));

		int highest = 0;
		int min = INT_MAX;
		for (int i = 0; i < scs.size(); i++)
		{
			if (score < scs[i] && i < min && i < scs.size() - 1)
			{
				high = scs[i];
				higher = scs[i + 1];
				min = i;
			}
			else if (score > scs[i] && i == scs.size() - 2)
			{
				highest = 2;
				higher = scs[scs.size() - 1];
			}
			else if (score > scs[i] && i == scs.size() - 1)
			{
				highest = 1;
			}
		}

		highT.setString(to_string(high));
		higherT.setString(to_string(higher));

		if (highest == 2)
		{
			highT.setString("second");
			higherT.setString(to_string(higher));
		}
		else if(highest == 1)
		{
			highT.setString("---------------");
			higherT.setString("congrats");
		}
		// check if the player has won
		if (Pellet::availablePell() == 0)
		{
			game.lostWon(window, 1, score, scores);
			return 0;
		}

		// getting different events and key presses and handling them
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			else if (event.type == Event::KeyPressed && t.asMilliseconds() > 300)
			{
				// move the charachter and check if any collisions happened (note: the time put in the condition is to handle constant key pressing glitch)
				if (!game.onKeyMove(p_mouth, event, window, score, scores, s, ClockInit)) return 0;
				p_mouth = !p_mouth;
					
				clock.restart();
			}
		}

		// add additional life each 10000
		game.checkAddLives();

		*fruitT = ClockF.getElapsedTime();
		if (fruitT->asSeconds() > 5)
		{
			ClockF.restart();
			game.addFruit(currF);
			currF = (currF * 2) % 31;

		}

		// check for crash
		if (game.crash(Character::getState()))
		{
			game.resetInitial(s, ClockInit);

			if (game.getPlayer()->getLives() < 1)
			{
				game.lostWon(window, 0, score, scores);
				return 0;
			}
		}

		// moving the player continuously;
		game.movePlayer(100, event, p_mouth, t, clock);

		
		
		// to avoid making the ghosts have the same path at the beginning
		*init = ClockInit.getElapsedTime();
		int initNum = 0;
		if (s)
		{
			if (init->asSeconds() < 3)
				initNum = 3;
			else if (init->asSeconds() >= 3 && init->asSeconds() < 5)
				initNum = 2;
			else if (init->asSeconds() >= 5 && init->asSeconds() < 7)
				initNum = 1;
			else if (init->asSeconds() >= 7)
			{
				initNum = 0;
				s = 0;
			}
		}
			

		// moving the ghost continuously
		game.moveGhost(initNum, 150, g, clockG, mat);

		// setting the invincible state and ending it after 10 seconds
		game.handleInv(firstTime, InvincibleC, Invincible);
		
		// displaying the game
		window.clear();
		game.drawOnWindow(window);
		game.drawGhosts(window);
		p1.drawOnWindow(window);
		if (Invincible->asMilliseconds() % 2 == 0 && Character::getState()) window.draw(InvLayer);
		window.draw(head);
		window.draw(scoreCurrent);
		p1.drawLives(window);
		if (Character::getState()) window.draw(invinc);
		window.draw(higherT);
		window.draw(highT);
		window.display();

	}

	delete Invincible;

	return 0;
}