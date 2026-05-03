#include "SeaBattle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    Matrix playerField, enemyField;
    char input[10];

    InitField(&playerField, FIELD_SIZE);
    InitField(&enemyField, FIELD_SIZE);

    // --- НОВИЙ БЛОК РОЗСТАНОВКИ ФЛОТУ ---
    int shipLengths[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; // Всі 10 кораблів
    char direction;

    printf("============================================\n");
    printf("   ФАЗА РОЗСТАНОВКИ ВАШОГО ФЛОТУ \n");
    printf("============================================\n");

    for (int i = 0; i < 10; i++) {
        int validPlace = 0;
        while (!validPlace) {
            printf("\nВаше поле зараз:");
            PrintField(&playerField);
            
            printf("\nСтавимо %d-палубний корабель (%d/10)\n", shipLengths[i], i + 1);
            printf("Введіть координату початку (напр. 1A): ");
            scanf("%s", input);
            
            direction = 'H'; 
            if (shipLengths[i] > 1) {
                printf("Оберіть напрямок (H - вбік, V - вниз): ");
                scanf(" %c", &direction); // Пробіл перед %c важливий!
            }

            Point p = ConvertInputToPoint(input);
            
            if (p.x != -1 && p.y != -1) {
                // НОВА ПЕРЕВІРКА:
                if (CanPlaceShip(&playerField, p.x, p.y, shipLengths[i], direction)) {
                    PlaceShipExtended(&playerField, p.x, p.y, shipLengths[i], direction);
                    validPlace = 1;
                } else {
                    printf("(!) Помилка! Корабель не влазить або там уже є інший. Спробуйте ще раз.\n");
                }
            } else {
                printf("(!) Помилка координат. Вводьте від 1A до 10J.\n");
            }
        }
    }

   // Автоматична розстановка для ворога (по 1 клітинці)
    for(int i = 0; i < 10; i++) {
        PlaceShipExtended(&enemyField, rand() % 10, rand() % 10, 1, 'H'); 
    }

    printf("\nУсі кораблі розставлено! Натисніть Enter для початку бою...");
    getchar(); getchar(); 

    // --- ДАЛІ ЙДЕ ТВІЙ ЦИКЛ БОЮ (while(1) { ... }) ЯКИЙ МИ РОБИЛИ РАНІШЕ ---
    while (1) {
        Point userShot;
        int validShot = 0; 

        // 1. Твій хід з перевіркою
        while (validShot == 0) {
            printf("\n--- ПОЛЕ ВОРОГА ---");
            PrintField(&enemyField);
            
            printf("Ваш постріл (напр. 1A): ");
            if (scanf("%s", input) != 1) return 0;

            userShot = ConvertInputToPoint(input);

            if (userShot.x == -1 || userShot.y == -1) {
                printf("(!) Помилка вводу! Діапазон 1A - 10J.\n");
                continue;
            }

            // Перевірка на повторний постріл[cite: 8]
            if (enemyField.grid[userShot.x][userShot.y].isHit != 0) {
                printf("(!) Ви вже сюди стріляли! Спробуйте іншу точку.\n");
            } else {
                validShot = 1; 
            }
        }

        // Обробка твого пострілу[cite: 12]
        ProcessVolley(&enemyField, 1, &userShot);
        
        if (CheckWinCondition(&enemyField)) {
            PrintField(&enemyField);
            printf("\n============================================\n");
            printf("      ПЕРЕМОГА! Флот ворога знищено! \n");
            printf("============================================\n");
            break;
        }

        // 2. Хід комп'ютера[cite: 12]
        printf("\nКомп'ютер цілиться...");
        Point aiShot = GetComputerShot(&playerField);
        ProcessVolley(&playerField, 1, &aiShot);
        
        printf("\nКомп'ютер вистрілив у %d%c", aiShot.x + 1, 'A' + aiShot.y);
        printf("\n--- ВАШЕ ПОЛЕ (стан вашого флоту) ---");
        PrintField(&playerField);

        if (CheckWinCondition(&playerField)) {
            printf("\n============================================\n");
            printf("      ПОРАЗКА! Ваші кораблі потоплено. \n");
            printf("============================================\n");
            break;
        }
    }

    printf("\nНатисніть будь-яку клавішу для виходу.");
    getchar(); getchar(); 
    return 0;

    return 0;
}