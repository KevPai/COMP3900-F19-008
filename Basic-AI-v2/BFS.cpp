#include "BFS.h"
#include "Header.h"
#include <iostream>
#include <queue>

bool isValid(int row, int col) {
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

int BFS(int mat[][COL], Point src, Point dest) {

	int rowNum[] = { -1, 0, 0, 1 };
	int colNum[] = { 0, -1, 1, 0 };

	if (!mat[src.x][src.y] || !mat[dest.x][dest.y]) {
		return -1;
	}

	bool visited[ROW][COL];
	memset(visited, false, sizeof visited);

	visited[src.x][src.y] = true;

	std::queue<queueNode> q;
	queueNode s = { src, 0 };
	q.push(s);

	while (!q.empty()) {
		queueNode cur = q.front();
		Point pt = cur.pt;

		if (pt.x == dest.x && pt.y == dest.y) {
			updateField(mat, ROW, COL);
			return cur.dist;
		}

		q.pop();

		int dX, dY;
		dX = pt.x;
		dY = pt.y;

		std::cout << "Position of tank: " << dX << ", " << dY << std::endl;

		for (int i = 0; i < 4; i++) {
			int row = pt.x + rowNum[i];
			int col = pt.y + colNum[i];

			mat[dX][dY] = 1;
			

			if (isValid(row, col) && mat[row][col] && !visited[row][col]) {
				move(mat, 5, row, col);
				std::cin.ignore();
				
				visited[row][col] = true;
				updateField(mat, ROW, COL);
				
				std::cout << std::endl;
				/*if ((row + 1 && col == 0)) {
					visited[row + 1][col] = true;
				}
				else if ((row - 1 && col == 0)) {
					visited[row - 1][col] = true;
				}
				else if ((row && col + 1 == 0)) {
					visited[row][col + 1] = true;
				}
				else if ((row && col - 1 == 0)) {
					visited[row][col - 1] = true;
				}*/
				queueNode Adjcell = { {row, col}, cur.dist + 1 };
				q.push(Adjcell);
				
			}
		}
	}

	return -1;
}