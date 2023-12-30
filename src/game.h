#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "player.h"
#include "floor.h"
#include "background.h"

typedef struct GameState
{
    Floor *floor;
    Player *player;
    Background *background;
} GameState;

void init_game(GameState *g, Floor *f, Player *p, Background *b);

#endif /* GAMESTATE_H */