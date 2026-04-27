#ifndef SEABATTLE_H
#define SEABATTLE_H

#include <stdio.h>
#include <stdbool.h>

#define FIELD_SIZE 10

typedef struct {
    int hasShip;
    int isHit;
} Cell;

typedef struct {
    Cell grid[FIELD_SIZE][FIELD_SIZE];
    unsigned int N;
} Matrix;

typedef struct {
    int x;
    int y;
} Point;

void InitField(Matrix* m, unsigned int size);
void PrintField(Matrix* m);
void ProcessVolley(Matrix* m, int n, Point shots[]);
Point GetUserShot();
int LoadFieldFromFile(Matrix* m, const char* filename);
Point GetComputerShot(Matrix* m);
int CheckWinCondition(Matrix* m);
void PlaceShip(Matrix* m, int x, int y);
Point ConvertInputToPoint(char* input);

#endif