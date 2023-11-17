#include <stdio.h>
#include "../include/player.h"

#define AND &&
#define OR ||

void tick_frame(Player *p, float currentFrame)
{
    if (p->standing)
    {
        p->idle.rec.x = (float)currentFrame * (float)p->idle.texture.width / p->idle.n_sprites;
    }
    else
    {
        p->run.rec.x = (float)currentFrame * (float)p->run.texture.width / p->run.n_sprites;
    }
};

void tick_input(Player *p)
{
    if (IsKeyDown(KEY_RIGHT))
    {
        p->standing = false;
        p->facingRight = true;
        p->position.x += 2.0f;
    }

    else if (IsKeyDown(KEY_LEFT))
    {
        p->standing = false;
        p->facingRight = false;
        p->position.x -= 2.0f;
    }

    else if (IsKeyDown(KEY_UP))
    {
        p->standing = false;
        p->position.y -= 2.0f;
    }

    else if (IsKeyDown(KEY_DOWN))
    {
        p->standing = false;
        p->position.y += 2.0f;
    }

    else
    {
        p->standing = true;
    }
};

void tick_animation(Player *p, Color color)
{
    bool right_movement = p->facingRight == 1 AND(p->run.rec.width <= 0 OR p->idle.rec.width <= 0);
    bool left_movement = p->facingRight == 0 AND(p->run.rec.width >= 0 OR p->idle.rec.width >= 0);

    if (right_movement)
    {
        p->run.rec.width = -p->run.rec.width;
        p->idle.rec.width = -p->idle.rec.width;
    }

    if (left_movement)
    {
        p->run.rec.width = -p->run.rec.width;
        p->idle.rec.width = -p->idle.rec.width;
    }

    if (p->standing)
    {
        DrawTextureRec(p->idle.texture, p->idle.rec, p->position, color);
    }
    else
    {
        DrawTextureRec(p->run.texture, p->run.rec, p->position, color);
    }
};
