#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "../headers/selection.h"
#include "../headers/globals.h"


int main() {

    srand(time(NULL));

    int maxSize;
    int amountOfFood;
    int extinction;
    int countFrames =0;
    float volumen;
    Specie allspecies[100];
    food comida[MAP_FOOD];

    createPopulation(allspecies);
    maxSize = meanSizeSpecies(allspecies);
    createFoodPos(comida, maxSize);


    InitWindow(1300, 600, "The Life");
    InitAudioDevice();
    SetTargetFPS(20);


    Music musiquita = LoadMusicStream("../Assets/pou.mp3");
    Image cookie = LoadImage("../Assets/cookie4.png");
    ImageResize(&cookie, 100, 100);
    UnloadImage(cookie);

    Texture2D texture = LoadTextureFromImage(cookie);


    PlayMusicStream(musiquita);

    while (!WindowShouldClose()) {

        volumen = 1.0;

        PlayMusicStream(musiquita);
        SetMusicVolume(musiquita, volumen);
        UpdateMusicStream(musiquita);

        ClearBackground(BLACK);

        BeginDrawing();

        //Draws the food in the map
        amountOfFood = quantityOfFood(comida);
        for (int j = 0; j < MAP_FOOD; j++) {
            Vector2 position = {(float) comida[j].coordinate.x, (float) comida[j].coordinate.y};
            DrawTextureEx(texture, position, 0.0f, (float) comida[j].size / 50, WHITE);
        }

        checkIsRadious(allspecies, comida);
        Collision(allspecies, comida);

        //Draws the species in the map
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

        // Detects either when the food is over or the frame period is over.
        if (amountOfFood == MAP_FOOD || countFrames > 70) {
            countFrames = 0;
            killSpecie(allspecies);
            AsexualReproduction(allspecies);
            maxSize = meanSizeSpecies(allspecies);
            createFoodPos(comida, maxSize);
        }

        extinction = endOfWorld(allspecies);

        //Checks if the size of at least one of the species is greater than the allowed and if there is only one specie left
        if(extinction>=70 && survivingSpecie(allspecies) == 0){
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




