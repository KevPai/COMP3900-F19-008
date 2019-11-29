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

		int x = localGrid.getCellP(p.first, p.second).getRealX();
		int z = localGrid.getCellP(p.first, p.second).getRealZ();

		glm::vec3 dest = glm::vec3(x, 0.0f, z);

		// move here since we get the coords here
		// move(position, rotation, camPosition, dest);

		std::cout << "Path: " << p.first << p.second << std::endl;
	}
	
	return;
}

Grid TankAI::getGrid() {
	return localGrid;
}

void TankAI::move(glm::vec3& position, glm::vec3& rotation, glm::vec3& camPosition, glm::vec3 dest) {

	// will have to round down positions for the tank to move point-to-point

	int curX = round(position.x);
	int curZ = round(position.z);
	//position.x = curX, position.z = curZ;

	int destX = round(dest.x);
	int destZ = round(dest.z);

	// saving all possible roations of the tank, tank is defaulted at 270* rotation

	glm::vec3 north_west_r = glm::vec3(0.0f, 315.0f, 0.0f);
	glm::vec3 north_east_r = glm::vec3(0.0f, 225.0f, 0.0f);

	glm::vec3 south_west_r = glm::vec3(0.0f, 45.0f, 0.0f); 
	glm::vec3 south_east_r = glm::vec3(0.0f, 135.0f, 0.0f);

	glm::vec3 north_r = glm::vec3(0.0f, 270.0f, 0.0f);
	glm::vec3 south_r = glm::vec3(0.0f, 90.0f, 0.0f);

	glm::vec3 west_r = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 east_r = glm::vec3(0.0f, 180.0f, 0.0f);
	
	// check distance between position and dest points to see which direction it would go

	bool north_west = (position.x - 1 == dest.x && position.z - 1 == dest.z);
	bool north_east = (position.x + 1 == dest.x && position.z - 1 == dest.z);

	bool south_west = (position.x - 1 == dest.x && position.z + 1 == dest.z);
	bool south_east = (position.x + 1 == dest.x && position.z + 1 == dest.z);

	bool north = (position.x == dest.x && position.z - 1 == dest.z);
	bool south = (position.x == dest.x && position.z + 1 == dest.z);

	bool east = (position.x + 1 == dest.x && position.z == dest.z);
	bool west = (position.x - 1 == dest.x && position.z == dest.z);

	// checking each of the 8 directions from the current cell 
	// note: once the algo properly works, occurances of camPosition can be removed

	float inc = 0.1f;

	if (north_west) {
		rotation = north_west_r;
		for (float i = position.x, j = position.z; i >= dest.x && j >= dest.z; i += 0.1f, j -= 0.1f) {
			position.x -= inc;
			camPosition.x += inc;

			position.z -= inc;
			camPosition.z += inc;
		}

	}

	if (north_east) {
		rotation = north_east_r;
		for (float i = position.x, j = position.z; i <= dest.x && j >= dest.z; i += 0.1f, j -= 0.1f) {
			position.x += inc;
			camPosition.x -= inc;

			position.z -= inc;
			camPosition.z += inc;
		}
		
	}

	if (south_west) {
		rotation = south_west_r;
		for (float i = position.x, j = position.z; i >= dest.x && j <= dest.z; i -= 0.1f, j += 0.1f) {
			position.x -= inc;
			camPosition.x += inc;

			position.z += inc;
			camPosition.z -= inc;
		}

	}

	if (south_east) {
		rotation = south_east_r;
		for (float i = position.x, j = position.z; i <= dest.x && j <= dest.z; i += 0.1f, j += 0.1f) {
			position.x += inc;
			camPosition.x -= inc;

			position.z += inc;
			camPosition.z -= inc;
		}

	}

	if (north) {
		rotation = north_r;
		for (float i = position.z; i >= dest.z; i -= 0.1f) {
			position.z -= inc;
			camPosition.z += inc;
		}

	}

	if (south) {
		rotation = south_r;
		for (float i = position.z; i <= dest.z; i += 0.1f) {
			position.z += inc;
			camPosition.z -= inc;
		}

	}

	if (west) {
		rotation = west_r;
		for (float i = position.x; i >= dest.x; i -= 0.1f) {
			position.x -= inc;
			camPosition.x += inc;
		}

	}

	if (east) {
		rotation = east_r;
		for (float i = position.x; i <= dest.x; i += 0.1f) {
			position.x += inc;
			camPosition.x -= inc;
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

	std::vector<std::vector<bool>> closedList;
	closedList.resize(localGrid.getRowsize());
	for (int i = 0; i < localGrid.getRowsize(); i++) {
		closedList[i].resize(localGrid.getColsize());
	}
	//std::fill(&closedList[0][0], &closedList[0][0] + sizeof(closedList), false);
	memset(&closedList[0][0], false, sizeof(closedList));

	cells cellDetails;
	cellDetails.resize(localGrid.getRowsize());
	for (int i = 0; i < localGrid.getRowsize(); i++) {
		cellDetails[i].resize(localGrid.getColsize());
	}

	int i, j;
	for (i = 0; i < localGrid.getRowsize(); i++) {
		for (j = 0; j < localGrid.getColsize(); j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	i = srcRow; j = srcCol;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	std::set<pPair> openList;
	openList.insert(std::make_pair(0.0, std::make_pair(i, j)));

	bool foundDest = false;

	while (!openList.empty()) {
		pPair p = *openList.begin();

		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		for (int z = -1; z <= 1; z++) {
			for (int x = -1; x <= 1; x++) {
				double gNew, hNew, fNew;
				
				// process this cell if its valid
				if (isValid(z + i, x + j) == true) {
					// if the destination cell is the same as its current successor
					if (isDestination(z + i, x + j, destCell) == true) {
						// set parent of the destination cell
						cellDetails[z + i][x + j].parent_i = i;
						cellDetails[z + i][x + j].parent_j = j;
						tracePath(cellDetails, position, rotation, camPosition, destCell);
						foundDest = true;
						return;
					}
					else if (closedList[z + i][x + j] == false && isUnblocked(z + i, x + j)) {
						gNew = cellDetails[i][j].g + 1.0;
						hNew = calculateHValue(z + i, x + j, destCell);
						fNew = gNew + hNew;
					}
				} 
			}
		}
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