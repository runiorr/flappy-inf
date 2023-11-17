#include "raylib.h"
#include <stdbool.h>
#include "sprite.h"

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player
{
    Sprite idle;
    Sprite run;
    Vector2 position;
    bool standing;
    bool facingRight;
} Player;

void tick_frame(Player *p, float currentFrame);
void tick_input(Player *p);
void tick_animation(Player *p, Color color);

#endif /* PLAYER_H */