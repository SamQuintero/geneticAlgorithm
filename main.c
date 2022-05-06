#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"
#include <math.h>


/*

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
    food closestFood;

} Specie;


Specie createSample(int id);

void createPopulation(Specie dudearray[]);

void fitness(float **arr);

void printPopulation(Specie dudearray[]);

int maxSizeSpecies(Specie allSpecies[]);

void createFoodPos(food arr[], int maxsize);

food findFood(pos dude, food comida[]);

void addClosestFood(Specie array[], food comida[]);

int checkIsRadious(Specie allSpecies[], food comida[]);

void Collision(Specie allSpecies[], food comida[]);

Specie outBounders(Specie dude);

Specie moveTowardsFood(Specie specie, int direction);

void killSpecie(Specie allSpcies[]);

int quantityOfFood(food comida[]);

void AsexualReproduction(Specie allSpecies[]);


int graveyard(Specie allSpecies[]);

void assignPos(Specie allSpecies[]);

void mutation(Specie allSpecies[], int oldies);


int main() {
    srand(time(NULL));
    InitWindow(1300, 600, "The Life");
    SetTargetFPS(20);
    InitAudioDevice();
    //Aquí empieza nuestra historia
    Specie allspecies[100];

    createPopulation(allspecies);
    int maxSize= maxSizeSpecies(allspecies);
    food comida[foodInMap];
    createFoodPos(comida,maxSize);
    printf("\n");
    Texture2D cookie= LoadTexture("../Assets/cookie.png");
    Music musiquita=LoadMusicStream("../Assets/MusiquitaChila.mp3");


    //Somos un fracaso
    PlayMusicStream(musiquita);
    while (!WindowShouldClose()) {

        float volumen = 1.0;

        PlayMusicStream(musiquita);
        SetMusicVolume(musiquita,volumen);
        UpdateMusicStream(musiquita);


        //DrawTexture(idle, 250,250,WHITE);
        ClearBackground(WHITE);


            SetTargetFPS(4);
            BeginDrawing();
            //dibuja la comida
            int amountOfFood=quantityOfFood(comida);
            printf("\n comida %d\n",amountOfFood);
            printf("\n map %d", foodInMap);
            for (int j = 0; j < foodInMap; j++) {
                DrawCircle(comida[j].cordinate.x, comida[j].cordinate.y, comida[j].size/2, RED);
            }

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
                    default:
                        printf("Adios");
                }
            }
            printf("\n");

        if(amountOfFood==foodInMap){
            killSpecie(allspecies);
            AsexualReproduction(allspecies);
            createFoodPos(comida, maxSize);
            printf("%d", population);

        }

        EndDrawing();
    }
    UnloadMusicStream(musiquita);
    CloseAudioDevice();

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
            dudearray[i].cordinate.x = rand() % (1200 - 20 + 1) + 20;
            dudearray[i].cordinate.y = rand() % (440 - 20 + 1) + 20;
        } else {
            dudearray[i] = dude2;
            dudearray[i].cordinate.x = rand() % (1200 - 20 + 1) + 20;
            dudearray[i].cordinate.y = rand() % (440 - 20 + 1) + 20;
        }
    }

}
int maxSizeSpecies(Specie allSpecies[]){
    if(allSpecies[0].size>allSpecies[1].size )
        return allSpecies[0].size;
    if(allSpecies[0].size<allSpecies[1].size )
        return allSpecies[1].size;
}
void printPopulation(Specie dudearray[]) {
    for (int i = 0; i < population; i++) {
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", dudearray[i].ID, dudearray[i].speed, dudearray[i].visibility,
               dudearray[i].size, dudearray[i].cordinate.x, dudearray[i].cordinate.y, dudearray[i].closestFood.cordinate.x,
               dudearray[i].closestFood.cordinate.y,dudearray[i].fat, dudearray[i].closestFood.size);
        printf("\n");
    }

}
//
void createFoodPos(food arr[], int maxsize) {
    for (int i = 0; i < foodInMap; i++) {
        arr[i].cordinate.x = rand() % (1200 - 20 + 1) + 20;

        arr[i].cordinate.y = rand() % (440 - 20 + 1) + 20;
        printf("%d %d\n", arr[i].cordinate.x, arr[i].cordinate.y);
        arr[i].size=rand() % (maxsize- 5 + 1) + 5;

    }

}
//Encuentra la comida más cerca de la celula
food findFood(pos dude, food comida[]) {
    float distance;
    float mindistance = 10000000;
    food closestFood;

    for (int i = 0; i < foodInMap; i++) {
        distance = abs(sqrt(pow((comida[i].cordinate.x - dude.x), 2) + pow((comida[i].cordinate.y - dude.y), 2)));
        if (mindistance > distance) {
            mindistance = distance;
            closestFood.cordinate.x = comida[i].cordinate.x;
            closestFood.cordinate.y = comida[i].cordinate.y;
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
    for (int i = 0; i < population; i++) {
        differenceX = allSpecies[i].cordinate.x - allSpecies[i].visibility;
        differenceY = allSpecies[i].cordinate.y - allSpecies[i].visibility;
        additionX = allSpecies[i].cordinate.x + allSpecies[i].visibility;
        additionY = allSpecies[i].cordinate.y + allSpecies[i].visibility;
        //Case 1, left down
        if (allSpecies[i].closestFood.cordinate.x <= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.cordinate.y >= allSpecies[i].cordinate.y) {
            if (differenceX <= allSpecies[i].closestFood.cordinate.x && additionY >= allSpecies[i].closestFood.cordinate.y && allSpecies[i].size >= allSpecies[i].closestFood.size) {
                printf("%d ", i);
                printf("Move left down\n");
                allSpecies[i].direction=1;
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if(allSpecies[i].cordinate.x < allSpecies[i].closestFood.cordinate.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.cordinate.x;
                }
                if(allSpecies[i].cordinate.y > allSpecies[i].closestFood.cordinate.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.cordinate.y;
                }
            } else {
                allSpecies[i].direction= (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
        //Case 2, left up
        else if (allSpecies[i].closestFood.cordinate.x <= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.cordinate.y <= allSpecies[i].cordinate.y) {
            if (differenceX <= allSpecies[i].closestFood.cordinate.x && differenceY <= allSpecies[i].closestFood.cordinate.y && allSpecies[i].size >= allSpecies[i].closestFood.size) {
                printf("%d ", i);
                printf("Move left up\n");
                allSpecies[i].direction=2;
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if(allSpecies[i].cordinate.x < allSpecies[i].closestFood.cordinate.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.cordinate.x;
                }
                if(allSpecies[i].cordinate.y < allSpecies[i].closestFood.cordinate.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.cordinate.y;
                }
            } else {
                allSpecies[i].direction= (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
        //Case 3, right down
        else if (allSpecies[i].closestFood.cordinate.x >= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.cordinate.y >= allSpecies[i].cordinate.y) {
            if (additionX >= allSpecies[i].closestFood.cordinate.x && additionY >= allSpecies[i].closestFood.cordinate.y && allSpecies[i].size >= allSpecies[i].closestFood.size) {
                printf("%d ", i);
                printf("Move right down\n");
                allSpecies[i].direction=3;
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
                if(allSpecies[i].cordinate.x > allSpecies[i].closestFood.cordinate.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.cordinate.x;
                }
                if(allSpecies[i].cordinate.y > allSpecies[i].closestFood.cordinate.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.cordinate.y;
                }
            } else {
                allSpecies[i].direction= (rand() % (4 - 1 + 1) + 1);
                printf("%d %d\n", i, allSpecies[i].direction);
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);
            }
        }
        //Case 4, right up
        else if (allSpecies[i].closestFood.cordinate.x >= allSpecies[i].cordinate.x &&
            allSpecies[i].closestFood.cordinate.y <= allSpecies[i].cordinate.y) {
            if (additionX >= allSpecies[i].closestFood.cordinate.x && differenceY <= allSpecies[i].closestFood.cordinate.y && allSpecies[i].size >= allSpecies[i].closestFood.size) {
                printf("%d ", i);
                printf("Move right up");
                allSpecies[i].direction=4;
                allSpecies[i]=outBounders(allSpecies[i]);
                allSpecies[i] = moveTowardsFood(allSpecies[i], allSpecies[i].direction);


                if(allSpecies[i].cordinate.x > allSpecies[i].closestFood.cordinate.x){
                    allSpecies[i].cordinate.x = allSpecies[i].closestFood.cordinate.x;
                }
                if(allSpecies[i].cordinate.y < allSpecies[i].closestFood.cordinate.y){
                    allSpecies[i].cordinate.y = allSpecies[i].closestFood.cordinate.y;
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

//Para dirigir la celula hacia la comida o algun punto
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
//Detecta si la celula comió
void Collision(Specie allSpecies[], food comida[]){

    for(int i=0;  i < population; i++){
        if(allSpecies[i].cordinate.x == allSpecies[i].closestFood.cordinate.x && allSpecies[i].cordinate.y == allSpecies[i].closestFood.cordinate.y)
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
//Checa si no se ha salido de los bordes del mapa
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
//Id 3 es la especie del más allá estas species ya pasaron en mejor vida
void killSpecie(Specie allSpcies[]){
    for(int i=0; i<population;i++){
        if (allSpcies[i].fat==0){
            allSpcies[i].ID=3;
        }
    }
}

//Para saber si aun queda comida dentro del mapa
int quantityOfFood(food comida[]){
    int contador=0;
    for (int i = 0; i < foodInMap; i++) {
        if (comida[i].cordinate.x < 0 && comida[i].cordinate.y < 0) {
            contador++;
        }
    }
    return contador;
}
//Recorre las especies muertas y contabiliza cuantas sobrevivieron
int graveyard(Specie allSpecies[]) {
    Specie temp;
    for (int i = 1; i < population; i++) {
        for (int j = 0; j < i; j++) {
            if (allSpecies[i].ID < allSpecies[j].ID) {
                temp = allSpecies[i];
                allSpecies[i] = allSpecies[j];
                allSpecies[j] = temp;

            }
        }

    }
    int count=0;
    for(int r=0; r<population;r++){
        if(allSpecies[r].ID!=3){
            count++;
        }

    }
    return count;
}
//Las especies se reproducen de forma asexual
void AsexualReproduction(Specie allSpecies[]){
    int survivor= graveyard(allSpecies);
    int oldies=survivor;

    for (int i=0; i<oldies;i++){
        if(allSpecies[i].fat>1){
            allSpecies[survivor]=allSpecies[i];
            survivor++;
        }
    }
    for(int i=0;i< population;i++){
        allSpecies[i].fat=0;
    }
    population=survivor;
    printf(":(");
    assignPos(allSpecies);
    printf(":(");
    mutation(allSpecies, oldies);

    }

void assignPos(Specie allSpecies[]){
    for (int i = 0; i < population; i++){
    allSpecies[i].cordinate.x = rand() % (1200 - 10 + 1) + 10;
    allSpecies[i].cordinate.y = rand() % (440 - 10 + 1) + 10;
    }

}
void mutation(Specie allSpecies[], int oldies){
    for (int i = oldies; i <population ; ++i) {
        int probability=rand() % (3 - 1 + 1) + 1;
        printf("probabilidad %d",probability);
        if(probability==2){
            int whosechanging=rand() % (4 - 1 + 1) + 1;

            switch (whosechanging){
                case 2:
                    allSpecies[i].speed+=10;
                    break;
                case 3:
                    allSpecies[i].visibility+=10;
                    break;
                case 4:
                    allSpecies[i].size+=10;
                    break;
            }

        }

    }


}