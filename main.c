#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"
#include <math.h>


/*
 Clonación
 Fitness a partir de sobrevivientes, el que tenemos esta feo
 Visibilidad por resistencia
 población cambiante*/
int MAX = 100;


int population = 12;
int foodInMap= 10;
typedef struct {
    int x;
    int y;
} pos;

typedef struct {
    pos cordinate;
    int size;
} food;
typedef struct {

    int speed;
    int ID;
    int visibility;
    int size;
    int fat;
    int direction;
    pos cordinate;
    pos closestFood;

} Specie;


Specie createSample(int id);

void createPopulation(Specie dudearray[]);

void fitness(float **arr);

void printPopulation(Specie dudearray[]);

void createFoodPos(food arr[]);

pos findFood(pos dude, food comida[]);

void addClosestFood(Specie array[], food comida[]);

int checkIsRadious(Specie allSpecies[], food comida[]);

void Collision(Specie allSpecies[], food comida[]);

Specie outBounders(Specie dude);

Specie moveTowardsFood(Specie specie, int direction);

void killSpecie(Specie allSpcies[]);

void quantityOfFood(food comida[], int amountOfFood[1]);

int main() {
    srand(time(NULL));
    InitWindow(1300, 600, "The Life");
    SetTargetFPS(4);
    //Aquí empieza nuestra historia
    Specie allspecies[100];
    int amountOfFood[1]={0};
    createPopulation(allspecies);
    food comida[foodInMap];
    createFoodPos(comida);
    printf("\n");
    //checkIsRadious(allspecies, comida);
    //printPopulation(allspecies);


    //Somos un fracaso
    //Pendiente


    while (!WindowShouldClose()) {


        //DrawTexture(idle, 250,250,WHITE);
        ClearBackground(WHITE);


            SetTargetFPS(4);
            BeginDrawing();
            //dibuja la comida
            for (int j = 0; j < foodInMap; j++) {
                DrawCircle(comida[j].cordinate.x, comida[j].cordinate.y, 5.5, RED);
            }
            //quantityOfFood(comida,amountOfFood);
            checkIsRadious(allspecies, comida);
            Collision(allspecies, comida);
            for (int i = 0; i < population; i++) {
                switch (allspecies[i].ID) {
                    case 1:
                        DrawCircle(allspecies[i].cordinate.x, allspecies[i].cordinate.y, allspecies[i].size / 2,
                                   DARKGREEN);
                        break;
                    case 2:
                        DrawCircle(allspecies[i].cordinate.x, allspecies[i].cordinate.y, allspecies[i].size / 2,
                                   DARKBLUE);
                        break;
                }
            }
            printf("\n");

        /*if(amountOfFood[0]==foodInMap){
            killSpecie(allspecies);

        }*/

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
    dude.speed = rand() % (20 - 5 + 1) + 5;
    dude.visibility = rand() % (500 - 20 + 1) + 20;
    dude.size = rand() % (20 - 11 + 1) + 11;
    dude.fat=0;
    return dude;
}

void addClosestFood(Specie array[], food comida[]) {
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
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d", dudearray[i].ID, dudearray[i].speed, dudearray[i].visibility,
               dudearray[i].size, dudearray[i].cordinate.x, dudearray[i].cordinate.y, dudearray[i].closestFood.x,
               dudearray[i].closestFood.y,dudearray[i].fat);
        printf("\n");
    }

}

void createFoodPos(food arr[]) {
    for (int i = 0; i < foodInMap; i++) {
        arr[i].cordinate.x = rand() % (490 - 10 + 1) + 10;

        arr[i].cordinate.y = rand() % (490 - 10 + 1) + 10;
        printf("%d %d\n", arr[i].cordinate.x, arr[i].cordinate.y);
        arr[i].size=0;
    }

}

