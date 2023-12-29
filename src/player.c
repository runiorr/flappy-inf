#include "player.h"

void init_player(Player *p, Image spriteImage)
{
    Texture2D *textures = load_textures(spriteImage, 3);
    p->textures = textures;
    p->current = textures[0];
    p->position = (Vector2){(float)(SCREEN_WIDTH / 4), (float)(SCREEN_HEIGHT / 2)};
    p->velocity = (Vector2){0, 0};
    p->jumpSpeed = 8.0f;
    p->alive = true;
    p->spinDegree = 1;
    p->color = RAYWHITE;
}

void deload_player(Player *p)
{
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(p->textures[i]);
    }
    free(p->textures);
}

void player_update_frame(Player *p, int currentFrame)
{
    if (p->alive)
    {
        p->current = p->textures[currentFrame];
    }
}

void player_update_position(Player *p)
{
    if (p->alive == true)
    {
        if (IsKeyDown(KEY_SPACE))
        {
            p->velocity.y = -p->jumpSpeed;
        }
        p->velocity.y += 0.5f; // Gravity
        p->position.y += p->velocity.y;

        if (p->position.y >= (SCREEN_HEIGHT - FLOOR_HEIGHT))
        {
            p->alive = false;
        }
    }
}

void player_animation(Player *p)
{
    if (p->alive)
    {
        float tiltAngle = (p->velocity.y / 10.0f) * 30.0f;
        Rectangle source = {0, 0, p->current.width, p->current.height};
        Rectangle dest = {p->position.x, p->position.y, p->current.width, p->current.height};
        Vector2 origin = {p->current.width / 2, p->current.height / 2};
        DrawTexturePro(p->current, source, dest, origin, tiltAngle, p->color);
    }
    else
    {
        // Transparency
        if (p->color.a <= 5)
        {
            p->color.a = 0;
        }
        else
        {
            p->color.a -= 4;
        }
        // Spinning
        p->tiltAngle = ((p->velocity.y - p->spinDegree) / 10.0f) * 30.0f;
        if (p->tiltAngle <= -90 && p->tiltAngle > -180)
        {
            p->spinDegree += 6;
        }
        else if (p->tiltAngle <= -180 && p->tiltAngle > -270)
        {
            p->spinDegree += 12;
        }
        else if (p->tiltAngle <= -270)
        {
            p->spinDegree += 28;
        }

        Rectangle source = {0, 0, p->current.width, p->current.height};
        Rectangle dest = {p->position.x, p->position.y - p->spinDegree, p->current.width, p->current.height};
        Vector2 origin = {p->current.width / 2, p->current.height / 2};
        DrawTexturePro(p->current, source, dest, origin, p->tiltAngle, p->color);
        p->spinDegree++;
    }
}
