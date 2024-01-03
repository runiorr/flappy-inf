#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "raylib.h"

#include "constants.h"
#include "game.h"
#include "floor.h"
#include "background.h"
#include "player.h"
#include "pipe.h"

void restart_game(GameState *gameState, PipeManager *pipeManager)
{
    // TODO: Criar metodos para reiniciar os objetos do player e cano
    gameState->player->alive = true;
    gameState->player->position.y = PLAYER_START_POSITION_Y;
    gameState->player->velocity = (Vector2){0, 0};
    gameState->player->alive = true;
    gameState->player->spinDegree = 0;
    gameState->player->tiltAngle = 0;
    gameState->player->color.a = 255;

    for (int i = 0; i < MAX_PIPE_COUNT; i++)
    {
        Pipe pipe;
        _random_pipe(pipeManager, &pipe, i);
        pipeManager->pipes[i] = pipe;
    }
}

// TODO: add DEBUG INFO through args ---> int main( int argc, char **argv )
int main(void)
{
    // TODO : GetScreenWidth()
    // TODO : use const
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

    // TODO: receive external configuration
    Texture2D bottomPipeTexture = LoadTexture("resources/obstacles/bottomPipe.png");
    Texture2D topPipeTexture = LoadTexture("resources/obstacles/topPipe.png");
    PipeManager pipeManager;
    init_pipe_manager(&pipeManager, bottomPipeTexture, topPipeTexture);

    Image playerImage = LoadImage("resources/flappy/flappy_mov_red_big.png");
    Player player;
    init_player(&player, playerImage);

    // TODO: Use gameState everywhere (headers, methods)
    GameState game;
    init_game(&game, &floor, &player, &background);

    Sound deathSound = LoadSound("resources/audio/evil_laugh_edit.mp3");
    Sound backgroundMusic = LoadSound("resources/audio/bg_blackops.mp3");

    // Subscribe(EVENT_COLLISION, &HandleCollision);
    // Subscribe(EVENT_MOVEMENT, &HandleMovement);

    int framesCounter = 0;
    int currentFrame = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //  Reinicia o jogo se pressionar 'Q'
        if (IsKeyPressed(KEY_Q))
            restart_game(&game, &pipeManager);

        // TODO: Add deltaTime to decouple FPS from logic
        // States
        //----------------------------------------------------------------------------------
        // TODO: Configure states (Menu, score, difficulty)
        // game_update_state(&game);
        //----------------------------------------------------------------------------------

        // Sounds
        //----------------------------------------------------------------------------------
        // TODO: Coin, power ups
        game_sounds(&game, deathSound, backgroundMusic);
        //----------------------------------------------------------------------------------

        // Update texture frame
        //----------------------------------------------------------------------------------
        player_update_frame(&player, &framesCounter, &currentFrame);
        //----------------------------------------------------------------------------------

        // Update positions
        //----------------------------------------------------------------------------------
        background_movement(&game, &background);
        pipe_movement(&game, &pipeManager);
        floor_movement(&game, &floor);
        player_movement(&game, &player);
        // Publish(EVENT_MOVEMENT, GRAVITY, &game);
        //----------------------------------------------------------------------------------

        // Draw textures
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);

        background_animation(&background);
        pipe_animation(&pipeManager);
        floor_animation(&floor);
        player_animation(&player);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(bushesTexture);
    UnloadTexture(buildingsTexture);
    UnloadTexture(cloudsTexture);
    UnloadTexture(floorTexture);
    UnloadTexture(bottomPipeTexture);
    UnloadTexture(topPipeTexture);
    UnloadImage(playerImage);
    deload_player(&player);

    UnloadSound(backgroundMusic);
    UnloadSound(deathSound);

    CloseAudioDevice();
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}