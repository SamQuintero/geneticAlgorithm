//
// Created by Benjamin Vergara on 2022/05/09.
//

#include "../specie.h"
#include "stdlib.h"



int POPULATION = 50;
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

    for (int i = 0; i < POPULATION; i++) {

        if (i % 2) {
            dudearray[i] = dude1;
            dudearray[i].coordinate.x = rand() % (1200 - 20 + 1) + 20;
            dudearray[i].coordinate.y = rand() % (440 - 20 + 1) + 20;
        } else {
            dudearray[i] = dude2;
            dudearray[i].coordinate.x = rand() % (1200 - 20 + 1) + 20;
            dudearray[i].coordinate.y = rand() % (440 - 20 + 1) + 20;
        }
    }

}

int maxSizeSpecies(Specie allSpecies[]) {
    int max = 0;
    for(int i = 0; i < POPULATION; i++){
        if(allSpecies[i].size > max){
            max = allSpecies[i].size;
        }
    }
    return max;
}
