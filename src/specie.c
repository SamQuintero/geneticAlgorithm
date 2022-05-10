//
// Created by Benjamin Vergara on 2022/05/09.
//

#include "../headers/specie.h"
#include "stdlib.h"
#include "../headers/globals.h"



int POPULATION = 80;
//Aquí se crea todos los valores de una especie
Specie createSample(int id) {

    Specie dude;
    dude.ID = id;
    dude.speed = 10; //rand() % (20 - 5 + 1) + 5;
    dude.visibility = rand() % (500 - 20 + 1) + 20;
    dude.size = rand() % (20 - 11 + 1) + 11;
    dude.fat = 0;
    return dude;
}

void createPopulation(Specie dudearray[]) {
    Specie dude1 = createSample(1);
    Specie dude2 = createSample(2);
    Specie dude4 = createSample(4);

    for (int i = 0; i < POPULATION; i++) { //1,2

        if (i % 4) {
            dudearray[i] = dude1;
            dudearray[i].coordinate.x = rand() % (1200 - 20 + 1) + 20;
            dudearray[i].coordinate.y = rand() % (440 - 20 + 1) + 20;

        }
        else if (i % 3) {
            dudearray[i] = dude4;
            dudearray[i].coordinate.x = rand() % (1200 - 20 + 1) + 20;
            dudearray[i].coordinate.y = rand() % (440 - 20 + 1) + 20;

        }
        else {
            dudearray[i] = dude2;
            dudearray[i].coordinate.x = rand() % (1200 - 20 + 1) + 20;
            dudearray[i].coordinate.y = rand() % (440 - 20 + 1) + 20;
        }
    }

}

int meanSizeSpecies(Specie allSpecies[]) {
    int mid = 0;
    for(int i = 0; i < POPULATION; i++){
        mid+=allSpecies[i].size;
        }

    return mid/POPULATION;
}
