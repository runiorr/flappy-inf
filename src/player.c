#include "player.h"
#include "pubsub.h"

#define NUMBER_SPRITES 3
#define FRAMES_SPEED 6

typedef struct GameState
{
    float gravity;
    Player *player;
} GameState;

void init_player(Player *p, Image spriteImage)
{
    Texture2D *textures = load_textures(spriteImage, NUMBER_SPRITES);
    p->textures = textures;
    p->current = textures[0];
    p->position = (Vector2){PLAYER_START_POSITION_X, PLAYER_START_POSITION_Y};
    p->velocity = (Vector2){0, 0};
    p->jumpSpeed = 10.0f;
    p->alive = true;
    p->spinDegree = 0;
    p->tiltAngle = 0;
    p->color = WHITE;
}

void deload_player(Player *p)
{
    unload_textures(p->textures, NUMBER_SPRITES);
}

void player_update_frame(Player *p, int *framesCounter, int *currentFrame)
{
    if (p->alive)
    {
        (*framesCounter)++;
        if (*framesCounter >= (60 / FRAMES_SPEED))
        {
            *framesCounter = 0;
            (*currentFrame)++;
            if (*currentFrame > 2)
                *currentFrame = 0;

            p->current = p->textures[*currentFrame];
        }
    }
}

void player_movement(void *g, Player *p)
{
    GameState *gameState = (GameState *)g;

    if (p->alive)
    {
        if (IsKeyPressed(KEY_SPACE))
            _player_jump(p);

        // TODO: Change to pubsub if have more objects
        _player_gravity(p, gameState->gravity);
        _player_update_position(p);

        if (_player_hits_floor(p))
            _player_dead(gameState->player);
        // Publish(EVENT_COLLISION, GROUND, gameState);
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
            p->color.a -= 2.5;
        }
        // Spinning
        p->tiltAngle = ((p->velocity.y - p->spinDegree) / 10.0f) * 30.0f;
        if (p->tiltAngle <= -90 && p->tiltAngle > -180)
        {
            p->spinDegree += 2;
        }
        else if (p->tiltAngle <= -180 && p->tiltAngle > -270)
        {
            p->spinDegree += 6;
        }
        else if (p->tiltAngle <= -270 && p->tiltAngle > -360)
        {
            p->spinDegree += 9;
        }
        else if (p->tiltAngle <= -360)
        {
            p->spinDegree += 12;
        }

        Rectangle source = {0, 0, p->current.width, p->current.height};
        Rectangle dest = {p->position.x, p->position.y - p->spinDegree, p->current.width, p->current.height};
        Vector2 origin = {p->current.width / 2, p->current.height / 2};
        DrawTexturePro(p->current, source, dest, origin, p->tiltAngle, p->color);
        p->spinDegree++;
    }
}

void _player_update_position(Player *p)
{
    p->position.y += p->velocity.y;
}

void _player_jump(Player *p)
{
    p->velocity.y = -p->jumpSpeed;
}

void _player_gravity(Player *p, float gravity)
{
    p->velocity.y += gravity;
}

bool _player_hits_floor(Player *p)
{
    return (p->position.y >= (SCREEN_HEIGHT - FLOOR_HEIGHT));
}

void _player_dead(Player *p)
{
    p->alive = false;
}