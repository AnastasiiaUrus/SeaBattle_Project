/* Задача: 18. SeaBattle-1
 * Група: Статистика 1
 * Прізвище: Урус Анастасія, Гетало Софія
 */


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

// Нова структура для координат пострілу
typedef struct {
    int x;
    int y;
} Point;

// Прототипи функцій
void InitField(Matrix* m, unsigned int size);
void PrintField(Matrix* m);
void ProcessVolley(Matrix* m, int n, Point shots[]);
Point GetUserShot();
#endif