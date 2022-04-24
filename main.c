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
typedef struct
{
    int x;
    int y;
}pos;
typedef struct
{

    int speed;
    int ID;
    int visibility;
    int size;
    pos cordinate;
    pos closestFood;
}Specie;


Specie createSample(int id);

void createPopulation(Specie dudearray[]);

void fitness(float **arr);

void printPopulation(Specie dudearray[]);

void matingPopulation(float **arr);

void extrapolationCrossover(float **arr);

void createFoodPos(pos arr[]);
pos findFood(pos dude, pos comida[]);
void addClosestFood(Specie array[],pos comida[]);

int main() {
    srand(time(NULL));
    InitWindow(1300, 600, "The Life");
    SetTargetFPS(10);
    //Aquí empieza nuestra historia
    Specie allspecies[100];

    createPopulation(allspecies);
    pos comida[population/2];
    createFoodPos(comida);
    addClosestFood(allspecies,comida);
    printPopulation(allspecies);
    printf("\n");





    while(!WindowShouldClose())
    {


        BeginDrawing();
        //DrawTexture(idle, 250,250,WHITE);
        ClearBackground(WHITE);

        for(int i=0;i<population;i++){

            switch(allspecies[i].ID) {
                case 1:
                    DrawCircle(allspecies[i].cordinate.x,allspecies[i].cordinate.y, allspecies[i].size/2, DARKGREEN);break;
                case 2:
                    DrawCircle(allspecies[i].cordinate.x,allspecies[i].cordinate.y, allspecies[i].size/2, DARKBLUE);break;

            }

            for(int j=0;j<=population/2;j++){
                DrawCircle(comida[j].x,comida[j].y, 5.5, (Color){170,119,0,50});
            }



        }


        EndDrawing();
    }

    CloseWindow();



    return 0;
}
//
//Aquí se crea todos los valores de una especie
Specie createSample(int id){

    Specie dude;
    dude.ID=id;
    dude.speed=(int) rand() / (int) (RAND_MAX / MAX);
    dude.visibility=(int) rand() / (int) (RAND_MAX / MAX);
    dude.size=rand() % (20-11+1)+11;


    return dude;
}
void addClosestFood(Specie array[],pos comida[]){
    for(int i=0;i<population;i++){
        array[i].closestFood= findFood(array[i].cordinate,comida);
    }
}
void createPopulation(Specie dudearray[]) {
    Specie dude1=createSample(1);
    Specie dude2=createSample(2);

    for (int i = 0; i <population ; i++) {

        if (i%2){
            dudearray[i] = dude1 ;
            dudearray[i].cordinate.x=rand() % (490-10+1)+10;
            dudearray[i].cordinate.y=rand() % (490-10+1)+10;
        }
        else{
            dudearray[i] = dude2;
            dudearray[i].cordinate.x=rand() % (490-10+1)+10;
            dudearray[i].cordinate.y=rand() % (490-10+1)+10;
        }


    }

}

void fitness(float **arr) {

}

void printPopulation(Specie dudearray[]) {
    for (int i = 0; i < population; i++) {
        printf("%d,%d,%d,%d,%d,%d,%d,%d", dudearray[i].ID,dudearray[i].speed,dudearray[i].visibility,dudearray[i].size,dudearray[i].cordinate.x,dudearray[i].cordinate.y,dudearray[i].closestFood.x,dudearray[i].closestFood.y);
        printf("\n");
    }

}
//Acomodamos las especies por su fitness
void matingPopulation(float **arr) {

    float *temp = (float *) malloc(7 * sizeof(float));
//InsertionSort matriz
    for (int i = 1; i < population; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i][4] > arr[j][4]) {
                memcpy(temp, arr[i], sizeof(float) * 7);
                memcpy(arr[i], arr[j], sizeof(float) * 7);
                memcpy(arr[j], temp, sizeof(float) * 7);
            }
        }
    }

    free(temp);
}

//안녕하세요, 선생님, 10점을 받으면 좋겠습니다 ^^
//De aquí salen los bebés
void extrapolationCrossover(float **arr) {


    float mutatedGene = 0;
    float mutatedGene2 = 0;
    for (int i = 0; i < population / 2; i += 2) {
        int cuttingIndex = (int) rand() % (4-1+1)+1;
        int scalar = (int) rand() / (int) (RAND_MAX / 2);
        float var1 = arr[i][cuttingIndex];
        float var2 = arr[i + 1][cuttingIndex];
        do {
            mutatedGene = var1 - scalar * (var1 - var2);
        } while (mutatedGene > 10);
        arr[population / 2 + i][cuttingIndex] = mutatedGene;
        do {
            mutatedGene2 = var2 + scalar * (var1 - var2);
        } while (mutatedGene2 > 10);
        arr[population / 2 + i + 1][cuttingIndex] = mutatedGene2;
    }
    fitness(arr);
}

void createFoodPos(pos arr[])
{
    for(int i=0;i<=population/2;i++)
    {
        arr[i].x=rand() % (490-10+1)+10;

        arr[i].y=rand() % (490-10+1)+10;
        printf("%d %d\n",arr[i].x,arr[i].y);
    }



}
pos findFood(pos dude, pos comida[]){
    float distance;
    float mindistance=10000000;
    pos closestFood;

    for(int i=0;i<=population/2;i++){
        distance= abs(sqrt(pow((comida[i].x-dude.x),2)+pow((comida[i].y-dude.y),2)));
        if(mindistance>distance){
            mindistance=distance;
            closestFood.x=comida[i].x;
            closestFood.y=comida[i].y;
        }
    }
return closestFood;
}
