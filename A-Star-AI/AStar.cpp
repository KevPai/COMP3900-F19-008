#include "AStar.h"

using namespace std;

void updateGrid(int grid[][COL]) {
	for (int r = 0; r < ROW; r++) {
		cout << "\t";
		for (int c = 0; c < COL; c++) {
			cout << grid[r][c] << " ";
		}
		cout << endl;
	}
}

void move(int grid[][COL], int row, int col) {
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			if (grid[r][c] == 5) {
				grid[r][c] = 1;
			}
		}
	}
	grid[row][col] = 5;
}

bool isValid(int row, int col)
{
	return (row >= 0) && (row < ROW) &&
		(col >= 0) && (col < COL);
}

bool isUnblocked(int grid[][COL], int row, int col)
{
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

double calculateHValue(int row, int col, Pair dest)
{
	return ((double)sqrt((row - dest.first) * (row - dest.first)
		+ (col - dest.second) * (col - dest.second)));
}

void tracePath(int grid[][COL], cell cellDetails[][COL], Pair dest)
{
	cout << ("The Path is ") << endl;
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
		&& cellDetails[row][col].parent_j == col))
	{
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty())
	{
		pair<int, int> p = Path.top();
		Path.pop();

		cin.ignore();
		move(grid, p.first, p.second);

		updateGrid(grid);

		cout << "-> (" << p.first << ", " << p.second << ") " << endl;
	}

	return;
}

