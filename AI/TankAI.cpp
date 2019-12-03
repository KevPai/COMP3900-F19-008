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
		glm::vec3& rotation, GridCell dest) {

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

		std::pair<int, int> real;
		real.first = x;
		real.second = z;
		movements.push_back(real);

		std::cout << "Path: (" << p.first << ", " <<p.second << ")" << std::endl;
		std::cout << "The real x and z of this location " << x << ", " << z << std::endl;
	}
	
	return;
}

void TankAI::adjustMovements() {
	
	for (size_t i = 0; i < movements.size(); i++) {
		int x = movements[i].first;
		int z = movements[i].second;
		//std::cout << "Altering " << x << ", " << z << std::endl;
		if (localGrid.getCellXZ(x, z - 1).getStatus() == 0) { // north block
			movements[i].second += 1;
			//std::cout << "Block at" << x << ", " << z - 1 << std::endl;
			continue;
		}
		if (localGrid.getCellXZ(x, z + 1).getStatus() == 0) { // south block
			movements[i].second -= 1;
			//std::cout << "Block at" << x << ", " << z + 1 << std::endl;
			continue;
		}
		if (localGrid.getCellXZ(x + 1, z).getStatus() == 0) { // east block
			movements[i].first -= 1;
			//std::cout << "Block at" << x + 1 << ", " << z << std::endl;
			continue;
		}
		if (localGrid.getCellXZ(x - 1, z).getStatus() == 0) { // west block
			movements[i].first += 1;
			//std::cout << "Block at" << x - 1 << ", " << z << std::endl;
			continue;
		}
		if (localGrid.getCellXZ(x - 1, z - 1).getStatus() == 0) { // north west block
			movements[i].first += 1;
			movements[i].second += 1;
			//std::cout << "Block at" << x - 1 << ", " << z - 1 << std::endl;
			continue;
		}
		if (localGrid.getCellXZ(x + 1, z - 1).getStatus() == 0) { // north east block
			movements[i].first -= 1;
			movements[i].second += 1;
			//std::cout << "Block at" << x + 1 << ", " << z - 1 << std::endl;
			continue;
		}
		if (localGrid.getCellXZ(x - 1, z + 1).getStatus() == 0) { // south west block
			movements[i].first += 1;
			movements[i].second -= 1;
			//std::cout << "Block at" << x - 1 << ", " << z + 1 << std::endl;
			continue;
		}
		if (localGrid.getCellXZ(x + 1, z + 1).getStatus() == 0) { // south east block
			movements[i].first -= 1;
			movements[i].second -= 1;
			//std::cout << "Block at" << x + 1 << ", " << z + 1 << std::endl;
			continue;
		}
	}
	
}

void TankAI::printMovements() {
	for (size_t i = 0; i < movements.size(); i++) {
		std::cout << movements[i].first << ", " << movements[i].second << std::endl;
	}
}

std::vector<std::pair<int, int>> TankAI::getMovements() {
	return movements;
}

Grid TankAI::getGrid() {
	return localGrid;
}

