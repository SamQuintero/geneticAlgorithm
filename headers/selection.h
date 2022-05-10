//
// Created by Benjamin Vergara on 2022/05/10.
//

#ifndef MAIN_C_SELECTION_H
#define MAIN_C_SELECTION_H

#include "movement.h"

void Collision(Specie allSpecies[], food comida[]);
void killSpecie(Specie allSpecies[]);
void AsexualReproduction(Specie allSpecies[]);
int graveyard(Specie allSpecies[]);
void assignPos(Specie allSpecies[]);
void mutation(Specie allSpecies[], int oldies);
int endOfWorld(Specie allSpecies[]);

#endif //MAIN_C_SELECTION_H
