#pragma once

#define MAX_SIZE 10

void move(int input[][MAX_SIZE], int icon, int row, int col);
void updateField(int input[][MAX_SIZE], const int ROWS, const int COLS);
void generateTank(int input[][MAX_SIZE], const int ROWS, const int COLS);