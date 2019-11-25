#include "Grid.h"

Grid::Grid() {
	rows = 0;
	cols = 0;
}

Grid::Grid(int rows, int cols, int cubeSize) {
	if (rows % 2 == 0 || cols % 2 == 0) {
		std::cout << "Number of rows/cols must be odd" << std::endl;
	}
	else {
		this->rows = rows;
		this->cols = cols;
	}
	for (int i = 0; i < cubeSize; i++) {
		cubes.push_back(cubePositions[i]);
	}

}

Grid& Grid::operator=(const Grid& rhs) {
	grid = rhs.grid;
	rows = rhs.rows;
	cols = rhs.cols;
	cubes = rhs.cubes;
	return *this;
}

void Grid::initGrid() {

	// this is to set the ranges of the x and z

	int rangeX = (cols / 2);
	int rangeZ = (rows / 2);

	// create base grid, all open cells

	grid.resize(rows);
	for (int i = 0; i < rows; i++) {
		grid[i].resize(cols);
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].setStatus(FREE_CELL); // set as an open cell
		}
	}

	// setting up the (x, z) for reference
	int z = -rangeZ;
	int x = -rangeX;
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols; j++) {
			grid[i][j].setRealX(x);
			grid[i][j].setRealZ(z);
			x++;
		}
		z++;
		x = -rangeX;
	}

}

void Grid::initObjectPos() {
	for (size_t i = 0; i < cubes.size(); i++) {
		int cubeX = (int) cubes[i].x;
		int cubeZ = (int) cubes[i].z;

		for (int r = 0; r < getRowsize(); r++) {
			for (int c = 0; c < getColsize(); c++) {
				if (grid[r][c].getRealX() == cubeX && grid[r][c].getRealZ() == cubeZ) {
					grid[r][c].setStatus(BLOCKED_CELL);
				}
			}
		}
	}
}

GridCell Grid::getCellXZ(int x, int z) {
	for (int i = 0; i < getRowsize(); i++) {
		for (int j = 0; j < getColsize(); j++) {
			if (grid[i][j].getRealX() == x && grid[i][j].getRealZ() == z) {
				return grid[i][j];
			}
		} 
	}
	return grid[0][0]; // cell not found
}

int Grid::getRow(GridCell cell) {
	for (int i = 0; i < getRowsize(); i++) {
		for (int j = 0; j < getColsize(); j++) {
			if (grid[i][j].getRealX() == cell.getRealX() && grid[i][j].getRealZ() == cell.getRealZ()) {
				return i;
			}
		}
	}
	return 0; // this cell is not in any row
}

int Grid::getColumn(GridCell cell) {
	for (int i = 0; i < getRowsize(); i++) {
		for (int j = 0; j < getColsize(); j++) {
			if (grid[i][j].getRealX() == cell.getRealX() && grid[i][j].getRealZ() == cell.getRealZ()) {
				return j;
			}
		}
	}
	return 0; // this cell is not in any column
}

GridCell Grid::getCellP(int row, int col) {
	return grid[row][col];
}

void Grid::printGrid() {
	for (int i = 0; i < getRowsize(); i++) {
		for (int j = 0; j < getColsize(); j++) {
			std::cout << grid[i][j].getStatus() << " ";
		}
		std::cout << std::endl;
	}
}

int Grid::getRowsize() const {
	return grid.size();
}

int Grid::getColsize() const {
	return grid[0].size();
}

