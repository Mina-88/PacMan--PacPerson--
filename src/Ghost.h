#ifndef GHOST_H
#define GHOST_H

#include "Character.h"
class Ghost :
    public Character
{
private:

public:

    Ghost();
    Ghost(string texteure_file, int r, int c, int gender, int intelligence);

    // move the ghost in a direction according to dijkstra direction
    // the ghost must move in a "not a wall" direction each time
    void moveChar(int**, vector<vector<int>>, int, int);

    // if the ghost is eaten reset his position to the ghost house
    void eaten();

};

#endif

