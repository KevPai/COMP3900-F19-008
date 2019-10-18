#include <iostream>
#include "Header.h"

using namespace std;

void move(int input[][MAX_SIZE], int icon, int row, int col) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 10; c++) {
			if (input[r][c] == 5) {
				input[r][c] == 1;
			}
		}
	}
	input[row][col] = icon;
}

void updateField(int input[][MAX_SIZE], const int ROWS, const int COLS) {
	for (int r = 0; r < ROWS; r++) {
		cout << '\t';
		for (int c = 0; c < COLS; c++) {
			cout << input[r][c] << ' ';
		}
		cout << endl;
	}
}

void generateTank(int input[][MAX_SIZE], const int ROWS, const int COLS) {
	input[0][0] = 5;
	cout << endl;
}