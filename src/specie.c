//
// Created by Benjamin Vergara and Sam Quintero
//

#include "../headers/specie.h"
#include "stdlib.h"


int POPULATION = 99;


/* Function: createSample
 * --------------------------
 * Returns the sample for a specie. Their attributes such as
 * speed, visibility and size will be given randomly. Fat
 * will be zero since it represents the amount of food eaten.
 *
 */

Specie createSample(int id) {

    Specie dude;
    dude.ID = id;
    dude.speed = rand() % (20 - 5 + 1) + 5;
    dude.visibility = rand() % (500 - 20 + 1) + 20;
    dude.size = rand() % (20 - 11 + 1) + 11;
    dude.fat = 0;
    return dude;
}


/* Function: createPopulation
 * --------------------------
 * Creates a population composed by three different species
 * for the amount of population that we have. Species will be
 * cloned, so  all sample from one specie will have tha same
 * attributes
 *
 * In order to have a fair amount of samples for each species
 * the for control statement will increase by three and  in
 * each iteration there will be one assignment per species.
 */

void createPopulation(Specie allSpecies[]) {
    Specie dude1 = createSample(1);
    Specie dude2 = createSample(2);
    Specie dude4 = createSample(4);

    for (int i = 0; i < POPULATION; i += 3) {

        allSpecies[i] = dude1;
        allSpecies[i].coordinate.x = rand() % (1200 - 20 + 1) + 20;
        allSpecies[i].coordinate.y = rand() % (440 - 20 + 1) + 20;

        if (i + 1 < POPULATION) {
            allSpecies[i + 1] = dude4;
            allSpecies[i + 1].coordinate.x = rand() % (1200 - 20 + 1) + 20;
            allSpecies[i + 1].coordinate.y = rand() % (440 - 20 + 1) + 20;

        }
        if (i + 2 < POPULATION) {
            allSpecies[i + 2] = dude2;
            allSpecies[i + 2].coordinate.x = rand() % (1200 - 20 + 1) + 20;
            allSpecies[i + 2].coordinate.y = rand() % (440 - 20 + 1) + 20;
        }
    }

}


/* Function: meanSizeSpecies
 * --------------------------
 * valuates the mean size among all the species
 *
 * In order to make use of the size trait for the species,
 * there must exist a variety of sizes in food.
 * The mean size of all species will be used as the maximum
 * size to give advantage to bigger species but being fair
 * with the rest of them.
 */

int meanSizeSpecies(Specie allSpecies[]) {
    int mid = 0;
    for (int i = 0; i < POPULATION; i++) {
        mid += allSpecies[i].size;
    }

    return mid / POPULATION;
}
