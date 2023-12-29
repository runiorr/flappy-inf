#include <stdio.h>
#include "player.h"

void tick_frame(Player *p, int currentFrame)
{
    p->current = p->textures[currentFrame];
}

void tick_input(Player *p)
{
    if (IsKeyDown(KEY_SPACE))
        p->velocity.y = -p->jumpSpeed;
    p->velocity.y += 0.5f; // Gravity
    p->position.y += p->velocity.y;
}

void tick_animation(Player *p, Color color)
{
    float tiltAngle = (p->velocity.y / 10.0f) * 30.0f;
    Rectangle source = {0, 0, p->current.width, p->current.height};
    Rectangle dest = {p->position.x, p->position.y, p->current.width, p->current.height};
    Vector2 origin = {p->current.width / 2, p->current.height / 2};
    DrawTexturePro(p->current, source, dest, origin, tiltAngle, color);
}
