#pragma once

#include <utility>
#include <iostream>
#include <stack>
#include <set>

#define ROW 9
#define COL 10

typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;

struct cell {
	int parent_i, parent_j;
	double f, g, h;
	// f: the lowest cost it takes to move to a cell
	// g: move cost
	// h: estimated move cost
};

bool isValid(int row, int col);
bool isUnblocked(int grid[][COL], int row, int col);
bool isDestination(int row, int col, Pair dest);
double calculateHValue(int row, int col, Pair dest);

void updateGrid(int grid[][COL]);
void move(int grid[][COL], int row, int col);

void tracePath(int grid[][COL], cell cellDet[][COL], Pair dest);
void aStarSearch(int grid[][COL], Pair src, Pair dest);
