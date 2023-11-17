#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include "../include/player.h"
#include "../include/sprite.h"

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    InitWindow(screenWidth, screenHeight, "raylib [texture] example - sprite anim");

    Texture2D runTexture = LoadTexture("resources/flappy_mov.png");
    Texture2D idleTexture = LoadTexture("resources/flappy.png");

    Image background_day_image = LoadImage("resources/background_day.png");
    Texture2D background_day = LoadTextureFromImage(background_day_image);
    UnloadImage(background_day_image);

    // Texture2D pipeTexture = LoadTexture("resources/obstaculo.png");

    Player player = {
        .run = (Sprite){runTexture, 3, load_frame_rec(runTexture, 3)},
        .idle = (Sprite){idleTexture, 1, load_frame_rec(idleTexture, 1)},
        .position = {(float)screenWidth / 2, (float)screenHeight / 2},
        .standing = true,
        .facingRight = true};

    int framesCounter = 0;
    int framesSpeed = 8; // Number of spritesheet frames shown by second
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

            if (currentFrame > 5)
                currentFrame = 0;

            tick_frame(&player, currentFrame);
        }

        // Control player
        tick_input(&player);

        // Draw textures
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(background_day, screenWidth / 2 - background_day.width / 2, screenHeight / 2 - background_day.height / 2 - 40, WHITE);
        tick_animation(&player, WHITE);

        DrawText("FlappyINF", screenWidth - 250, screenHeight - 20, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background_day);
    UnloadTexture(runTexture);
    UnloadTexture(idleTexture);

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}