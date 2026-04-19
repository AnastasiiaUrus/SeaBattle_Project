#include "SeaBattle.h"

int main() {
    Matrix myField;
    InitField(&myField, FIELD_SIZE);
    
    // Поставимо для тесту корабель вручну в позицію 0,0
    myField.grid[0][0].hasShip = 1; 

    //стріляємо по (0,0), (0,1) та (5,5)
    Point myVolley[3] = {{0, 0}, {0, 1}, {5, 5}};
    
    ProcessVolley(&myField, 3, myVolley);
    PrintField(&myField);
    
    return 0;
}