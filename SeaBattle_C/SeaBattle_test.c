#include "SeaBattle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    Matrix playerField, enemyField;
    char input[10];

    // Ініціалізація обох полів
    InitField(&playerField, FIELD_SIZE);
    InitField(&enemyField, FIELD_SIZE);

    // ... ініціалізація полів ...
    
    printf("============================================\n");
    printf("   НАЛАШТУВАННЯ ВАШОГО ФЛОТУ \n");
    printf("============================================\n");
    
    // Показуємо пусте поле, щоб було легше обрати координати
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

    // Корабель ворога все ще ставимо випадково
    PlaceShip(&enemyField, rand() % 10, rand() % 10);
    
    printf("\nНатисніть Enter, щоб розпочати бій...");
    getchar(); getchar(); // Очікування натискання


    printf("============================================\n");
    printf("   ВІТАЄМО У ГРІ МОРСЬКИЙ БІЙ (SeaBattle-1) \n");
    printf("============================================\n");
    printf("Формат вводу: ЦифраБуква (наприклад: 1A або 10J)\n\n");

    while (1) {
        // --- ВАШ ХІД ---
        printf("\n--- ПОЛЕ ВОРОГА (куди ви стріляєте) ---");
        PrintField(&enemyField);
        
        printf("Ваш постріл: ");
        if (scanf("%s", input) != 1) break;

        Point userShot = ConvertInputToPoint(input);

        if (userShot.x == -1 || userShot.y == -1) {
            printf("(!) Помилка вводу. Використовуйте формат 1A - 10J.\n");
            continue;
        }

        // Обробка вашого пострілу
        ProcessVolley(&enemyField, 1, &userShot);
        
        // Показуємо результат вашого пострілу відразу
        printf("\nВи вистрілили в %s:", input);
        PrintField(&enemyField);

        if (CheckWinCondition(&enemyField)) {
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