#ifndef SEABATTLE_H
#define SEABATTLE_H

#include <stdio.h>
#include <stdbool.h>

#define FIELD_SIZE 10

typedef struct {
    int hasShip; // 0 - порожньо, 1 - корабель
    int isHit;   // 0 - не стріляли, 1 - мимо, 2 - влучили
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
#endif