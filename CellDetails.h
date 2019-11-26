#pragma once

class CellDetails {
public:
	// row and column index of its parent
	int parent_i;
	int parent_j;

	// f = g + h
	double f; // the lowest cost it takes to move to a cell
	double g; // move cost to move to a specified square
	double h; // estimated move cost from the square to the destination
};