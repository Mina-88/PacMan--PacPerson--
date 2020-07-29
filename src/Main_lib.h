#ifndef MAIN_LIB_H
#define MAIN_LIB_H


#include "Header.h"
#include "AVLTree.h"
#include "Pac.h"
#include "Ghost.h"
#include "Mode.h"

// creates the adjacency matrix txt file
void adjMatrix(int**, string&);

// checks whether a certain file exists or not
bool Exists(const string&);

// creates the adjacency matrix for the board graph
vector<vector<int>> createAdjMatrix(string&);

// performs dijkstra's algorithm on adjacency matrix
vector<vector<int>> Dijkstra(vector<vector<int>> Graph, int startNode);

#endif