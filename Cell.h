#pragma once

#include "Header.h"

class Cell {
public:
	int parent_x;
	int parent_z;
	double f; // the lowest cost it takes to move to a cell
	double g; // move cost to move to a specified square
	double h; // estimated move cost from the square to the destination
};