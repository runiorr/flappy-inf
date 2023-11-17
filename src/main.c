#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include "../include/player.h"
#include "../include/sprite.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    InitWindow(screenWidth, screenHeight, "raylib [texture] example - sprite anim");

    Texture2D runTexture = LoadTexture("resources/dummy/char_run_cycle.png");
    Texture2D idleTexture = LoadTexture("resources/dummy/char_idle.png");

    Player p = {
        .run = (Sprite){runTexture, 8, load_frame_rec(runTexture, 8)},
        .idle = (Sprite){idleTexture, 10, load_frame_rec(idleTexture, 10)},
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

            tick_frame(&p, currentFrame);
        }

        // Control player
        tick_input(&p);

        // Draw textures
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        tick_animation(&p, WHITE);
        DrawText("Testing player movement with animation", screenWidth - 250, screenHeight - 20, 10, GRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(runTexture);
    UnloadTexture(idleTexture);

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}