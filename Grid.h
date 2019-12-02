#pragma once

#include "Header.h"
#include "GridCell.h"
#include "CellDetails.h"
#include <iomanip>

class Grid {
private:

	std::vector<std::vector<GridCell>> grid = {};
	std::vector<glm::vec3> cubes;

	int rows; // rows representing the z values along the range
	int cols; // cols representing the x values along the range

	// number of rows and cols must be odd, because we are counting 
	// ex: -10 to 10 (including 0), so there would be 21 rows and cols to 
	// keep track of each (x, y) coord accordingly

	const int FREE_CELL = 1;
	const int BLOCKED_CELL = 0;

public:

	Grid();
	Grid(int rows, int cols, int cubeSize);
	~Grid() {
		grid.clear();
	}

	Grid& operator=(const Grid& rhs);

	void initGrid(); // initalize the grid with all open cells
	void initObjectPos(); // initalize objects in the grid marked with '0'
	void printGrid(); // testing the grid

	int getRowsize() const;
	int getColsize() const;

	GridCell getCellXZ(int x, int z); // get cell based on actual coordinates
	GridCell getCellP(int row, int col); // get cell based on its row, col position in the grid

	int getRow(GridCell cell); // get the row that this cell is in
	int getColumn(GridCell cell); // get the column that this cell is in

	//bool isWithinCell(float x, float z);

};