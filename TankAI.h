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

	// check if this "cell" is is a valid cell 
	bool isValid(float x, float z);

	// check if given cell is blocked or not
	bool isUnblocked(float x, float z);

	// check if destination cell has been reached or not
	bool isDestination(float x, float z, glm::vec3 dest);

	// calculate the h value
	double calculateHValue(float x, float z, glm::vec3 dest);

	bool fabsEqual(float a, float b);

public:

	TankAI(glm::vec3 cubePositions[], int cubesSize);
	~TankAI() {}

	// trace the path from the source to destination
	void tracePath(Cell cellDetails[][COL], glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest);

	// move to the next "cell" based on difference between position and dest
	void move(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest);

	// perform the search, will have to do this in a thread
	void performSearch(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 src, glm::vec3 dest);

};