void TankAI::move(std::vector<std::pair<int, int>> moves, int &move, glm::vec3& position, glm::vec3& rotation) {

	if (move == moves.size()) {
		return;
	}

	float moveScale = 0.01f;
	int x = movements[move].first;
	int z = movements[move].second;

	// store rotations when moving
	glm::vec3 north_r = glm::vec3(0.0f, 270.0f, 0.0f);
	glm::vec3 south_r = glm::vec3(0.0f, 90.0f, 0.0f);

	glm::vec3 west_r = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 east_r = glm::vec3(0.0f, 180.0f, 0.0f);

	glm::vec3 north_west_r = glm::vec3(0.0f, 315.0f, 0.0f);
	glm::vec3 north_east_r = glm::vec3(0.0f, 225.0f, 0.0f);

	glm::vec3 south_west_r = glm::vec3(0.0f, 45.0f, 0.0f);
	glm::vec3 south_east_r = glm::vec3(0.0f, 135.0f, 0.0f);

	bool xAbsEqual = fabs(position.x - movements[move].first) <= 0.01;
	bool zAbsEqual = fabs(position.z - movements[move].second) <= 0.01;

	if (position.z < movements[move].second) { // south
		rotation = south_r;
		position.z += moveScale;
	}
	if (position.z > movements[move].second) { // north
		rotation = north_r;
		position.z -= moveScale;
	}
	if (position.x < movements[move].first) { // east
		rotation = east_r;
		position.x += moveScale;
	}
	if (position.x > movements[move].first) { // west
		rotation = west_r;
		position.x -= moveScale;
	}
	if (position.x < movements[move].first && position.z < movements[move].second) { // south east
		rotation = south_east_r;
		position.x += moveScale;
		position.z += moveScale;
	}
	if (position.x < movements[move].first && position.z > movements[move].second) { // north east
		rotation = north_east_r;
		position.x += moveScale;
		position.z -= moveScale;
	}
	if (position.x > movements[move].first && position.z > movements[move].second) { // north west
		rotation = north_west_r;
		position.x -= moveScale;
		position.z -= moveScale;
	}
	if (position.x > movements[move].first && position.z < movements[move].second) { // south west
		rotation = south_west_r;
		position.x -= moveScale;
		position.z += moveScale;
	}
	if (xAbsEqual && zAbsEqual && move < (int) moves.size()) {
		position.x = (float) x;
		position.z = (float) z;
		move++;
	}

	//std::cout << position.x << ", " << position.z << std::endl;
}

