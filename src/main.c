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

    Image background_day_image = LoadImage("resources/background_day.png");
    Texture2D background_day = LoadTextureFromImage(background_day_image);
    UnloadImage(background_day_image);

    // Texture2D pipeTexture = LoadTexture("resources/obstaculo.png");

    Texture2D sprite = LoadTexture("resources/flappy_mov_red.png");
    Player player = {
        .sprite = (Sprite){sprite, 3, load_frame_rec(sprite, 3)},
        .image = LoadImage("resources/flappy_mov_red.png"),
        .current = LoadTexture("resources/flappy_red.png"),
        .position = {(float)screenWidth / 4, (float)screenHeight / 2},
        .velocity = {0, 0},
        .jumpSpeed = 8.0f};

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
    UnloadTexture(sprite);

    UnloadImage(player.image);
    UnloadTexture(player.current);

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}