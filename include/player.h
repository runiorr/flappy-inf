#include "raylib.h"
#include <stdbool.h>
#include "sprite.h"

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player
{
    Sprite sprite;
    Image image;
    Texture2D current;
    Vector2 position;
    Vector2 velocity;
    float jumpSpeed;
} Player;

void tick_frame(Player *p, float currentFrame);
void tick_input(Player *p);
void tick_animation(Player *p, Color color);

#endif /* PLAYER_H */