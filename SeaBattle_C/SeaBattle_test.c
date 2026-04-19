#include "SeaBattle.h"

int main() {
    Matrix myField;
    InitField(&myField, FIELD_SIZE);
    
    myField.grid[0][0].hasShip = 1; 

    printf("Початок гри\n");
    while (myField.grid[0][0].isHit != 2) {
        PrintField(&myField);
        Point shot = GetUserShot();
        
        ProcessVolley(&myField, 1, &shot);
        
        if (myField.grid[0][0].isHit == 2) {
            printf("\nКорабель потоплено\n");
        }
    }
    
    PrintField(&myField);
    return 0;
}