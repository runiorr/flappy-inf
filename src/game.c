#include "game.h"

void init_game(GameState *g, Floor *f, Player *p, Background *b)
{
    g->floor = f;
    g->player = p;
    g->background = b;
}