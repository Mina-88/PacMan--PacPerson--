
#include "Main_lib.h"


void adjMatrix(int** board, string& outputFile)
{
	ofstream AdjMatrix;
	AdjMatrix.open(outputFile);
	if (AdjMatrix.is_open())
	{
		vector<int> row(adjSize, 9999);
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLUMNS; j++)
			{
				if (board[i][j] > -1)
				{
					if (board[i][j - 1] > -1)
						row[board[i][j - 1]] = 1;

					if (board[i][j + 1] > -1)
						row[board[i][j + 1]] = 1;

					if (board[i - 1][j] > -1)
						row[board[i - 1][j]] = 1;

					if (board[i + 1][j] > -1)
						row[board[i + 1][j]] = 1;

					if(i==8 && j==0) 
						row[board[8][19]] = 1;

					if (i == 8 && j == 19)
						row[board[8][19]] = 1;


					for (int i = 0; i < adjSize; i++)
						AdjMatrix << row[i] << " ";


					fill(row.begin(), row.end(), 9999);
					AdjMatrix << "\n";
				}
			}
			
		}
		
		AdjMatrix.close();
	}
	else cout << "File is not open.." << endl;
}

 bool Exists(const string& name)
{
	ifstream file(name);
	bool state = file.good();
	file.close();
	return state;
}

vector<vector<int>> createAdjMatrix(string& name)
{

	vector<vector<int>> AdjMatrix(adjSize, vector<int> (adjSize));

	ifstream matFile;
	matFile.open(name);

	if (matFile.is_open())
	{
		for(int i = 0; i < adjSize;i++)
			for (int j = 0; j < adjSize; j++)
			{
				if (!matFile.eof())
					matFile >> AdjMatrix[i][j];
			}

		matFile.close();
		return AdjMatrix;
	}
	else
		cout << "error opening the matrix file..." << endl;
}

vector<vector<int>> Dijkstra(vector<vector<int>> Graph, int startNode)
{
	int costs[adjSize], previous[adjSize];
	bool visited[adjSize];

	// costs, previous, and visited
	for (int i = 0; i < adjSize; i++)
	{
		costs[i] = Graph[startNode][i];
		previous[i] = startNode;
		visited[i] = false;
	}

	// startNode
	costs[startNode] = 0;
	visited[startNode] = true;

	int count = 1, nextNode, minimumCost;
	while (count < adjSize)
	{
		// Find the minimum cost in order to visit a node.
		minimumCost = 9999;

		for (int i = 0; i < adjSize; i++)
			if ((costs[i] < minimumCost) && (visited[i] == false))
			{
				minimumCost = costs[i];
				nextNode = i;
			}

		// Visit the node.
		visited[nextNode] = true;

		// Update the costs of the children of the visited node.
		for (int i = 0; i < adjSize; i++)
			if ( (minimumCost + Graph[nextNode][i] < costs[i]) && (visited[i] == false))
			{
				costs[i] = minimumCost + Graph[nextNode][i];
				previous[i] = nextNode;
			}
		count++;

	}

	// Fill the paths.
	int j;
	vector<vector<int>> paths;
	paths.resize(adjSize);
	for (int i = 0; i < adjSize; i++)
	{
		paths[i].push_back(i);
		if (i != startNode)
		{
			j = i;
			do
			{
				j = previous[j];
				paths[i].push_back(j);
			} while (j != startNode);
		}
	}
	return paths;
}
