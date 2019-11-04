#pragma once

#include "Header.h"
#include <stack>
#include <thread>

// fixed until we know the full size of our field
const int ROW = 7;
const int COL = 9;

// we dont care about Y-coordinate
typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

class TankAI
{
private:

	const int CUBES_SIZE = 29; // manually counted for now
	int grid[ROW][COL];

	const int CUBE_ID = 0;
	const int EMPTY_CELL = 1;
	const int TANK_ID = 2;

	const int PLAYER_ID_1 = 11;
	const int PLAYER_ID_2 = 12;
	const int PLAYER_ID_3 = 13;

	struct Cell {
		float parent_i;
		float parent_j;
		double f; // the lowest cost it takes to move to a cell
		double g; // move cost to move to a specified square
		double h; // estimated move cost from the square to the destination
	};

	// check if this "cell" is is a valid cell 
	bool isValid(float x, float z) {
		return (x >= 0) && (x < ROW) && (z >= 0) && (z < COL);
	}

	// check if given cell is blocked or not
	bool isUnblocked(glm::vec3 cubePositions[], float x, float z) {
		for (int i = 0; i < CUBES_SIZE; i++) {
			if (cubePositions[i].x == x && cubePositions[i].z == z) {
				return false;
			}			
			
		}
		return true;
	}

	// check if destination cell has been reached or not
	bool isDestination(float x, float z, glm::vec3 dest) {
		if (x == dest.x && z == dest.z) {
			return true;
		}
		else {
			return false;
		}
	}

	// calculate the h value
	double calculateHValue(float x, float z, glm::vec3 dest) {
		return ((double)sqrt((x - dest.x) * (x - dest.x) +
			(z - dest.z) * (z - dest.z)));
	}

	

public:

	TankAI() {
		
	}

	void populateGrid(glm::vec3 positions[], glm::vec3 tankPos) {
		for (int r = 0; r < ROW; r++) {
			for (int c = 0; c < COL; c++) {
				for (int i = 0; i < CUBES_SIZE; i++) {
					if (r == positions[i].x && c == positions[i].z) {
						grid[r][c] = 0;
					}
					else {
						grid[r][c] = 1;
					}
				}
			}
		}
	}

	void updateGrid() {

	}

	// locate a new path to trace
	void tracePath(Cell cellDetails[][COL], glm::vec3 dest) {

		int row = (int)dest.x;
		int col = (int)dest.z;

		float x = dest.x;
		float z = dest.z;

		stack<glm::vec3> Path;

		while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
			Path.push(glm::vec3(x, 0.0f, z));
			int temp_row = cellDetails[row][col].parent_i;
			int temp_col = cellDetails[row][col].parent_j;
			row = temp_row;
			col = temp_col;
		}

		Path.push(glm::vec3(x, 0.0f, z));
		while (!Path.empty()) {
			glm::vec3 pos = Path.top();
			Path.pop();

			//move(position, camPosition, pos.x, pos.z);

		}
	}


	void printGrid(int grid[][COL]) {
		for (int r = 0; r < ROW; r++) {
			cout << "\t";
			for (int c = 0; c < COL; c++) {
				cout << grid[r][c] << " ";
			}
			cout << endl;
		}
		cout << "--------" << endl;
	}

	// move to the specified location
	void move(glm::vec3& position, glm::vec3& camPosition, float x, float z) {
		float inc = 0.002f;
		if (position.x <= x) {
			position.x += inc;
			camPosition.x -= inc;
		}
		if (position.z <= z) {
			position.z += inc;
			camPosition.z -= inc;
		}
		// accomodate for rotation
	}

	// 
	void aStarSearch(glm::vec3 cubePositions[], glm::vec3& src, glm::vec3& dest) {
		if (isValid(src.x, src.z) == false) {
			//cout << "Source is invalid" << endl;
			return;
		}

		if (isValid(dest.x, dest.z) == false) {
			//cout << "Destination is invalid" << endl;
			return;
		}

		if (isUnblocked(cubePositions, src.x, src.z) == false || isUnblocked(cubePositions, dest.x, dest.z) == false) {
			return;
		}

		if (isDestination(src.x, src.z, dest) == true) {
			// refresh for a new path
			
			return;
		}

		bool closedList[ROW][COL];
		memset(closedList, false, sizeof(closedList));

		Cell cellDetails[ROW][COL];

		int i, j;

		for (i = 0; i < ROW; i++) {
			for (j = 0; j < COL; j++) {
				cellDetails[i][j].f = FLT_MAX;
				cellDetails[i][j].g = FLT_MAX;
				cellDetails[i][j].parent_i = -1;
				cellDetails[i][j].parent_j = -1;
			}
		}

		float new_i, new_j;
		new_i = src.x;
		new_j = src.z;

		i = (int) new_i;
		j = (int) new_j;
		cellDetails[i][j].f = 0.0;
		cellDetails[i][j].g = 0.0;
		cellDetails[i][j].h = 0.0;
		cellDetails[i][j].parent_i = i;
		cellDetails[i][j].parent_j = j;




	}

};

