#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"

int MAX = 10;

int population = 16;
typedef struct
{
    int x;
    int y;
}food;



void createSample(float *arr);

void createPopulation(float **arr);

void fitness(float **arr);

void printPopulation(float **arr);

void matingPopulation(float **arr);

void extrapolationCrossover(float **arr);

void createFoodPos(food arr[]);

int main() {
    srand(time(NULL));
    InitWindow(500, 500, "The Life");
    SetTargetFPS(10);
    //Aquí empieza nuestra historia
    float **arr = (float **) malloc(population * sizeof(float *));
    createPopulation(arr);
    fitness(arr);
    matingPopulation(arr);
    printPopulation(arr);
    printf("\n");
    extrapolationCrossover(arr);
    printPopulation(arr);
    food comida[population/2];
    createFoodPos(comida);



    while(!WindowShouldClose())
    {


        BeginDrawing();
        //DrawTexture(idle, 250,250,WHITE);
        ClearBackground(WHITE);

        for(int i=0;i<population;i++){

            switch((int)arr[i][0]) {
                case 1:
                    DrawCircle((int)arr[i][5],(int)arr[i][6], 5.5, DARKGREEN);break;
                case 2:
                    DrawCircle((int)arr[i][5],(int)arr[i][6], 5.5, DARKBLUE);break;
                case 3:
                    DrawCircle((int)arr[i][5],(int)arr[i][6], 5.5, (Color){0,25 ,67,123});break;
                case 4:
                    DrawCircle((int)arr[i][5],(int)arr[i][6], 5.5, PURPLE);break;
            }

            for(int j=0;j<=population/2;j++){
                DrawCircle(comida[i].x,comida[i].y, 5.5, (Color){170,119,0,50});
            }



        }


        EndDrawing();
    }

    CloseWindow();

    for (int i = 0; i < population; i++)
        free(arr[i]);

    free(arr);


    return 0;
}

void createSample(float *arr) {

    for (int gen = 1; gen < 4; gen++) {
        arr[gen] = (float) rand() / (float) (RAND_MAX / MAX);

    }
    arr[5]=(float) rand() / (float) (RAND_MAX / 500);
    arr[6]=(float) rand() / (float) (RAND_MAX / 500);

}

void createPopulation(float **arr) {
    for (int i = 0; i < population; i++) {
        arr[i] = (float *) malloc(7 * sizeof(float));
        createSample(arr[i]);
    }
    int max=4;
    int j=0;
    int cons=1;
    for(int i=0;i<4;i++){
        for (j;j<max;j++){
            arr[j][0]=(float)cons;
        }
        max+=4;
        cons+=1;

    }


}

void fitness(float **arr) {
    for (int sample = 0; sample < population; sample++) {
        arr[sample][4] = arr[sample][1] + arr[sample][2] - arr[sample][3];
    }
}

void printPopulation(float **arr) {
    for (int i = 0; i < population; i++) {
        for (int j = 0; j < 7; j++)
            printf("%f ", arr[i][j]);
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

void createFoodPos(food arr[])
{
    for(int i=0;i<=population/2;i++)
    {
        arr[i].x=(int) rand() / (int) (RAND_MAX / 500);
        arr[i].y=(int) rand() / (int) (RAND_MAX / 500);
    }



}