void TankAI::performSearch(glm::vec3& position, glm::vec3& rotation, glm::vec3 src, glm::vec3 dest) {

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

		double gNew, hNew, fNew;

		// NORTH DIRECTION

		if (isValid(i - 1, j) == true)
		{

			if (isDestination(i - 1, j, destCell) == true)
			{

				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				std::cout << "The destination cell is found" << std::endl;
				tracePath(cellDetails, position, rotation, destCell);
				foundDest = true;
				return;
			}

			else if (closedList[i - 1][j] == false &&
				isUnblocked(i - 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i - 1, j, destCell);
				fNew = gNew + hNew;


				if (cellDetails[i - 1][j].f == FLT_MAX ||
					cellDetails[i - 1][j].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i - 1, j)));

					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}

		// SOUTH DIRECTION

		if (isValid(i + 1, j) == true)
		{

			if (isDestination(i + 1, j, destCell) == true)
			{

				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				std::cout << "The destination cell is found" << std::endl;
				tracePath(cellDetails, position, rotation, destCell);
				foundDest = true;
				return;
			}

			else if (closedList[i + 1][j] == false &&
				isUnblocked(i + 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i + 1, j, destCell);
				fNew = gNew + hNew;


				if (cellDetails[i + 1][j].f == FLT_MAX ||
					cellDetails[i + 1][j].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i + 1, j)));

					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		// EAST DIRECTION

		if (isValid(i, j + 1) == true)
		{

			if (isDestination(i, j + 1, destCell) == true)
			{

				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				std::cout << "The destination cell is found" << std::endl;
				tracePath(cellDetails, position, rotation, destCell);
				foundDest = true;
				return;
			}

			else if (closedList[i][j + 1] == false &&
				isUnblocked(i, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j + 1, destCell);
				fNew = gNew + hNew;


				if (cellDetails[i][j + 1].f == FLT_MAX ||
					cellDetails[i][j + 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i, j + 1)));

					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}

		// WEST DIRECTION

		if (isValid(i, j - 1) == true)
		{

			if (isDestination(i, j - 1, destCell) == true)
			{

				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				std::cout << "The destination cell is found" << std::endl;
				tracePath(cellDetails, position, rotation, destCell);
				foundDest = true;
				return;
			}

			else if (closedList[i][j - 1] == false &&
				isUnblocked(i, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j - 1, destCell);
				fNew = gNew + hNew;


				if (cellDetails[i][j - 1].f == FLT_MAX ||
					cellDetails[i][j - 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i, j - 1)));

					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}

		// NORTH EAST DIRECTION

		if (isValid(i - 1, j + 1) == true)
		{

			if (isDestination(i - 1, j + 1, destCell) == true)
			{

				cellDetails[i - 1][j + 1].parent_i = i;
				cellDetails[i - 1][j + 1].parent_j = j;
				std::cout << "The destination cell is found" << std::endl;
				tracePath(cellDetails, position, rotation, destCell);
				foundDest = true;
				return;
			}

			else if (closedList[i - 1][j + 1] == false &&
				isUnblocked(i - 1, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i - 1, j + 1, destCell);
				fNew = gNew + hNew;


				if (cellDetails[i - 1][j + 1].f == FLT_MAX ||
					cellDetails[i - 1][j + 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i - 1, j + 1)));

					cellDetails[i - 1][j + 1].f = fNew;
					cellDetails[i - 1][j + 1].g = gNew;
					cellDetails[i - 1][j + 1].h = hNew;
					cellDetails[i - 1][j + 1].parent_i = i;
					cellDetails[i - 1][j + 1].parent_j = j;
				}
			}
		}

		// NORTH WEST DIRECTION

		if (isValid(i - 1, j - 1) == true)
		{

			if (isDestination(i - 1, j - 1, destCell) == true)
			{

				cellDetails[i - 1][j - 1].parent_i = i;
				cellDetails[i - 1][j - 1].parent_j = j;
				std::cout << "The destination cell is found" << std::endl;
				tracePath(cellDetails, position, rotation, destCell);
				foundDest = true;
				return;
			}

			else if (closedList[i - 1][j - 1] == false &&
				isUnblocked(i - 1, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i - 1, j - 1, destCell);
				fNew = gNew + hNew;


				if (cellDetails[i - 1][j - 1].f == FLT_MAX ||
					cellDetails[i - 1][j - 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i - 1, j - 1)));

					cellDetails[i - 1][j - 1].f = fNew;
					cellDetails[i - 1][j - 1].g = gNew;
					cellDetails[i - 1][j - 1].h = hNew;
					cellDetails[i - 1][j - 1].parent_i = i;
					cellDetails[i - 1][j - 1].parent_j = j;
				}
			}
		}

		// SOUTH EAST DIRECTION

		if (isValid(i + 1, j + 1) == true)
		{

			if (isDestination(i + 1, j + 1, destCell) == true)
			{

				cellDetails[i + 1][j + 1].parent_i = i;
				cellDetails[i + 1][j + 1].parent_j = j;
				std::cout << "The destination cell is found" << std::endl;
				tracePath(cellDetails, position, rotation, destCell);
				foundDest = true;
				return;
			}

			else if (closedList[i + 1][j + 1] == false &&
				isUnblocked(i + 1, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i + 1, j + 1, destCell);
				fNew = gNew + hNew;


				if (cellDetails[i + 1][j + 1].f == FLT_MAX ||
					cellDetails[i + 1][j + 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i + 1, j + 1)));

					cellDetails[i + 1][j + 1].f = fNew;
					cellDetails[i + 1][j + 1].g = gNew;
					cellDetails[i + 1][j + 1].h = hNew;
					cellDetails[i + 1][j + 1].parent_i = i;
					cellDetails[i + 1][j + 1].parent_j = j;
				}
			}
		}

		// SOUTH WEST DIRECTION

		if (isValid(i + 1, j - 1) == true)
		{

			if (isDestination(i + 1, j - 1, destCell) == true)
			{

				cellDetails[i + 1][j - 1].parent_i = i;
				cellDetails[i + 1][j - 1].parent_j = j;
				std::cout << "The destination cell is found" << std::endl;
				tracePath(cellDetails, position, rotation, destCell);
				foundDest = true;
				return;
			}

			else if (closedList[i + 1][j - 1] == false &&
				isUnblocked(i + 1, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i + 1, j - 1, destCell);
				fNew = gNew + hNew;


				if (cellDetails[i + 1][j - 1].f == FLT_MAX ||
					cellDetails[i + 1][j - 1].f > fNew)
				{
					openList.insert(std::make_pair(fNew,
						std::make_pair(i + 1, j - 1)));

					cellDetails[i + 1][j - 1].f = fNew;
					cellDetails[i + 1][j - 1].g = gNew;
					cellDetails[i + 1][j - 1].h = hNew;
					cellDetails[i + 1][j - 1].parent_i = i;
					cellDetails[i + 1][j - 1].parent_j = j;
				}
			}
		}

	}

	if (foundDest == false) {
		std::cout << "failed to find the destination cell" << std::endl;
	}
	return;
}