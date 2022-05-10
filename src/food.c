#include <stdlib.h>
#include "../headers/food.h"
#include "../headers/globals.h"


int MAP_FOOD=40;
void createFoodPos(food arr[], int maxsize) {
    for (int i = 0; i < MAP_FOOD; i++) {
        arr[i].coordinate.x = rand() % (1200 - 40 + 1) + 40;

        arr[i].coordinate.y = rand() % (400 - 40 + 1) + 40;
        printf("%d %d\n", arr[i].coordinate.x, arr[i].coordinate.y);
        arr[i].size=rand() % ((maxsize-2)- 5 + 1) + 5;

    }
}

//Para saber si aun queda comida dentro del mapa
int quantityOfFood(food comida[]){
    int contador=0;
    for (int i = 0; i < MAP_FOOD; i++) {
        if (comida[i].coordinate.x < 0 && comida[i].coordinate.y < 0) {
            contador++;
        }
    }
    return contador;
}