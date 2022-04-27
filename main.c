#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"
#include <math.h>


/* Cambiar estructuras a structs
 Clonación
 Fitness a partir de sobrevivientes, el que tenemos esta feo
 Visibilidad por resistencia
 población cambiante*/
int MAX = 100;


int population = 8;
typedef struct {
    int x;
    int y;
} pos;
typedef struct {

    int speed;
    int ID;
    int visibility;
    int size;
    int fat;
    pos cordinate;
    pos closestFood;
} Specie;


Specie createSample(int id);

void createPopulation(Specie dudearray[]);

void fitness(float **arr);

void printPopulation(Specie dudearray[]);

void createFoodPos(pos arr[]);

pos findFood(pos dude, pos comida[]);

void addClosestFood(Specie array[], pos comida[]);

int checkIsRadious(Specie allSpecies[], pos comida[]);

void Collision(Specie allSpecies[], pos comida[]);

Specie moveTowardsFood();

int main() {
    srand(time(NULL));
    InitWindow(1300, 600, "The Life");
    SetTargetFPS(10);
    //Aquí empieza nuestra historia
    Specie allspecies[100];

    createPopulation(allspecies);
    pos comida[population / 2];
    createFoodPos(comida);
    printf("\n");
    //checkIsRadious(allspecies, comida);
    //printPopulation(allspecies);


    //Somos un fracaso
    //Pendiente
 int amountFood = 0;
    do {
        amountFood = 0;
        for (int i = 0; i < population / 2; i++) {
            if (comida[i].x > 0 && comida[i].y > 0) {
                amountFood++;
            }
        }
        checkIsRadious(allspecies, comida);
        Collision(allspecies, comida);

    }while(amountFood > 0);




    while (!WindowShouldClose()) {

        BeginDrawing();
        //DrawTexture(idle, 250,250,WHITE);
        ClearBackground(WHITE);

        for (int i = 0; i < population; i++) {

            switch (allspecies[i].ID) {
                case 1:
                    DrawCircle(allspecies[i].cordinate.x, allspecies[i].cordinate.y, allspecies[i].size / 2, DARKGREEN);
                    break;
                case 2:
                    DrawCircle(allspecies[i].cordinate.x, allspecies[i].cordinate.y, allspecies[i].size / 2, DARKBLUE);
                    break;
            }

            for (int j = 0; j <= population / 2; j++) {
                DrawCircle(comida[j].x, comida[j].y, 5.5, (Color) {170, 119, 0, 50});
            }

        }

        DrawCircle(-1, -1,  5.5, ORANGE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

//
//Aquí se crea todos los valores de una especie
Specie createSample(int id) {

    Specie dude;
    dude.ID = id;
    dude.speed = (int) rand() / (int) (RAND_MAX / 10);
    dude.visibility = (int) rand() / (int) (RAND_MAX / MAX);
    dude.size = rand() % (20 - 11 + 1) + 11;

    return dude;
}

void addClosestFood(Specie array[], pos comida[]) {
    for (int i = 0; i < population; i++) {
        array[i].closestFood = findFood(array[i].cordinate, comida);
    }
}

void createPopulation(Specie dudearray[]) {
    Specie dude1 = createSample(1);
    Specie dude2 = createSample(2);

    for (int i = 0; i < population; i++) {

        if (i % 2) {
            dudearray[i] = dude1;
            dudearray[i].cordinate.x = rand() % (490 - 10 + 1) + 10;
            dudearray[i].cordinate.y = rand() % (490 - 10 + 1) + 10;
        } else {
            dudearray[i] = dude2;
            dudearray[i].cordinate.x = rand() % (490 - 10 + 1) + 10;
            dudearray[i].cordinate.y = rand() % (490 - 10 + 1) + 10;
        }
    }
}

void printPopulation(Specie dudearray[]) {
    for (int i = 0; i < population; i++) {
        printf("%d,%d,%d,%d,%d,%d,%d,%d", dudearray[i].ID, dudearray[i].speed, dudearray[i].visibility,
               dudearray[i].size, dudearray[i].cordinate.x, dudearray[i].cordinate.y, dudearray[i].closestFood.x,
               dudearray[i].closestFood.y);
        printf("\n");
    }

}

void createFoodPos(pos arr[]) {
    for (int i = 0; i <= population / 2; i++) {
        arr[i].x = rand() % (490 - 10 + 1) + 10;

        arr[i].y = rand() % (490 - 10 + 1) + 10;
        printf("%d %d\n", arr[i].x, arr[i].y);
    }

}

pos findFood(pos dude, pos comida[]) {
    float distance;
    float mindistance = 10000000;
    pos closestFood;

    for (int i = 0; i <= population / 2; i++) {
        distance = abs(sqrt(pow((comida[i].x - dude.x), 2) + pow((comida[i].y - dude.y), 2)));
        if (mindistance > distance) {
            mindistance = distance;
            closestFood.x = comida[i].x;
            closestFood.y = comida[i].y;
        }
    }
    return closestFood;
}

int checkIsRadious(Specie allSpecies[], pos comida[]) {
    int differenceX;
    int differenceY;
    int additionX;
    int additionY;
    int option = 0;
    addClosestFood(allSpecies, comida);
    printPopulation(allSpecies);
    for (int i = 0; i < population; i++) {
        differenceX = allSpecies[i].cordinate.x - allSpecies[i].visibility;
        differenceY = allSpecies[i].cordinate.y - allSpecies[i].visibility;
        additionX = allSpecies[i].cordinate.x + allSpecies[i].visibility;
        additionY = allSpecies[i].cordinate.y + allSpecies[i].visibility;
        //Case 1, left down
        if (allSpecies[i].closestFood.x <= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.y >= allSpecies[i].cordinate.y) {
            if (differenceX <= allSpecies[i].closestFood.x && additionY >= allSpecies[i].closestFood.y) {
                printf("%d ", i);
                printf("Move left down\n");
                allSpecies[i] = moveTowardsFood(allSpecies[i], 1);
                if(allSpecies[i].cordinate.x < allSpecies[i].closestFood.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.x;
                }
                if(allSpecies[i].cordinate.y > allSpecies[i].closestFood.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.y;
                }
            } else {
                option = (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, option);
                allSpecies[i] = moveTowardsFood(allSpecies[i], option);
            }
        }
        //Case 2, left up
        else if (allSpecies[i].closestFood.x <= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.y <= allSpecies[i].cordinate.y) {
            if (differenceX <= allSpecies[i].closestFood.x && differenceY <= allSpecies[i].closestFood.y) {
                printf("%d ", i);
                printf("Move left up\n");
                allSpecies[i] =moveTowardsFood(allSpecies[i], 2);
                if(allSpecies[i].cordinate.x < allSpecies[i].closestFood.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.x;
                }
                if(allSpecies[i].cordinate.y < allSpecies[i].closestFood.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.y;
                }
            } else {
                option = (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, option);
                allSpecies[i] = moveTowardsFood(allSpecies[i], option);
            }
        }
        //Case 3, right down
        else if (allSpecies[i].closestFood.x >= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.y >= allSpecies[i].cordinate.y) {
            if (additionX >= allSpecies[i].closestFood.x && additionY >= allSpecies[i].closestFood.y) {
                printf("%d ", i);
                printf("Move right down\n");
                allSpecies[i] = moveTowardsFood(allSpecies[i], 3);
                if(allSpecies[i].cordinate.x > allSpecies[i].closestFood.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.x;
                }
                if(allSpecies[i].cordinate.y > allSpecies[i].closestFood.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.y;
                }
            } else {
                option = (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, option);
                allSpecies[i] = moveTowardsFood(allSpecies[i], option);
            }
        }
        //Case 4, right up
        else if (allSpecies[i].closestFood.x >= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.y <= allSpecies[i].cordinate.y) {
            if (additionX >= allSpecies[i].closestFood.x && differenceY <= allSpecies[i].closestFood.y) {
                printf("%d ", i);
                printf("Move right up");
                allSpecies[i] = moveTowardsFood(allSpecies[i], 4);
                if(allSpecies[i].cordinate.x > allSpecies[i].closestFood.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.x;
                }
                if(allSpecies[i].cordinate.y < allSpecies[i].closestFood.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.y;
                }
            } else {
                option = (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, option);
                allSpecies[i] = moveTowardsFood(allSpecies[i], option);
            }
        }
    }
}


Specie moveTowardsFood(Specie specie, int direction) {
    switch (direction) {
        case 1:
            specie.cordinate.x-= specie.speed;
            specie.cordinate.y += specie.speed;
            break;
        case 2:
            specie.cordinate.x -= specie.speed;
            specie.cordinate.y -= specie.speed;
            break;
        case 3:
            specie.cordinate.x += specie.speed;
            specie.cordinate.y += specie.speed;
            break;
        case 4:
            specie.cordinate.x += specie.speed;
            specie.cordinate.y -= specie.speed;
            break;
        default:
            break;
    }
    return specie;
}

void Collision(Specie allSpecies[], pos comida[]){

    for(int i=0;  i < population; i++){
        if(allSpecies[i].cordinate.x == allSpecies[i].closestFood.x && allSpecies[i].cordinate.y == allSpecies[i].closestFood.y)
        {
            for(int j = 0; j < population/2; j++){
                if(comida[j].x == allSpecies[i].cordinate.x && comida[j].y == allSpecies[i].cordinate.y){
                    comida[j].x = -190;
                    comida[j].y = -290;
                }
                printf("%d, %d", comida[j].x, comida[j].y);
            }
        }
    }
}




