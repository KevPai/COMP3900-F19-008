#pragma once

#include "Cell.h"
#include <stack>
#include <set>
#include <thread>

class TankAI
{
private:
	typedef std::pair<double, std::pair<int, int>> pPair;

	std::vector<glm::vec3> cubes;

	// fixed number until we have a proper field
	static const int ROW = 7;
	static const int COL = 9;

	int grid[ROW][COL];

	void initGrid();
	int round(float f);

	// check if this "cell" is is a valid cell 
	bool isValid(float x, float z);

	// check if given cell is blocked or not
	bool isUnblocked(int x, int z);

	// check if destination cell has been reached or not
	bool isDestination(int x, int z, glm::vec3 dest);

	// calculate the h value
	double calculateHValue(int x, int z, glm::vec3 dest);

public:

	TankAI(glm::vec3 cubePositions[], int cubesSize);
	~TankAI() {}

	//void updateGrid();
	//void printGrid();

	// trace the path from the source to destination
	void tracePath(Cell cellDetails[][COL], glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest);

	// move to the next "cell" based on difference between position and dest
	void move(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest);

	// perform the search, will have to do this in a thread because loops
	void performSearch(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 src, glm::vec3 dest);

};

