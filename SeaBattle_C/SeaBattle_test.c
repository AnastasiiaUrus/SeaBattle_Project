#include "SeaBattle.h"

int main() {
    Matrix myField;
    
    // 1. Тест ініціалізацію
    InitField(&myField, FIELD_SIZE);
    
    // 2. Тест вивід порожнього поля
    printf("Welcome to Sea Battle");
    PrintField(&myField);
    
    return 0;
}