#include "SeaBattle.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void InitField(Matrix* m, unsigned int size) {
    m->N = size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            m->grid[i][j].hasShip = 0;
            m->grid[i][j].isHit = 0;
        }
    }
}

void PrintField(Matrix* m) {
    printf("\n    "); 
    for (int i = 0; i < m->N; i++) printf("%c ", 'A' + i); // Букви зверху (Y)
    printf("\n");

    for (int i = 0; i < m->N; i++) {
        printf("%2d |", i + 1); // Цифри збоку (X)
        for (int j = 0; j < m->N; j++) {
            // ЛОГІКА ВІДОБРАЖЕННЯ:
            if (m->grid[i][j].isHit == 0) {
                printf(". "); 
            } 
            else if (m->grid[i][j].isHit == 1) {
                printf("0 "); // ПРОМАХ (відображаємо ноликом)
            } 
            else if (m->grid[i][j].isHit == 2) {
                printf("X "); // ВЛУЧАННЯ (відображаємо іксом)
            }
        }
        printf("\n");
    }
}

void ProcessVolley(Matrix* m, int n, Point shots[]) {
    int hits = 0;
    int misses = 0;
    for (int i = 0; i < n; i++) {
        int x = shots[i].x;
        int y = shots[i].y;
        if (x >= 0 && x < m->N && y >= 0 && y < m->N) {
            if (m->grid[x][y].hasShip == 1) {
                m->grid[x][y].isHit = 2;
                hits++;
            } else {
                m->grid[x][y].isHit = 1;
                misses++;
            }
        }
    }
    printf("Результат залпу: %d влучань, %d промахів.\n", hits, misses);
}

Point GetUserShot() {
    Point p;
    printf("Введіть координати (x y): ");
    scanf("%d %d", &p.x, &p.y);
    return p;
}

int LoadFieldFromFile(Matrix* m, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    for (int i = 0; i < m->N; i++) {
        for (int j = 0; j < m->N; j++) {
            fscanf(f, "%d", &m->grid[i][j].hasShip);
            m->grid[i][j].isHit = 0;
        }
    }
    fclose(f);
    return 1;
}

Point GetComputerShot(Matrix* m) {
    Point p;
    do {
        p.x = rand() % m->N;
        p.y = rand() % m->N;
    } while (m->grid[p.x][p.y].isHit != 0);
    return p;
}

int CheckWinCondition(Matrix* m) {
    for (int i = 0; i < m->N; i++) {
        for (int j = 0; j < m->N; j++) {
            if (m->grid[i][j].hasShip == 1 && m->grid[i][j].isHit != 2) return 0;
        }
    }
    return 1;
}

void PlaceShip(Matrix* m, int x, int y) {
    if (x >= 0 && x < m->N && y >= 0 && y < m->N) {
        m->grid[x][y].hasShip = 1;
    }
}
Point ConvertInputToPoint(char* input) {
    Point p = {-1, -1};
    int len = strlen(input);
    if (len < 2) return p;

    // Цифра (X) — на початку (1-10)
    char numPart[4] = {0};
    strncpy(numPart, input, len - 1);
    int num = atoi(numPart);
    if (num >= 1 && num <= 10) p.x = num - 1;

    // Буква (Y) — в кінці (A-J)
    char letter = input[len - 1];
    if (letter >= 'A' && letter <= 'J') p.y = letter - 'A';
    else if (letter >= 'a' && letter <= 'j') p.y = letter - 'a';

    return p;
}
