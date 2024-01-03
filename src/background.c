#include "game.h"

void init_background(Background *b,
                     Texture2D bushesTexture,
                     Texture2D buildingsTexture,
                     Texture2D cloudsTexture)
{
    b->bushesTexture = bushesTexture;
    b->bushesScrollSpeed = 2.0f;
    b->bushesScrollOffset = 0.0f;
    b->buildingsTexture = buildingsTexture;
    b->buildingsScrollSpeed = 1.0f;
    b->buildingsScrollOffset = 0.0f;
    b->cloudsTexture = cloudsTexture;
    b->cloudsScrollSpeed = 0.5f;
    b->cloudsScrollOffset = 0.0f;
}

void background_movement(void *g, Background *b)
{
    GameState *game = (GameState *)g;

    // If the offset is greater than the texture width, reset it to create a looping effect
    if (game->player->alive)
    {
        b->bushesScrollOffset += b->bushesScrollSpeed;
        if (b->bushesScrollOffset == b->bushesTexture.width)
        {
            b->bushesScrollOffset = 0.0f;
        }

        b->buildingsScrollOffset += b->buildingsScrollSpeed;
        if (b->buildingsScrollOffset == b->buildingsTexture.width)
        {
            b->buildingsScrollOffset = 0.0f;
        }

        b->cloudsScrollOffset += b->cloudsScrollSpeed;
        if (b->cloudsScrollOffset == b->cloudsTexture.width)
        {
            b->cloudsScrollOffset = 0.0f;
        }
    }
}

void background_animation(Background *b)
{
    int cloudsHeight = 0;
    int buildingsHeight = 285;
    int bushesHeight = 380;

    DrawTextureEx(b->cloudsTexture, (Vector2){-b->cloudsScrollOffset, cloudsHeight}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(b->cloudsTexture, (Vector2){b->cloudsTexture.width - b->cloudsScrollOffset, cloudsHeight}, 0.0f, 1.0f, WHITE);

    DrawTextureEx(b->buildingsTexture, (Vector2){-b->buildingsScrollOffset, buildingsHeight}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(b->buildingsTexture, (Vector2){b->buildingsTexture.width - b->buildingsScrollOffset, buildingsHeight}, 0.0f, 1.0f, WHITE);

    DrawTextureEx(b->bushesTexture, (Vector2){-b->bushesScrollOffset, bushesHeight}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(b->bushesTexture, (Vector2){b->bushesTexture.width - b->bushesScrollOffset, bushesHeight}, 0.0f, 1.0f, WHITE);
}