#pragma once

#define MAX_SIZE 40

int checkDistance(char icon, int pos, int);
bool hasCollided();

void initField(char input[][MAX_SIZE], const int ROWS, const int COLS);
char generateTank(char input[]);