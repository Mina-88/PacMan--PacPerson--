
#ifndef MODE_H
#define MODE_H

#include "Header.h"
#include "Ghost.h"
#include "Pellet.h"
#include "Pac.h"
#include "Fruit.h"
#include "AVLTree.h"
#include "Main_lib.h"

class Mode
{
private:

    RectangleShape** board;
    int** boardNum;
    Pellet*** pellets;
    vector<Ghost*> ghosts;
    vector<Fruit> fruits;
    Pac* p1;
    int numGhosts;
    Texture wallT;
    Texture groundT;
    Music backMusic;
    Music gainLife;
    Music Won;
    Music Lost;
    Music AtePP;

public:

    // the constructor with given parameters
    Mode(string, string, string, int, Pac*);
    // destructor
    ~Mode();
    // getter for the numbers on the board dynamic array
    int** getBoardNum();
    // getter for the pellets objects dynamic array
    Pellet*** getPellets();
    // checks if the score is the required to add more lives or not
    void checkAddLives();
    // moves the character according to dijkstra
    bool onKeyMove(bool, Event, RenderWindow&, int, AVLTree&, bool&, Clock&);
    // check if collision between the player and the ghost happens
    bool crash(bool);
    //  reset ghosts to the initial point
    void resetInitial(bool&, Clock&);
    // add fruit to the board
    void addFruit(int);
    // move the player
    void movePlayer(int speed, Event event, bool& mouth, Time& t, Clock& c);
    // move the ghost
    void moveGhost(int, int, Time&, Clock&, vector<vector<int>>&);
    // keeps track of the invincibility mode
    void handleInv(bool&, Clock&, Time*);
    // getter for the vector of ghosts
    vector<Ghost*>* getGhosts();
    // gets the player object
    Pac* getPlayer();
    // drawing the board and the pellets
    void drawOnWindow(RenderWindow&);
    // draws the ghosts on the window
    void drawGhosts(RenderWindow&);
    // displays the last window and the leaderboard
    void lostWon(RenderWindow&, bool, int, AVLTree&);
};

#endif

