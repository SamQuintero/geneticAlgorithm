//
// Created by Benjamin Vergara on 2022/05/10.
//

#ifndef MAIN_C_MOVEMENT_H
#define MAIN_C_MOVEMENT_H
#include "specie.h"

int checkIsRadious(Specie allSpecies[], food comida[]);
void addClosestFood(Specie array[], food comida[]);
food findFood(pos dude, food comida[]);
Specie outBounders(Specie dude);
Specie moveTowardsFood(Specie specie, int direction);

#endif //MAIN_C_MOVEMENT_H