void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
	if (isValid(src.first, src.second) == false)
	{
		cout << ("Source is invalid\n");
		return;
	}

	if (isValid(dest.first, dest.second) == false)
	{
		cout << ("Destination is invalid\n");
		return;
	}

	if (isUnblocked(grid, src.first, src.second) == false ||
		isUnblocked(grid, dest.first, dest.second) == false)
	{
		cout << ("Source or the destination is blocked\n");
		return;
	}

	if (isDestination(src.first, src.second, dest) == true)
	{
		cout << ("We are already at the destination\n");
		return;
	}

	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	cell cellDetails[ROW][COL];

	int i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	set<pPair> openList;

	openList.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();
		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;
		
		double gNew, hNew, fNew;

		// NORTH DIRECTION
 
		if (isValid(i - 1, j) == true)
		{
			if (isDestination(i - 1, j, dest) == true)
			{
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				cout << ("The destination cell is found\n") << endl;
				tracePath(grid, cellDetails, dest);
				foundDest = true;
				return;
			}
			else if (closedList[i - 1][j] == false &&
				isUnblocked(grid, i - 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i - 1, j, dest);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j].f == FLT_MAX ||
					cellDetails[i - 1][j].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i - 1, j)));

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
			if (isDestination(i + 1, j, dest) == true)
			{
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				cout << ("The destination cell is found\n");
				tracePath(grid, cellDetails, dest);
				foundDest = true;
				return;
			} else if (closedList[i + 1][j] == false &&
				isUnblocked(grid, i + 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i + 1, j, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j].f == FLT_MAX ||
					cellDetails[i + 1][j].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i + 1, j)));

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
			if (isDestination(i, j + 1, dest) == true)
			{
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				cout << ("The destination cell is found\n");
				tracePath(grid, cellDetails, dest);
				foundDest = true;
				return;
			} else if (closedList[i][j + 1] == false &&
				isUnblocked(grid, i, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j + 1].f == FLT_MAX ||
					cellDetails[i][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i, j + 1)));

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
			if (isDestination(i, j - 1, dest) == true)
			{ 
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				cout << ("The destination cell is found\n");
				tracePath(grid, cellDetails, dest);
				foundDest = true;
				return;
			} else if (closedList[i][j - 1] == false &&
				isUnblocked(grid, i, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j - 1].f == FLT_MAX ||
					cellDetails[i][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i, j - 1)));

					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}

		// NORTH-EAST DIRECTION

		if (isValid(i - 1, j + 1) == true)
		{
			if (isDestination(i - 1, j + 1, dest) == true)
			{
				cellDetails[i - 1][j + 1].parent_i = i;
				cellDetails[i - 1][j + 1].parent_j = j;
				cout << ("The destination cell is found\n");
				tracePath(grid, cellDetails, dest);
				foundDest = true;
				return;
			}
			else if (closedList[i - 1][j + 1] == false &&
				isUnblocked(grid, i - 1, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i - 1, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j + 1].f == FLT_MAX ||
					cellDetails[i - 1][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i - 1, j + 1)));

					cellDetails[i - 1][j + 1].f = fNew;
					cellDetails[i - 1][j + 1].g = gNew;
					cellDetails[i - 1][j + 1].h = hNew;
					cellDetails[i - 1][j + 1].parent_i = i;
					cellDetails[i - 1][j + 1].parent_j = j;
				}
			}
		}

		// NORTH-WEST DIRECTION

		if (isValid(i - 1, j - 1) == true)
		{
			if (isDestination(i - 1, j - 1, dest) == true)
			{
				cellDetails[i - 1][j - 1].parent_i = i;
				cellDetails[i - 1][j - 1].parent_j = j;
				cout << ("The destination cell is found\n");
				tracePath(grid, cellDetails, dest);
				foundDest = true;
				return;
			}
			else if (closedList[i - 1][j - 1] == false &&
				isUnblocked(grid, i - 1, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i - 1, j - 1, dest);
				fNew = gNew + hNew;


				if (cellDetails[i - 1][j - 1].f == FLT_MAX ||
					cellDetails[i - 1][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));

					cellDetails[i - 1][j - 1].f = fNew;
					cellDetails[i - 1][j - 1].g = gNew;
					cellDetails[i - 1][j - 1].h = hNew;
					cellDetails[i - 1][j - 1].parent_i = i;
					cellDetails[i - 1][j - 1].parent_j = j;
				}
			}
		}

		// SOUTH-EAST DIRECTION

		if (isValid(i + 1, j + 1) == true)
		{
			if (isDestination(i + 1, j + 1, dest) == true)
			{
				cellDetails[i + 1][j + 1].parent_i = i;
				cellDetails[i + 1][j + 1].parent_j = j;
				cout << ("The destination cell is found\n");
				tracePath(grid, cellDetails, dest);
				foundDest = true;
				return;
			}

			else if (closedList[i + 1][j + 1] == false &&
				isUnblocked(grid, i + 1, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i + 1, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j + 1].f == FLT_MAX ||
					cellDetails[i + 1][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i + 1, j + 1)));

					cellDetails[i + 1][j + 1].f = fNew;
					cellDetails[i + 1][j + 1].g = gNew;
					cellDetails[i + 1][j + 1].h = hNew;
					cellDetails[i + 1][j + 1].parent_i = i;
					cellDetails[i + 1][j + 1].parent_j = j;
				}
			}
		}

		// SOUTH-WEST DIRECTION

		if (isValid(i + 1, j - 1) == true)
		{
			if (isDestination(i + 1, j - 1, dest) == true)
			{
				cellDetails[i + 1][j - 1].parent_i = i;
				cellDetails[i + 1][j - 1].parent_j = j;
				cout << ("The destination cell is found\n");
				tracePath(grid, cellDetails, dest);
				foundDest = true;
				return;
			}

			else if (closedList[i + 1][j - 1] == false &&
				isUnblocked(grid, i + 1, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.414;
				hNew = calculateHValue(i + 1, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j - 1].f == FLT_MAX ||
					cellDetails[i + 1][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i + 1, j - 1)));

					cellDetails[i + 1][j - 1].f = fNew;
					cellDetails[i + 1][j - 1].g = gNew;
					cellDetails[i + 1][j - 1].h = hNew;
					cellDetails[i + 1][j - 1].parent_i = i;
					cellDetails[i + 1][j - 1].parent_j = j;
				}
			}
		}
	}

	if (foundDest == false)
		cout << ("Failed to find the Destination Cell\n");

	return;
}