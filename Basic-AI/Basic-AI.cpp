// Basic-AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Header.h"
#include "BFS.h"

using namespace std;

int main() {
	char input = '0';

	const int ROWS = 9;
	const int COLS = 10;
	int field[ROWS][COLS] = {
		{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 0, 0, 1, 1, 1 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 0, 0, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 0, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 1, 1, 1, 0, 1 }
	};

	generateTank(field, ROWS, COLS);
	updateField(field, ROWS, COLS); // set up the field with tank and walls in place
	cout << endl;

	Point src = { 0, 0 };
	Point dest = { 8, 9 };

	int dist = BFS(field, src, dest);
	cout << "Distance by number of points taken: " << dist << endl;
	cout << "Reached dest: " << dest.x << ", "<< dest.y << endl;

	return 0;
}