pos findFood(pos dude, food comida[]) {
    float distance;
    float mindistance = 10000000;
    pos closestFood;

    for (int i = 0; i < foodInMap; i++) {
        distance = abs(sqrt(pow((comida[i].cordinate.x - dude.x), 2) + pow((comida[i].cordinate.y - dude.y), 2)));
        if (mindistance > distance) {
            mindistance = distance;
            closestFood.x = comida[i].cordinate.x;
            closestFood.y = comida[i].cordinate.y;
        }
    }
    return closestFood;
}
//Esta función detecta en que cuadrante esta la comida más cercana a la celula y si esta dentro de su ramgo se dirige a ella, si no la mueve de forma random
int checkIsRadious(Specie allSpecies[], food comida[]) {
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
                allSpecies[i].direction=1;
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if(allSpecies[i].cordinate.x < allSpecies[i].closestFood.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.x;
                }
                if(allSpecies[i].cordinate.y > allSpecies[i].closestFood.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.y;
                }
            } else {
                allSpecies[i].direction= (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
        //Case 2, left up
        else if (allSpecies[i].closestFood.x <= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.y <= allSpecies[i].cordinate.y) {
            if (differenceX <= allSpecies[i].closestFood.x && differenceY <= allSpecies[i].closestFood.y) {
                printf("%d ", i);
                printf("Move left up\n");
                allSpecies[i].direction=2;
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if(allSpecies[i].cordinate.x < allSpecies[i].closestFood.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.x;
                }
                if(allSpecies[i].cordinate.y < allSpecies[i].closestFood.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.y;
                }
            } else {
                allSpecies[i].direction= (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
        //Case 3, right down
        else if (allSpecies[i].closestFood.x >= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.y >= allSpecies[i].cordinate.y) {
            if (additionX >= allSpecies[i].closestFood.x && additionY >= allSpecies[i].closestFood.y) {
                printf("%d ", i);
                printf("Move right down\n");
                allSpecies[i].direction=3;
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if(allSpecies[i].cordinate.x > allSpecies[i].closestFood.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.x;
                }
                if(allSpecies[i].cordinate.y > allSpecies[i].closestFood.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.y;
                }
            } else {
                allSpecies[i].direction= (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
        //Case 4, right up
        else if (allSpecies[i].closestFood.x >= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.y <= allSpecies[i].cordinate.y) {
            if (additionX >= allSpecies[i].closestFood.x && differenceY <= allSpecies[i].closestFood.y) {
                printf("%d ", i);
                printf("Move right up");
                allSpecies[i].direction=4;
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);


                if(allSpecies[i].cordinate.x > allSpecies[i].closestFood.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.x;
                }
                if(allSpecies[i].cordinate.y < allSpecies[i].closestFood.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.y;
                }
            } else {
                allSpecies[i].direction= (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
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

void Collision(Specie allSpecies[], food comida[]){

    for(int i=0;  i < population; i++){
        if(allSpecies[i].cordinate.x == allSpecies[i].closestFood.x && allSpecies[i].cordinate.y == allSpecies[i].closestFood.y)
        {
            for(int j = 0; j < foodInMap; j++){
                if(comida[j].cordinate.x == allSpecies[i].cordinate.x && comida[j].cordinate.y == allSpecies[i].cordinate.y){
                    comida[j].cordinate.x = -1900;
                    comida[j].cordinate.y = -2900;
                    allSpecies[i].fat+=1;
                }
                printf("[%d, %d]", comida[j].cordinate.x, comida[j].cordinate.y);
            }
        }
    }
}

Specie outBounders(Specie dude){
    Specie dudeprueba= moveTowardsFood(dude, dude.direction);
    if(dudeprueba.cordinate.x<0 || dudeprueba.cordinate.x>1300 || dudeprueba.cordinate.y<0 || dudeprueba.cordinate.y>600){
        switch (dude.direction) {
            case 1:
                dude.direction=4;break;

            case 2:
                dude.direction=3;break;

            case 3:
                dude.direction=2;break;

            case 4:
                dude.direction=1;break;

        }
    }

    return dude;
}

void killSpecie(Specie allSpcies[]){

}
void quantityOfFood(food comida[], int amountOfFood[1]){
    for (int i = 0; i < foodInMap; i++) {
        if (comida[i].cordinate.x < 0 && comida[i].cordinate.y < 0) {
            amountOfFood[0]++;
        }
    }

}