#include "SeaBattle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    Matrix playerField, enemyField;
    char input[10];

    // 1. Ініціалізація обох полів
    InitField(&playerField, FIELD_SIZE);
    InitField(&enemyField, FIELD_SIZE);

    printf("============================================\n");
    printf("   НАЛАШТУВАННЯ ВАШОГО ФЛОТУ \n");
    printf("============================================\n");
    
    // Показуємо пусте поле
    PrintField(&playerField);
    
    printf("Оберіть місце для вашого корабля (наприклад, 1A): ");
    scanf("%s", input);
    
    Point playerShipPos = ConvertInputToPoint(input);
    if (playerShipPos.x != -1 && playerShipPos.y != -1) {
        PlaceShip(&playerField, playerShipPos.x, playerShipPos.y);
        printf("Корабель встановлено в %s!\n", input);
    } else {
        printf("Помилка! Ставимо дефолтний корабель в 1A.\n");
        PlaceShip(&playerField, 0, 0);
    }

    // Корабель ворога ставимо випадково
    PlaceShip(&enemyField, rand() % 10, rand() % 10);
    
    printf("\nНатисніть Enter, щоб розпочати бій...");
    getchar(); getchar(); 

    printf("\n============================================\n");
    printf("   ВІТАЄМО У ГРІ МОРСЬКИЙ БІЙ (SeaBattle-1) \n");
    printf("============================================\n");

    // ОСНОВНИЙ ЦИКЛ ГРИ
    while (1) {
        Point userShot;
        int validShot = 0; 

        // Цикл перевірки вводу гравця
        while (validShot == 0) {
            printf("\n--- ПОЛЕ ВОРОГА ---");
            PrintField(&enemyField);
            
            printf("Ваш постріл (напр. 1A): ");
            if (scanf("%s", input) != 1) return 0;

            userShot = ConvertInputToPoint(input);

            // Перевірка 1: Чи в межах поля
            if (userShot.x == -1 || userShot.y == -1) {
                printf("(!) Помилка! Вводьте координати від 1A до 10J.\n");
                continue;
            }

            // ПЕРЕВІРКА НА ПОВТОРНИЙ ПОСТРІЛ
            int currentStatus = enemyField.grid[userShot.x][userShot.y].isHit;
            
            if (currentStatus != 0) {
                printf("(!) Ви вже стріляли в %s. Стан клітинки: %d\n", input, currentStatus);
                printf("(!) Оберіть іншу координату.\n");
            } else {
                validShot = 1; 
            }
        }

        // Обробка вашого пострілу
        ProcessVolley(&enemyField, 1, &userShot);
        
        if (CheckWinCondition(&enemyField)) {
            printf("\n--- РЕЗУЛЬТАТ ВАШОГО ПОСТРІЛУ ---");
            PrintField(&enemyField);
            printf("\n============================================\n");
            printf("      ПЕРЕМОГА! Ворожий корабель потоплено! \n");
            printf("============================================\n");
            break;
        }

        // --- ХІД КОМП'ЮТЕРА ---
        printf("\nКомп'ютер робить свій хід...");
        Point aiShot = GetComputerShot(&playerField);
        ProcessVolley(&playerField, 1, &aiShot);
        
        printf("\nКомп'ютер вистрілив у %d%c", aiShot.x + 1, 'A' + aiShot.y);
        printf("\n--- ВАШЕ ПОЛЕ (куди стріляв ворог) ---");
        PrintField(&playerField);

        if (CheckWinCondition(&playerField)) {
            printf("\n============================================\n");
            printf("      ПОРАЗКА! Ваш корабель було знищено.   \n");
            printf("============================================\n");
            break;
        }
    }

    printf("\nДякуємо за гру! Натисніть будь-яку клавішу для виходу.");
    return 0;
}