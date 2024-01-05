#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "player.h"
#include "floor.h"
#include "background.h"
#include "score.h"

typedef struct GameState
{
    float gravity;
    float deltaTime;
    Floor *floor;
    Player *player;
    Background *background;
    Score *score;
} GameState;

void init_game(GameState *g, Floor *f, Player *p, Background *b, Score *s);

void game_update_state(GameState *g, float deltaTime);

void game_sounds(GameState *g, Sound deathSound, Sound backgroundMusic);

#endif /* GAMESTATE_H */