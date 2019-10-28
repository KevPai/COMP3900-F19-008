#pragma once

#define ROW 9
#define COL 10

struct Point {
	int x;
	int y;
};

struct queueNode {
	Point pt;
	int dist;
};

bool isValid(int row, int col);
int BFS(int mat[][COL], Point src, Point dest);