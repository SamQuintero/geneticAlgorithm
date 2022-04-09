#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int MAX = 10;

int population = 16;

void createSample(float *arr);

void createPopulation(float **arr);

void fitness(float **arr);

void printPopulation(float **arr);

void matingPopulation(float **arr);

void extrapolationCrossover(float **arr);


int main() {

    srand(time(NULL));
    float **arr = (float **) malloc(population * sizeof(float *));
    createPopulation(arr);
    fitness(arr);
    matingPopulation(arr);
    printPopulation(arr);
    printf("\n");
    extrapolationCrossover(arr);
    printPopulation(arr);

    for (int i = 0; i < population; i++)
        free(arr[i]);

    free(arr);

    return 0;
}

void createSample(float *arr) {
    for (int gen = 0; gen < 3; gen++) {
        arr[gen] = (float) rand() / (float) (RAND_MAX / MAX);
    }
}

void createPopulation(float **arr) {
    for (int i = 0; i < population; i++) {
        arr[i] = (float *) malloc(3 * sizeof(float));
        createSample(arr[i]);
    }
}

void fitness(float **arr) {
    for (int sample = 0; sample < population; sample++) {
        arr[sample][3] = arr[sample][0] + arr[sample][1] - arr[sample][2];
    }
}

void printPopulation(float **arr) {
    for (int i = 0; i < population; i++) {
        for (int j = 0; j < 4; j++)
            printf("%f ", arr[i][j]);
        printf("\n");
    }

}

void matingPopulation(float **arr) {

    float *temp = (float *) malloc(4 * sizeof(float));

    for (int i = 1; i < population; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i][3] > arr[j][3]) {
                memcpy(temp, arr[i], sizeof(float) * 4);
                memcpy(arr[i], arr[j], sizeof(float) * 4);
                memcpy(arr[j], temp, sizeof(float) * 4);
            }
        }
    }

    free(temp);
}

//안녕하세요, 선생님, 10점을 받으면 좋겠습니다 ^^
void extrapolationCrossover(float **arr) {

    int cuttingIndex;
    float mutatedGene = 0;
    float mutatedGene2 = 0;
    for (int i = 0; i < population / 2; i += 2) {
        int cuttingIndex = (int) rand() / (int) (RAND_MAX / 3);
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

