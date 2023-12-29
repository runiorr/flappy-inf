#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include "player.h"
#include "sprite.h"

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    InitWindow(screenWidth, screenHeight, "raylib [texture] example - sprite anim");

    Texture2D background = LoadTexture("resources/scenario/background_day.png");
    // Texture2D pipeTexture = LoadTexture("resources/obstaculo.png");

    Image spriteImage = LoadImage("resources/flappy/flappy_mov_red.png");
    Texture2D *textures = load_textures(spriteImage, 3);
    Player player = {
        .textures = textures,
        .current = textures[0],
        .position = {(float)screenWidth / 4, (float)screenHeight / 2},
        .velocity = {0, 0},
        .jumpSpeed = 8.0f};

    int framesCounter = 0;
    int framesSpeed = 6; // Number of spritesheet frames shown by second
    int currentFrame = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update texture frame
        //----------------------------------------------------------------------------------
        framesCounter++;

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 2)
                currentFrame = 0;

            tick_frame(&player, currentFrame);
        }
        //----------------------------------------------------------------------------------

        // Control player
        //----------------------------------------------------------------------------------
        tick_input(&player);
        //----------------------------------------------------------------------------------

        // Draw textures
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(background, screenWidth / 2 - background.width / 2, screenHeight / 2 - background.height / 2 - 40, WHITE);
        tick_animation(&player, WHITE);

        DrawText("FlappyINF", screenWidth - 250, screenHeight - 20, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);
    UnloadImage(spriteImage);

    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(textures[i]);
    }
    free(textures);

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}