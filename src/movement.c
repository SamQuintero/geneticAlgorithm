//
// Created by Benjamin Vergara and Sam Quintero
//


#include "../headers/movement.h"
#include "../headers/globals.h"
#include "math.h"
#include "stdlib.h"


/* Function: checkIsRadious
 * --------------------------
 * Assigns the rate of vision for all cardinal points in the
 * difference and addition variables. Then the closestFood
 * function is called. Once all the species have the closest
 * food assigned they will find the quadrant in such food
 * is located. If the food is within the vision of the specie,
 * and it doesn't get out of the plane, the specie will move towards
 * the food,otherwise it will move randomly.
 *
 */
void checkIsRadious(Specie allSpecies[], food comida[]) {
    int differenceX;
    int differenceY;
    int additionX;
    int additionY;
    addClosestFood(allSpecies, comida);
    printPopulation(allSpecies);
    for (int i = 0; i < POPULATION; i++) {
        differenceX = allSpecies[i].coordinate.x - allSpecies[i].visibility;
        differenceY = allSpecies[i].coordinate.y - allSpecies[i].visibility;
        additionX = allSpecies[i].coordinate.x + allSpecies[i].visibility;
        additionY = allSpecies[i].coordinate.y + allSpecies[i].visibility;
        //The quadrant is left down
        if (allSpecies[i].closestFood.coordinate.x <= allSpecies[i].coordinate.x &&
            allSpecies[i].closestFood.coordinate.y >= allSpecies[i].coordinate.y) {
            if (differenceX <= allSpecies[i].closestFood.coordinate.x &&
                additionY >= allSpecies[i].closestFood.coordinate.y &&
                allSpecies[i].size >= allSpecies[i].closestFood.size) {
                allSpecies[i].direction = 1;
                allSpecies[i] = outBoundaries(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if (allSpecies[i].coordinate.x < allSpecies[i].closestFood.coordinate.x) {
                    allSpecies[i].coordinate.x = allSpecies[i].closestFood.coordinate.x;
                }
                if (allSpecies[i].coordinate.y > allSpecies[i].closestFood.coordinate.y) {
                    allSpecies[i].coordinate.y = allSpecies[i].closestFood.coordinate.y;
                }
            } else {
                allSpecies[i].direction = (rand() % (4 - 1 + 1) + 1);
                allSpecies[i] = outBoundaries(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
        //The quadrant is left up
        else if (allSpecies[i].closestFood.coordinate.x <= allSpecies[i].coordinate.x &&
                 allSpecies[i].closestFood.coordinate.y <= allSpecies[i].coordinate.y) {
            if (differenceX <= allSpecies[i].closestFood.coordinate.x &&
                differenceY <= allSpecies[i].closestFood.coordinate.y &&
                allSpecies[i].size >= allSpecies[i].closestFood.size) {
                allSpecies[i].direction = 2;
                allSpecies[i] = outBoundaries(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if (allSpecies[i].coordinate.x < allSpecies[i].closestFood.coordinate.x) {
                    allSpecies[i].coordinate.x = allSpecies[i].closestFood.coordinate.x;
                }
                if (allSpecies[i].coordinate.y < allSpecies[i].closestFood.coordinate.y) {
                    allSpecies[i].coordinate.y = allSpecies[i].closestFood.coordinate.y;
                }
            } else {
                allSpecies[i].direction = (rand() % (4 - 1 + 1) + 1);
                allSpecies[i] = outBoundaries(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }

        //The quadrant is right down
        else if (allSpecies[i].closestFood.coordinate.x >= allSpecies[i].coordinate.x &&
                 allSpecies[i].closestFood.coordinate.y >= allSpecies[i].coordinate.y) {
            if (additionX >= allSpecies[i].closestFood.coordinate.x &&
                additionY >= allSpecies[i].closestFood.coordinate.y &&
                allSpecies[i].size >= allSpecies[i].closestFood.size) {
                allSpecies[i].direction = 3;
                allSpecies[i] = outBoundaries(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if (allSpecies[i].coordinate.x > allSpecies[i].closestFood.coordinate.x) {
                    allSpecies[i].coordinate.x = allSpecies[i].closestFood.coordinate.x;
                }
                if (allSpecies[i].coordinate.y > allSpecies[i].closestFood.coordinate.y) {
                    allSpecies[i].coordinate.y = allSpecies[i].closestFood.coordinate.y;
                }
            } else {
                allSpecies[i].direction = (rand() % (4 - 1 + 1) + 1);
                allSpecies[i] = outBoundaries(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
        //The quadrant is right up
        else if (allSpecies[i].closestFood.coordinate.x >= allSpecies[i].coordinate.x &&
                 allSpecies[i].closestFood.coordinate.y <= allSpecies[i].coordinate.y) {
            if (additionX >= allSpecies[i].closestFood.coordinate.x &&
                differenceY <= allSpecies[i].closestFood.coordinate.y &&
                allSpecies[i].size >= allSpecies[i].closestFood.size) {
                allSpecies[i].direction = 4;
                allSpecies[i] = outBoundaries(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);


                if (allSpecies[i].coordinate.x > allSpecies[i].closestFood.coordinate.x) {
                    allSpecies[i].coordinate.x = allSpecies[i].closestFood.coordinate.x;
                }
                if (allSpecies[i].coordinate.y < allSpecies[i].closestFood.coordinate.y) {
                    allSpecies[i].coordinate.y = allSpecies[i].closestFood.coordinate.y;
                }
            } else {
                allSpecies[i].direction = (rand() % (4 - 1 + 1) + 1);
                allSpecies[i] = outBoundaries(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
    }
}

/* Function: addClosestFood
 * --------------------------
 * Calls the findFood function and assigns the closest
 * food with respect to each of the species
 *
 */
void addClosestFood(Specie array[], food comida[]) {
    for (int i = 0; i < POPULATION; i++) {
        array[i].closestFood = findFood(array[i].coordinate, comida);
    }
}


/* Function: findFood
 * --------------------------
 * Using the closest point formula, it finds the
 * nearest food with regard of each specie and
 * returns a structure of type food that is added
 * to the species closestFood attribute
 *
 */
food findFood(pos dude, food comida[]) {
    float distance;
    float mindistance = 10000000;
    food closestFood;

    for (int i = 0; i < MAP_FOOD; i++) {
        distance = abs(sqrt(pow((comida[i].coordinate.x - dude.x), 2) + pow((comida[i].coordinate.y - dude.y), 2)));
        if (mindistance > distance) {
            mindistance = distance;
            closestFood.coordinate.x = comida[i].coordinate.x;
            closestFood.coordinate.y = comida[i].coordinate.y;
            closestFood.size = comida[i].size;
        }
    }
    return closestFood;
}


/* Function: outBoundaries
 * --------------------------
 * The function evaluates tha the species don't get out
 * of boundaries when moving. Depending on the
 * direction they are supposed to go, if the case is that
 * they get out of boundaries they will go move towards
 * the opposite direction. 
 */
Specie outBoundaries(Specie specie) {
    Specie testSpecie = moveTowardsFood(specie, specie.direction);
    if (testSpecie.coordinate.x < 0 || testSpecie.coordinate.x > 1300 || testSpecie.coordinate.y < 0 ||
        testSpecie.coordinate.y > 600) {
        switch (specie.direction) {
            case 1:
                specie.direction = 4;
                break;

            case 2:
                specie.direction = 3;
                break;

            case 3:
                specie.direction = 2;
                break;

            case 4:
                specie.direction = 1;
                break;
        }
    }

    return specie;
}


//Para dirigir la celula hacia la comida o algun punto
Specie moveTowardsFood(Specie specie, int direction) {
    switch (direction) {
        case 1:
            specie.coordinate.x -= specie.speed;
            specie.coordinate.y += specie.speed;
            break;
        case 2:
            specie.coordinate.x -= specie.speed;
            specie.coordinate.y -= specie.speed;
            break;
        case 3:
            specie.coordinate.x += specie.speed;
            specie.coordinate.y += specie.speed;
            break;
        case 4:
            specie.coordinate.x += specie.speed;
            specie.coordinate.y -= specie.speed;
            break;
        default:
            break;
    }
    return specie;
}

void printPopulation(Specie allSpecies[]) {
    for (int i = 0; i < POPULATION; i++) {
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", allSpecies[i].ID, allSpecies[i].speed, allSpecies[i].visibility,
               allSpecies[i].size, allSpecies[i].coordinate.x, allSpecies[i].coordinate.y,
               allSpecies[i].closestFood.coordinate.x,
               allSpecies[i].closestFood.coordinate.y, allSpecies[i].fat, allSpecies[i].closestFood.size);
        printf("\n");
    }

}