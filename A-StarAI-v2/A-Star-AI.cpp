// A-Star-AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <utility>
#include "AStar.h"

using namespace std;

int main()
{
	
	int grid[ROW][COL] =
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
	};

	Pair src = make_pair(0, 0);
	Pair dest = make_pair(4, 6);
	aStarSearch(grid, src, dest);

	return 0;
}

