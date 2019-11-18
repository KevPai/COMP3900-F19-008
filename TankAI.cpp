#include "TankAI.h"

TankAI::TankAI(glm::vec3 cubePositions[], int cubesSize) {
	for (int i = 0; i < cubesSize; i++) {
		cubes.push_back(cubePositions[i]);
	}
	initGrid();
}

int TankAI::round(float f) {
	return f + (f < 0 ? -0.5 : +0.5);
}

/*void TankAI::printGrid() {
	for (int r = 0; r < ROW; r++) {
		std::cout << "\t";
		for (int c = 0; c < COL; c++) {
			std::cout << grid[r][c] << " ";
		}
		std::cout << std::endl;
	}
}*/

void TankAI::initGrid() {
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			grid[r][c] = 1;
		}
	}

	for (size_t i = 0; i < cubes.size(); i++) {
		int cubeX = (int)cubes[i].x;
		int cubeZ = (int)cubes[i].z;

		grid[cubeX][cubeZ] = 0;
	}
}

bool TankAI::isValid(float x, float z) {
	return (x >= 0) && (x < ROW) && (z >= 0) && (z < COL);
}

bool TankAI::isUnblocked(int x, int z) {
	if (grid[x][z] == 1) {
		return true;
	}
	else {
		return false;
	}
}

bool TankAI::isDestination(int x, int z, glm::vec3 dest) {
	if (x == round(dest.x) && z == round(dest.z)) {
		return true;
	}
	else {
		return false;
	}
}

double TankAI::calculateHValue(int x, int z, glm::vec3 dest) {
	return ((double) sqrt ((x-round(dest.x))*(x-round(dest.x)) 
		+ (z-round(dest.z))*(z-round(dest.z))));
}

void TankAI::tracePath(Cell cellDetails[][COL], glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest) {
	int row = round(dest.x);
	int col = round(dest.z);

	std::stack<glm::vec3> Path;

	while (!(cellDetails[row][col].parent_x == row 
		&& cellDetails[row][col].parent_z == col)) {
		Path.push(glm::vec3(row, 0, col));
		int temp_row = cellDetails[row][col].parent_x;
		int temp_col = cellDetails[row][col].parent_z;
		row = temp_row;
		col = temp_col;
	}

	Path.push(glm::vec3(row, 0, col));
	while (!Path.empty()) {
		glm::vec3 current = Path.top();
		Path.pop();

		// do the moving here
		// move(position, rotation, camPosition, current);
	}

	return;
	
}

