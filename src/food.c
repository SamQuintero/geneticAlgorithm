#include <stdlib.h>
#include "../headers/food.h"


int MAP_FOOD=70;
/* Function: createFoodPos
 * --------------------------
 * The function assigns randomly a coordinate to each food
 * that will be in the map. The size it´s also given
 * randomly but the max size it can take is the mean
 * of the species size.
 *
 */
void createFoodPos(food arr[], int maxsize) {
    for (int i = 0; i < MAP_FOOD; i++) {
        arr[i].coordinate.x = rand() % (1200 - 40 + 1) + 40;

        arr[i].coordinate.y = rand() % (400 - 40 + 1) + 40;
        arr[i].size=rand() % ((maxsize-2)- 5 + 1) + 5;

    }
}

/* Function: quantityOfFood
 * --------------------------
 * The function check if the coordinates of
 * each food are still positive numbers, this is because
 * when the specie collide with the food, the food is
 * sent to the negatives.
 * The function returns the amount of food
 * outside the map.
 *
 */

int quantityOfFood(food comida[]){
    int contador=0;
    for (int i = 0; i < MAP_FOOD; i++) {
        if (comida[i].coordinate.x < 0 && comida[i].coordinate.y < 0) {
            contador++;
        }
    }
    return contador;
}