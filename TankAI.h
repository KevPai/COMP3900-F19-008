#pragma once

#include "Grid.h"
#include <stack>
#include <set>
#include <thread>

class TankAI
{
private:
	typedef std::pair<int, int> Pair;
	typedef std::pair<double, std::pair<int, int>> pPair;
	typedef std::vector<std::vector<CellDetails>> cells;
	cells cellDetails = {};

	Grid localGrid;

	int round(float f); // to help with rounding floats

	void initCellDetails(cells& cellDetails);

	bool isValid(int row, int col); // check if this cell is is a valid cell 
	bool isUnblocked(int row, int col); // check if given cell is blocked or not
	bool isDestination(int row, int col, GridCell dest); // check if destination cell has been reached or not
	double calculateHValue(int row, int col, GridCell dest); // calculate the h value for Euclidian distance

	void tracePath(cells cellDetails, glm::vec3& position,
		glm::vec3& rotation, glm::vec3& camPosition, GridCell dest); // trace the path from the source to destination

public:

	TankAI(int rows, int cols, int cubesSize);
	~TankAI() {}

	// move to the next "cell" based on difference between position and dest
	void move(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest);

	// perform the search, will have to do this in a thread because loops
	void performSearch(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 src, glm::vec3 dest);

};

