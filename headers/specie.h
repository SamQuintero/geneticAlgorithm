//
// Created by Benjamin Vergara on 2022/05/09.
//

#ifndef MAIN_C_SPECIE_H
#define MAIN_C_SPECIE_H

#include "food.h"


typedef struct {

    int speed;
    int ID;
    int visibility;
    int size;
    int fat;
    int direction;
    pos coordinate;
    food closestFood;

} Specie;

Specie createSample(int id);
void createPopulation(Specie dudearray[]);
int meanSizeSpecies(Specie allSpecies[]);

#endif //MAIN_C_SPECIE_H
