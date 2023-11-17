#include "raylib.h"
#include "sprite.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H

typedef struct Obstacle
{
    Sprite texture;
    Vector2 position;
    bool standing;
    bool facingRight;
} Obstacle;

void tick_frame(Obstacle *p, float currentFrame);
void tick_input(Obstacle *p);
void tick_animation(Obstacle *p, Color color);

#endif /* OBSTACLE_H */