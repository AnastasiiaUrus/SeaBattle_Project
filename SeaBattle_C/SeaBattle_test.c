#include "SeaBattle.h"
#include <stdlib.h>
#include <time.h>
int main() {
    srand(time(NULL));
    Matrix myField;
    InitField(&myField, FIELD_SIZE);

    printf("Оберіть режим: 1 - Вручну, 2 - З файлу: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 2) {
        if (!LoadFieldFromFile(&myField, "SeaBattle_test.dat")) {
            printf("Помилка: файл не знайдено\n");
            return 1;
        }
    } else {
        myField.grid[0][0].hasShip = 1;
    }

    printf("Гра почалася!\n");
    for(int i = 0; i < 3; i++) {
        Point aiShot = GetComputerShot(&myField);
        printf("AI стріляє в %d %d\n", aiShot.x, aiShot.y);
        ProcessVolley(&myField, 1, &aiShot);
    }
    
    PrintField(&myField);
    // ... після InitField ...
PlaceShip(&myField, 0, 0); 
printf("Тест: Корабель поставлено в 0,0. Чи є перемога? (1 - так, 0 - ні): %d\n", CheckWinCondition(&myField));

// Тепер зробимо постріл, щоб "вбити" його
Point hitPoint = {0, 0};
ProcessVolley(&myField, 1, &hitPoint);
printf("Тест: Після пострілу перемога? (1 - так, 0 - ні): %d\n", CheckWinCondition(&myField));
    return 0;
}