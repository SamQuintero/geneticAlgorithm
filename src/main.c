#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "../headers/selection.h"
#include "../headers/globals.h"


//void printPopulation(Specie dudearray[]);

int main() {
    srand(time(NULL));

    int maxSize;
    int amountOfFood;
    int extinction;
    int countFrames =0;
    Specie allspecies[100];
    food comida[MAP_FOOD];

    createPopulation(allspecies);
    maxSize = meanSizeSpecies(allspecies);
    createFoodPos(comida, maxSize);


    InitWindow(1300, 600, "The Life");
    SetTargetFPS(100);

    InitAudioDevice();
    Music musiquita = LoadMusicStream("../Assets/pou.mp3");
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

        ClearBackground(BLACK);

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
                               PINK);
                    break;
                case 2:
                    DrawCircle(allspecies[i].coordinate.x, allspecies[i].coordinate.y, allspecies[i].size / 2,
                               BLUE);
                    break;
                case 4:
                    DrawCircle(allspecies[i].coordinate.x, allspecies[i].coordinate.y, allspecies[i].size / 2,
                               GREEN);
                    break;
                default:
                    printf(":)");
            }
        }

        countFrames++;
        // Detecta cuando se acaba la comida o el periodo generacional para matar a las especies tontas
        if (amountOfFood == MAP_FOOD || countFrames > 70) {
            countFrames = 0;
            printf("Frames %d \n", countFrames);
            killSpecie(allspecies);
            AsexualReproduction(allspecies);
            maxSize = meanSizeSpecies(allspecies);
            printf("Max %d: ", maxSize);
            createFoodPos(comida, maxSize);
            printf("%d", POPULATION);
        }
        extinction = endOfWorld(allspecies);
        if(extinction>=70){
            UnloadTexture(texture);
            UnloadMusicStream(musiquita);
            CloseAudioDevice();
            CloseWindow();
            return 0;
        }

        EndDrawing();
    }
    return 0;
}


/*void printPopulation(Specie dudearray[]) {
    for (int i = 0; i < POPULATION; i++) {
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", dudearray[i].ID, dudearray[i].speed, dudearray[i].visibility,
               dudearray[i].size, dudearray[i].coordinate.x, dudearray[i].coordinate.y,
               dudearray[i].closestFood.coordinate.x,
               dudearray[i].closestFood.coordinate.y, dudearray[i].fat, dudearray[i].closestFood.size);
        printf("\n");
    }

}*/

