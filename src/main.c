#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include <math.h>
#include "../specie.h"
#include "../globals.h"


void printPopulation(Specie dudearray[]);

food findFood(pos dude, food comida[]);

void addClosestFood(Specie array[], food comida[]);

int checkIsRadious(Specie allSpecies[], food comida[]);

void Collision(Specie allSpecies[], food comida[]);

Specie outBounders(Specie dude);

Specie moveTowardsFood(Specie specie, int direction);

void killSpecie(Specie allSpcies[]);

void AsexualReproduction(Specie allSpecies[]);

int graveyard(Specie allSpecies[]);

void assignPos(Specie allSpecies[]);

void mutation(Specie allSpecies[], int oldies);


int main() {
    srand(time(NULL));
    MAP_FOOD = 20;
    POPULATION = 50;

    int maxSize;
    int amountOfFood;
    int countFrames =0;
    Specie allspecies[100];
    food comida[MAP_FOOD];

    createPopulation(allspecies);
    maxSize = maxSizeSpecies(allspecies);
    createFoodPos(comida, maxSize);


    InitWindow(1300, 600, "The Life");
    SetTargetFPS(20);
    InitAudioDevice();
    Music musiquita = LoadMusicStream("../Assets/pou.mpeg");
    Image cookie = LoadImage("../Assets/cookie4.png");
    ImageResize(&cookie, 100, 100);
    UnloadImage(cookie);
    Texture2D texture = LoadTextureFromImage(cookie);


    PlayMusicStream(musiquita);
    while (!WindowShouldClose()) {

        float volumen = 1.0;

        PlayMusicStream(musiquita);
        SetMusicVolume(musiquita, volumen);
        UpdateMusicStream(musiquita);

        ClearBackground(WHITE);
        BeginDrawing();


        //Dibuja la comida
        amountOfFood = quantityOfFood(comida);
        for (int j = 0; j < MAP_FOOD; j++) {
            Vector2 position = {(float) comida[j].coordinate.x, (float) comida[j].coordinate.y};
            //DrawCircle(comida[j].coordinate.x, comida[j].coordinate.y, comida[j].size / 2, RED);
            DrawTextureEx(texture, position, 0.0f, (float) comida[j].size / 50, WHITE);
        }

        checkIsRadious(allspecies, comida);
        Collision(allspecies, comida);
        for (int i = 0; i < POPULATION; i++) {
            switch (allspecies[i].ID) {
                case 1:
                    DrawCircle(allspecies[i].coordinate.x, allspecies[i].coordinate.y, allspecies[i].size / 2,
                               DARKGREEN);
                    break;
                case 2:
                    DrawCircle(allspecies[i].coordinate.x, allspecies[i].coordinate.y, allspecies[i].size / 2,
                               DARKBLUE);
                    break;
                default:
                    printf("Adios");
            }
        }
        printf("\n");
        countFrames++;

        if (amountOfFood == MAP_FOOD || countFrames > 70) {
            countFrames = 0;
            printf("Frames %d \n", countFrames);
            killSpecie(allspecies);
            AsexualReproduction(allspecies);
            maxSize = maxSizeSpecies(allspecies);
            printf("Max %d: ", maxSize);
            createFoodPos(comida, maxSize);
            printf("%d", POPULATION);
        }

        EndDrawing();
    }
    UnloadTexture(texture);
    UnloadMusicStream(musiquita);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}


void addClosestFood(Specie array[], food comida[]) {
    for (int i = 0; i < POPULATION; i++) {
        array[i].closestFood = findFood(array[i].coordinate, comida);
    }
}

void printPopulation(Specie dudearray[]) {
    for (int i = 0; i < POPULATION; i++) {
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", dudearray[i].ID, dudearray[i].speed, dudearray[i].visibility,
               dudearray[i].size, dudearray[i].coordinate.x, dudearray[i].coordinate.y,
               dudearray[i].closestFood.coordinate.x,
               dudearray[i].closestFood.coordinate.y, dudearray[i].fat, dudearray[i].closestFood.size);
        printf("\n");
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

//Esta función detecta en que cuadrante esta la comida más cercana a la celula y si esta dentro de su rango se dirige a ella, si no la mueve de forma random
int checkIsRadious(Specie allSpecies[], food comida[]) {
    int differenceX;
    int differenceY;
    int additionX;
    int additionY;
    int option = 0;
    addClosestFood(allSpecies, comida);
    printPopulation(allSpecies);
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
                printf("[%d, %d]", comida[j].coordinate.x, comida[j].coordinate.y);
            }
        }
    }
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

//Id 3 es la especie del más allá estas species ya pasaron en mejor vida
void killSpecie(Specie allSpcies[]) {
    for (int i = 0; i < POPULATION; i++) {
        if (allSpcies[i].fat == 0) {
            allSpcies[i].ID = 3;
        }
    }
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
        if (allSpecies[r].ID != 3) {
            count++;
        }
    }
    return count;
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