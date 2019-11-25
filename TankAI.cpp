#include "TankAI.h"

TankAI::TankAI(int rows, int cols, int cubesSize) {

	Grid grid(rows, cols, cubesSize);
	grid.initGrid();
	grid.initObjectPos();
	grid.printGrid();
	localGrid = grid;
}

int TankAI::round(float f) {
	return f + (f < 0 ? -0.5 : +0.5);
}

bool TankAI::isValid(int row, int col) {
	return (row >= 0) && (row < localGrid.getRowsize()) 
		&& (col >= 0) && (col < localGrid.getColsize());
}

bool TankAI::isUnblocked(int row, int col) {
	if (localGrid.getCellP(row, col).getStatus() == 1) {
		return true;
	}
	else {
		return false;
	}
}

bool TankAI::isDestination(int row, int col, GridCell dest) {

	int destRow = localGrid.getRow(dest);
	int destCol = localGrid.getColumn(dest);

	if (row == destRow && col == destCol) {
		return true;
	}
	else {
		return false;
	}
}

double TankAI::calculateHValue(int row, int col, GridCell dest) {
	
	int destRow = localGrid.getRow(dest);
	int destCol = localGrid.getColumn(dest);

	return ((double) sqrt ((row-destRow)*(row-destRow) 
		+ (col-destCol)*(col-destCol)));
}

void TankAI::initCellDetails(cells& cellDetails) {
	cellDetails.resize(localGrid.getRowsize());
	for (int i = 0; i < localGrid.getRowsize(); i++) {
		cellDetails[i].resize(localGrid.getColsize());
	}

	for (int i = 0; i < localGrid.getRowsize(); i++) {
		for (int j = 0; j < localGrid.getColsize(); j++) {
			std::cout << cellDetails[i][j].parent_i << std::endl;
		}
	}
}

void TankAI::tracePath(cells cellDetails, glm::vec3& position,
		glm::vec3& rotation, glm::vec3& camPosition, GridCell dest) {

	int row = localGrid.getRow(dest);
	int col = localGrid.getColumn(dest);

	std::stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
		&& cellDetails[row][col].parent_j == col)) {
		Path.push(std::make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(std::make_pair(row, col));
	while (!Path.empty()) {
		std::pair<int, int> p = Path.top();
		Path.pop();

		// move here since we get the coords here
	}
	
	return;
}

void TankAI::move(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest) {

	int curX = round(position.x);
	int curZ = round(position.z);

	int destX = round(dest.x);
	int destZ = round(dest.z);

	GridCell curCell = localGrid.getCellXZ(curX, curZ);
	GridCell destCell = localGrid.getCellXZ(destX, destZ);

	// saving all possible roations of the tank, tank is defaulted at 270* rotation
	glm::vec3 top_left = glm::vec3(0.0f, 315.0f, 0.0f); //315
	glm::vec3 top_right = glm::vec3(0.0f, 225.0f, 0.0f); //225

	glm::vec3 bottom_left = glm::vec3(0.0f, 45.0f, 0.0f); //45
	glm::vec3 bottom_right = glm::vec3(0.0f, 135.0f, 0.0f); //135

	glm::vec3 forward = glm::vec3(0.0f, 270.0f, 0.0f);
	glm::vec3 backward = glm::vec3(0.0f, 90.0f, 0.0f);

	glm::vec3 left = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 right = glm::vec3(0.0f, 180.0f, 0.0f);
	
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

	// referencing to positions
	int srcX = round(src.x);
	int srcZ = round(src.z);

	int destX = round(dest.x);
	int destZ = round(dest.z);

	// reference to the cells
	GridCell srcCell = localGrid.getCellXZ(srcX, srcZ);
	GridCell destCell = localGrid.getCellXZ(destX, destZ);

	// reference to the row/col of cells
	int srcRow = localGrid.getRow(srcCell);
	int srcCol = localGrid.getColumn(srcCell);

	int destRow = localGrid.getRow(destCell);
	int destCol = localGrid.getColumn(destCell);

	initCellDetails(cellDetails);

	if (isValid(srcRow, srcCol) == false) {
		std::cout << "src invalid" << std::endl;
		return;
	}
	if (isValid(destRow, destCol) == false) {
		std::cout << "dest invalid" << std::endl;
		return;
	}
	if (isUnblocked(srcRow, srcCol) == false) {
		std::cout << "src is blocked" << std::endl;
		return;
	}
	if (isUnblocked(destRow, destCol) == false) {
		std::cout << "dest is blocked" << std::endl;
		return;
	}
	if (isDestination(srcRow, srcCol, destCell) == true) {
		std::cout << "we are already at the destination" << std::endl;
		return;
	}

	// check forward (north) direction
	// check backward (south) direction
	// check right (east) direction
	// check left (west) direction
	// check top-left (north-west) direction
	// check top-right (north-east) direction
	// check bottom-left (south-west) direction
	// check bottom-right (south-east) direction
}