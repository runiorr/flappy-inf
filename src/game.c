#include "game.h"

void init_game(GameState *g, Floor *f, Player *p, Background *b)
{
    g->floor = f;
    g->player = p;
    g->background = b;
}

void game_sounds(GameState *g, Sound deathSound, Sound backgroundMusic)
{
    // Background Music
    {
        if (!IsSoundPlaying(backgroundMusic))
        {
            SetSoundVolume(backgroundMusic, 0.1);
            PlaySound(backgroundMusic);
        }
    }

    // Death sound
    bool visible = g->player->color.a != 0;
    bool dead = !g->player->alive;
    if (dead && visible)
    {
        if (!IsSoundPlaying(deathSound))
        {
            PlaySound(deathSound);
        }
    }
}