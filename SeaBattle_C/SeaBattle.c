#include "SeaBattle.h"

void InitField(Matrix* m, unsigned int size) {
    m->N = size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            m->grid[i][j].hasShip = 0;
            m->grid[i][j].isHit = 0;
        }
    }
}

// Виводимо поле у зрозумілому вигляді [cite: 13, 384]
void PrintField(Matrix* m) {
    printf("\n   ");
    for (int i = 0; i < m->N; i++) {
        printf("%c ", 'A' + i); 
    }
    printf("\n");

    for (int i = 0; i < m->N; i++) {
        printf("%2d ", i + 1); 
        for (int j = 0; j < m->N; j++) {
            if (m->grid[i][j].isHit == 0) printf(". "); // Невідома територія
            else if (m->grid[i][j].isHit == 1) printf("O "); // Мимо
            else printf("X "); // Влучили
        }
        printf("\n");
    }
}