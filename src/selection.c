//
// Created by Benjamin Vergara on 2022/05/10.
//

#include "../headers/selection.h"
#include "../headers/globals.h"
#include "stdlib.h"

//Detecta si la celula comió
void Collision(Specie allSpecies[], food comida[]) {

    for (int i = 0; i < POPULATION; i++) {
        if (allSpecies[i].coordinate.x == allSpecies[i].closestFood.coordinate.x &&
            allSpecies[i].coordinate.y == allSpecies[i].closestFood.coordinate.y ||
            allSpecies[i].coordinate.x - allSpecies[i].size/2  <= allSpecies[i].closestFood.coordinate.x &&
            allSpecies[i].coordinate.y - allSpecies[i].size/2  <= allSpecies[i].closestFood.coordinate.y ||
            allSpecies[i].coordinate.x - allSpecies[i].size/2  <= allSpecies[i].closestFood.coordinate.x &&
            allSpecies[i].coordinate.y + allSpecies[i].size/2  >= allSpecies[i].closestFood.coordinate.y ||
            allSpecies[i].coordinate.x + allSpecies[i].size/2  >= allSpecies[i].closestFood.coordinate.x &&
            allSpecies[i].coordinate.y - allSpecies[i].size/2  <= allSpecies[i].closestFood.coordinate.y ||
            allSpecies[i].coordinate.x + allSpecies[i].size/2  >= allSpecies[i].closestFood.coordinate.x &&
            allSpecies[i].coordinate.y + allSpecies[i].size/2  >= allSpecies[i].closestFood.coordinate.y) {
            for (int j = 0; j < MAP_FOOD; j++) {
                if (comida[j].coordinate.x == allSpecies[i].coordinate.x &&
                    comida[j].coordinate.y == allSpecies[i].coordinate.y) {
                    comida[j].coordinate.x = -1900;
                    comida[j].coordinate.y = -2900;
                    allSpecies[i].fat += 1;
                }

            }
        }
    }
}

//Id 3 es la especie del más allá estas species ya pasaron en mejor vida
void killSpecie(Specie allSpecies[]) {
    for (int i = 0; i < POPULATION; i++) {
        if (allSpecies[i].fat == 0) {
            allSpecies[i].ID = 666;
        }
    }
}

//Las especies se reproducen de forma asexual
void AsexualReproduction(Specie allSpecies[]) {
    int survivor = graveyard(allSpecies);
    int oldies = survivor;

    for (int i = 0; i < oldies; i++) {
        if (allSpecies[i].fat > 1) {
            allSpecies[survivor] = allSpecies[i];
            survivor++;
        }
    }
    for (int i = 0; i < POPULATION; i++) {
        allSpecies[i].fat = 0;
    }
    POPULATION = survivor;
    printf(":(");
    assignPos(allSpecies);
    printf(":(");
    mutation(allSpecies, oldies);

}

//Recorre las especies muertas y contabiliza cuantas sobrevivieron
int graveyard(Specie allSpecies[]) {
    Specie temp;
    for (int i = 1; i < POPULATION; i++) {
        for (int j = 0; j < i; j++) {
            if (allSpecies[i].ID < allSpecies[j].ID) {
                temp = allSpecies[i];
                allSpecies[i] = allSpecies[j];
                allSpecies[j] = temp;

            }
        }
    }
    int count = 0;
    for (int r = 0; r < POPULATION; r++) {
        if (allSpecies[r].ID != 666) {
            count++;
        }
    }
    return count;
}

void assignPos(Specie allSpecies[]) {
    for (int i = 0; i < POPULATION; i++) {
        allSpecies[i].coordinate.x = rand() % (1200 - 10 + 1) + 10;
        allSpecies[i].coordinate.y = rand() % (440 - 10 + 1) + 10;
    }

}

void mutation(Specie allSpecies[], int oldies) {
    for (int i = oldies; i < POPULATION; ++i) {
        int probability = rand() % (3 - 1 + 1) + 1;
        if (probability == 2) {
            int whosechanging = rand() % (4 - 1 + 1) + 1;

            switch (whosechanging) {
                case 2:
                    allSpecies[i].speed += 10;
                    break;
                case 3:
                    allSpecies[i].visibility += 10;
                    break;
                case 4:
                    allSpecies[i].size += 10;
                    break;
            }

        }

    }
}

int endOfWorld(Specie allSpecies[]){
    int max=0;
    for (int i=0;i<POPULATION;i++){
        if (allSpecies[i].size>max){
            max=allSpecies[i].size;
        }

    }
    return max;
}
