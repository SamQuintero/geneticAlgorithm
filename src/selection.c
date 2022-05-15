//
// Created by Benjamin Vergara on 2022/05/10.
//

#include "../headers/selection.h"
#include "../headers/globals.h"
#include "stdlib.h"

/* Function: Collision
 * --------------------------
 * Check if the specie coordinate is the same as its
 * closest food or if its edges are in the same
 * range of space, then find which food was and switch
 * the coordinates to high negatives, avoiding the
 * species continue looking for them
 *
 */
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

/* Function: KillSpecie
 * --------------------------
 * The function evaluates if the species ate
 * at least one food if doesn´t it gives a new
 * id to identify it
 */

void killSpecie(Specie allSpecies[]) {
    for (int i = 0; i < POPULATION; i++) {
        if (allSpecies[i].fat == 0) {
            allSpecies[i].ID = 666;
        }
    }
}
/* Function: graveyard
 * --------------------------
 * Rearrange the array with the survivor
 * species on the top and who many of
 * them are, return this integer
 */

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

/* Function: AsexualReproduction
 * --------------------------
 * The function check which dude eat more
 * than just one food an put a copy of this
 * in the after all the alive species in the array.
 * Update de population.
 * Called the function which mutate
 */
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
    assignPos(allSpecies);
    mutation(allSpecies, oldies);

}


/* Function: assignPoss
 * --------------------------
 *  Reassign a coordinate to each sample
 *  from the array when start a new generation
 */
void assignPos(Specie allSpecies[]) {
    for (int i = 0; i < POPULATION; i++) {
        allSpecies[i].coordinate.x = rand() % (1200 - 10 + 1) + 10;
        allSpecies[i].coordinate.y = rand() % (440 - 10 + 1) + 10;
    }

}
/* Function: mutation
 * --------------------------
 *  Every sample have a fifty fifty chance
 *  to mutate, in just one of its attributes
 *  which are chosen randomly
 */

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
/* Function: endOfWorld
 * --------------------------
 * The function check the size of
 * every sample and return the larger,
 * to evaluate the end condition.
 */
int endOfWorld(Specie allSpecies[]){
    int max=0;
    for (int i=0;i<POPULATION;i++){
        if (allSpecies[i].size>max){
            max=allSpecies[i].size;
        }

    }
    return max;
}

/* Function: survivingSpecie
 * --------------------------
 * The function check if is only one specie
 * alive to evaluate the end condition, return
 * 0 if this is true an 1 if doesn´t.
 */
int survivingSpecie(Specie allSpecies[]){

    int idCheck = allSpecies[0].ID;
    for(int i=0; i<POPULATION; i++){
        if(allSpecies[i].ID != idCheck)
            return 1;
    }
    return 0;
}

