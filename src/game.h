#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "player.h"
#include "floor.h"
#include "background.h"

typedef struct GameState
{
    float gravity;
    Floor *floor;
    Player *player;
    Background *background;
} GameState;

void init_game(GameState *g, Floor *f, Player *p, Background *b);

// void game_update_state(GameState *g);

void game_sounds(GameState *g, Sound deathSound, Sound backgroundMusic);

#endif /* GAMESTATE_H */