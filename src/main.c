#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"

#include "constants.h"
#include "game.h"
#include "floor.h"
#include "background.h"
#include "player.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FlappyInf");
    InitAudioDevice();

    Texture2D bushesTexture = LoadTexture("resources/scenario/bushes.png");
    Texture2D buildingsTexture = LoadTexture("resources/scenario/buildings.png");
    Texture2D cloudsTexture = LoadTexture("resources/scenario/clouds.png");
    Background background;
    init_background(&background, bushesTexture, buildingsTexture, cloudsTexture);

    Texture2D floorTexture = LoadTexture("resources/obstacles/floor_complete.png");
    Floor floor;
    init_floor(&floor, floorTexture);

    Image playerImage = LoadImage("resources/flappy/flappy_mov_red_big.png");
    Player player;
    init_player(&player, playerImage);

    GameState game;
    init_game(&game, &floor, &player, &background);

    Sound deathSound = LoadSound("resources/audio/evil_laugh_edit.mp3");
    Sound backgroundMusic = LoadSound("resources/audio/bg_music.mp3");

    int framesCounter = 0;
    int framesSpeed = 6; // Number of spritesheet frames shown by second
    int currentFrame = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Sounds
        //----------------------------------------------------------------------------------
        game_sounds(&game, deathSound, backgroundMusic);
        //----------------------------------------------------------------------------------
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
        ClearBackground(WHITE);

        background_draw(&game, &background);
        player_animation(&player);
        floor_draw(&game, &floor);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(bushesTexture);
    UnloadTexture(buildingsTexture);
    UnloadTexture(cloudsTexture);
    UnloadTexture(floorTexture);
    UnloadImage(playerImage);
    deload_player(&player);

    UnloadSound(backgroundMusic);
    UnloadSound(deathSound);

    CloseAudioDevice();
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}