void TankAI::move(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest) {

	if (round(position.x == dest.x) && round(position.z == dest.z)) {
		return;
	}

	// saving all possible roations of the tank, tank is defaulted at 90* rotation
	glm::vec3 top_left = glm::vec3(0.0f, 135.0f, 0.0f);
	glm::vec3 top_right = glm::vec3(0.0f, 45.0f, 0.0f);

	glm::vec3 bottom_left = glm::vec3(0.0f, 225.0f, 0.0f);
	glm::vec3 bottom_right = glm::vec3(0.0f, 315.0f, 0.0f);

	glm::vec3 forward = glm::vec3(0.0f, 90.0f, 0.0f);
	glm::vec3 backward = glm::vec3(0.0f, 270.0f, 0.0f);

	glm::vec3 left = glm::vec3(0.0f, 180.0f, 0.0f);
	glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);
	
	// check if the difference between the tank's current position is within a certain distance
	// of the destination to go in a specified direction
	bool diag_topleft = (position.x + 1 == dest.x && position.z + 1 == dest.z);
	bool diag_topright = (position.x - 1 == dest.x && position.z + 1 == dest.z);

	bool diag_botleft = (position.x + 1 == dest.x && position.z - 1 == dest.z);
	bool diag_botright = (position.x - 1 == dest.x && position.z - 1 == dest.z);

	bool vert_forward = (position.x == dest.x && position.z + 1 == dest.z);
	bool vert_backward = (position.x == dest.x && position.z - 1 == dest.z);

	// x positive to the left of origin
	bool horizontal_left = (position.x + 1 == dest.x && position.z == dest.z);
	bool horizontal_right = (position.x - 1 == dest.x && position.z == dest.z);

	// checking each of the 8 directions from the current cell 
	// note: once the algo properly works, occurances of camPosition can be removed

	float inc = 0.1f;

	if (diag_topleft) {
		rotation = top_left;
		for (float i = position.x, j = position.z; i <= dest.x && j <= dest.z; i += 0.1f, j += 0.1f) {
			position.x += inc;
			camPosition.x -= inc;

			position.z += inc;
			camPosition.z -= inc;
		}

	}

	if (diag_topright) {
		rotation = top_right;
		for (float i = position.x, j = position.z; i >= dest.x && j <= dest.z; i -= 0.1f, j += 0.1f) {
			position.x -= inc;
			camPosition.x += inc;

			position.z += inc;
			camPosition.z -= inc;
		}
		
	}

	if (diag_botleft) {
		rotation = bottom_left;
		for (float i = position.x, j = position.z; i <= dest.x && j >= dest.z; i += 0.1f, j -= 0.1f) {
			position.x += inc;
			camPosition.x -= inc;

			position.z -= inc;
			camPosition.z += inc;
		}

	}

	if (diag_botright) {
		rotation = bottom_right;
		for (float i = position.x, j = position.z; i >= dest.x && j >= dest.z; i -= 0.1f, j -= 0.1f) {
			position.x -= inc;
			camPosition.x += inc;

			position.z -= inc;
			camPosition.z += inc;
		}

	}

	if (vert_forward) {
		rotation = forward;
		for (float i = position.z; i <= dest.z; i += 0.1f) {
			position.z += inc;
			camPosition.z -= inc;
		}

	}

	if (vert_backward) {
		rotation = backward;
		for (float i = position.z; i >= dest.z; i -= 0.1f) {
			position.z -= inc;
			camPosition.z += inc;
		}

	}

	if (horizontal_left) {
		rotation = left;
		for (float i = position.x; i <= dest.x; i += 0.1f) {
			position.x += inc;
			camPosition.x -= inc;
		}

	}

	if (horizontal_right) {
		rotation = right;
		for (float i = position.x; i >= dest.x; i -= 0.1f) {
			position.x -= inc;
			camPosition.x += inc;
		}

	}

}

void TankAI::performSearch(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 src, glm::vec3 dest) {

	int srcX = round(src.x);
	int srcZ = round(src.z);

	int destX = round(dest.x);
	int destZ = round(dest.z);

	if (isValid(src.x, src.z) == false) {
		std::cout << "src invalid" << std::endl;
		return;
	}
	if (isValid(dest.x, dest.z) == false) {
		std::cout << "dest invalid" << std::endl;
		return;
	}
	if (isUnblocked(srcX, srcZ) == false) {
		std::cout << "src is blocked" << std::endl;
		return;
	}
	if (isUnblocked(destX, destZ) == false) {
		std::cout << "dest is blocked" << std::endl;
		return;
	}
	if (isDestination(srcX, srcZ, dest) == true) {
		std::cout << "we are already at the destination" << std::endl;
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
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_x = -1;
			cellDetails[i][j].parent_z = -1;
		}
	}

	i = srcX; 
	j = srcZ;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_x = i;
	cellDetails[i][j].parent_z = j;

	std::set<pPair> openList;
	openList.insert(std::make_pair(0.0, std::make_pair(i, j)));

	bool foundDest = false;

	// check forward (north) direction
	// check backward (south) direction
	// check right (east) direction
	// check left (west) direction
	// check top-left (north-west) direction
	// check top-right (north-east) direction
	// check bottom-left (south-west) direction
	// check bottom-right (south-east) direction
}