#ifndef MAIN_C_FOOD_H
#define MAIN_C_FOOD_H


#include "stdio.h"

typedef struct {
    int x;
    int y;
} pos;

typedef struct {
    pos coordinate;
    int size;
} food;

void createFoodPos(food arr[], int maxsize);
int quantityOfFood(food comida[]);


#endif //MAIN_C_FOOD_H
