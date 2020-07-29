#ifndef FRUIT_H
#define FRUIT_H

#include "Pellet.h"

class Fruit :
    public Pellet
{
private:

    // an attribute to change the shape of the fruit
    Texture type;

public:
    
    Fruit(bool, int,int, int, string);
    // making the fruit unavailable and transparent after getting eaten
    int eaten();
};

#endif

