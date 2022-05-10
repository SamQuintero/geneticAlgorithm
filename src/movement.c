//
// Created by Benjamin Vergara on 2022/05/10.
//

#include "../headers/movement.h"
#include "../headers/globals.h"
#include "math.h"
#include "stdlib.h"

//Esta función detecta en que cuadrante esta la comida más cercana a la celula y si esta dentro de su rango se dirige a ella, si no la mueve de forma random
int checkIsRadious(Specie allSpecies[], food comida[]) {
    int differenceX;
    int differenceY;
    int additionX;
    int additionY;
    int option = 0;
    addClosestFood(allSpecies, comida);
    for (int i = 0; i < POPULATION; i++) {
        differenceX = allSpecies[i].coordinate.x - allSpecies[i].visibility;
        differenceY = allSpecies[i].coordinate.y - allSpecies[i].visibility;
        additionX = allSpecies[i].coordinate.x + allSpecies[i].visibility;
        additionY = allSpecies[i].coordinate.y + allSpecies[i].visibility;
        //Case 1, left down
        if (allSpecies[i].closestFood.coordinate.x <= allSpecies[i].coordinate.x &&
            allSpecies[i].closestFood.coordinate.y >= allSpecies[i].coordinate.y) {
            if (differenceX <= allSpecies[i].closestFood.coordinate.x &&
                additionY >= allSpecies[i].closestFood.coordinate.y &&
                allSpecies[i].size >= allSpecies[i].closestFood.size) {
                printf("%d ", i);
                printf("Move left down\n");
                allSpecies[i].direction = 1;
                allSpecies[i] = outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if (allSpecies[i].coordinate.x < allSpecies[i].closestFood.coordinate.x) {
                    allSpecies[i].coordinate.x = allSpecies[i].closestFood.coordinate.x;
                }
                if (allSpecies[i].coordinate.y > allSpecies[i].closestFood.coordinate.y) {
                    allSpecies[i].coordinate.y = allSpecies[i].closestFood.coordinate.y;
                }
            } else {
                allSpecies[i].direction = (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i] = outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
            //Case 2, left up
        else if (allSpecies[i].closestFood.coordinate.x <= allSpecies[i].coordinate.x &&
                 allSpecies[i].closestFood.coordinate.y <= allSpecies[i].coordinate.y) {
            if (differenceX <= allSpecies[i].closestFood.coordinate.x &&
                differenceY <= allSpecies[i].closestFood.coordinate.y &&
                allSpecies[i].size >= allSpecies[i].closestFood.size) {
                printf("%d ", i);
                printf("Move left up\n");
                allSpecies[i].direction = 2;
                allSpecies[i] = outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if (allSpecies[i].coordinate.x < allSpecies[i].closestFood.coordinate.x) {
                    allSpecies[i].coordinate.x = allSpecies[i].closestFood.coordinate.x;
                }
                if (allSpecies[i].coordinate.y < allSpecies[i].closestFood.coordinate.y) {
                    allSpecies[i].coordinate.y = allSpecies[i].closestFood.coordinate.y;
                }
            } else {
                allSpecies[i].direction = (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i] = outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }

            //Case 3, right down
        else if (allSpecies[i].closestFood.coordinate.x >= allSpecies[i].coordinate.x &&
                 allSpecies[i].closestFood.coordinate.y >= allSpecies[i].coordinate.y) {
            if (additionX >= allSpecies[i].closestFood.coordinate.x &&
                additionY >= allSpecies[i].closestFood.coordinate.y &&
                allSpecies[i].size >= allSpecies[i].closestFood.size) {
                printf("%d ", i);
                printf("Move right down\n");
                allSpecies[i].direction = 3;
                allSpecies[i] = outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if (allSpecies[i].coordinate.x > allSpecies[i].closestFood.coordinate.x) {
                    allSpecies[i].coordinate.x = allSpecies[i].closestFood.coordinate.x;
                }
                if (allSpecies[i].coordinate.y > allSpecies[i].closestFood.coordinate.y) {
                    allSpecies[i].coordinate.y = allSpecies[i].closestFood.coordinate.y;
                }
            } else {
                allSpecies[i].direction = (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i] = outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
            //Case 4, right up
        else if (allSpecies[i].closestFood.coordinate.x >= allSpecies[i].coordinate.x &&
                 allSpecies[i].closestFood.coordinate.y <= allSpecies[i].coordinate.y) {
            if (additionX >= allSpecies[i].closestFood.coordinate.x &&
                differenceY <= allSpecies[i].closestFood.coordinate.y &&
                allSpecies[i].size >= allSpecies[i].closestFood.size) {
                printf("%d ", i);
                printf("Move right up");
                allSpecies[i].direction = 4;
                allSpecies[i] = outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);


                if (allSpecies[i].coordinate.x > allSpecies[i].closestFood.coordinate.x) {
                    allSpecies[i].coordinate.x = allSpecies[i].closestFood.coordinate.x;
                }
                if (allSpecies[i].coordinate.y < allSpecies[i].closestFood.coordinate.y) {
                    allSpecies[i].coordinate.y = allSpecies[i].closestFood.coordinate.y;
                }
            } else {
                allSpecies[i].direction = (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i] = outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
    }
}

void addClosestFood(Specie array[], food comida[]) {
    for (int i = 0; i < POPULATION; i++) {
        array[i].closestFood = findFood(array[i].coordinate, comida);
    }
}

//
//Encuentra la comida más cerca de la celula
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


//Checa si no se ha salido de los bordes del mapa
Specie outBounders(Specie dude) {
    Specie dudeprueba = moveTowardsFood(dude, dude.direction);
    if (dudeprueba.coordinate.x < 0 || dudeprueba.coordinate.x > 1300 || dudeprueba.coordinate.y < 0 ||
        dudeprueba.coordinate.y > 600) {
        switch (dude.direction) {
            case 1:
                dude.direction = 4;
                break;

            case 2:
                dude.direction = 3;
                break;

            case 3:
                dude.direction = 2;
                break;

            case 4:
                dude.direction = 1;
                break;
        }
    }

    return dude;
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