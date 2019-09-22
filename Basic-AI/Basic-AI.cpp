// Basic-AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Header.h"

using namespace std;

void initField(char input[][MAX_SIZE], const int ROWS, const int COLS) {
	for (int r = 0; r < ROWS; r++) {
		if (r == 0 || r == ROWS - 1) {
			for (int c = 0; c < COLS; c++) {
				input[r][c] = 'B';

			}
		}
		else {
			for (int c = 0; c < COLS; c++) {
				if (c == 0 || c == COLS - 1) {
					input[r][c] = 'B';
				}
				else {
					input[r][c] = '.';
				}
			}
		}
	}

	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			cout << input[r][c] << ' ';
		}
		cout << endl;
	}
}

int main() {
	string input;
	bool done = false;

	int ROWS = 20;
	int COLS = 40;
	char field[20][40];

	char tank = 'T';


	initField(field, ROWS, COLS);



	return 0;
}
