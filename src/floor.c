#include "game.h"

void init_floor(Floor *f, Texture2D floorTexture)
{
    f->texture = floorTexture;
    f->scrollSpeed = 5.0f;
    f->scrollOffset = 0.0f;
}

void floor_movement(void *g, Floor *f)
{
    GameState *game = (GameState *)g;
    if (game->player->alive)
    {
        f->scrollOffset += f->scrollSpeed;
        // If the offset is greater than the texture width, reset it to create a looping effect
        if (f->scrollOffset >= f->texture.width)
        {
            f->scrollOffset = 0.0f;
        }
    }
}

void floor_animation(Floor *f)
{
    DrawTextureEx(f->texture, (Vector2){-f->scrollOffset, SCREEN_HEIGHT - f->texture.height}, 0.0f, 1.0f, WHITE);
    DrawTextureEx(f->texture, (Vector2){f->texture.width - f->scrollOffset, SCREEN_HEIGHT - f->texture.height}, 0.0f, 1.0f, WHITE);
}