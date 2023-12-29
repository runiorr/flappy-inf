#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"

#include "player.h"
#include "sprite.h"
#include "floor.h"
#include "constants.h"

int main(void)
{
    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [texture] example - sprite anim");

    // TODO: Create background struct
    // TODO: Add Parallax (bushes, buildings)
    Texture2D background = LoadTexture("resources/scenario/background_day_full.png");

    Texture2D floorTexture = LoadTexture("resources/obstacles/floor_complete.png");

    Image spriteImage = LoadImage("resources/flappy/flappy_mov_red_big.png");
    Player player;
    init_player(&player, spriteImage);

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
            player_update_frame(&player, currentFrame);
        }
        //----------------------------------------------------------------------------------

        // Control player
        //----------------------------------------------------------------------------------
        player_update_position(&player);
        //----------------------------------------------------------------------------------

        // Draw textures
        //----------------------------------------------------------------------------------
        BeginDrawing();
        // Background
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, -60, RAYWHITE);
        // Player
        player_animation(&player);
        floor_draw(floorTexture);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadImage(spriteImage);
    deload_player(&player);

    UnloadTexture(background);
    UnloadTexture(floorTexture);

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}