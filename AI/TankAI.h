#pragma once

#include "Grid.h"
#include <stack>
#include <set>
#include <thread>

class TankAI
{
private:
	// keeps track of <row, col> from the grid
	typedef std::pair<int, int> Pair;
	// keeps track of <f, <i, j>> of a CellDetails cell
	typedef std::pair<double, std::pair<int, int>> pPair;
	// shorthand for this 2d vector
	typedef std::vector<std::vector<CellDetails>> cells;

	Grid localGrid;

	bool isValid(int row, int col); // check if this cell is is a valid cell 
	bool isUnblocked(int row, int col); // check if given cell is blocked or not
	bool isDestination(int row, int col, GridCell dest); // check if destination cell has been reached or not
	double calculateHValue(int row, int col, GridCell dest); // calculate the h value for Euclidian distance

	void tracePath(cells cellDetails, glm::vec3& position,
		glm::vec3& rotation, glm::vec3& camPosition, GridCell dest); // trace the path from the source to destination

public:

	TankAI(int rows, int cols, int cubesSize);
	~TankAI() {}

	Grid getGrid();
	int round(float f); // to help with rounding floats

	// move to the next "cell" based on difference between position and dest
	void move(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest);

	

	// perform the search, will have to do this in a thread because loops
	void performSearch(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 src, glm::vec3 dest);

};

