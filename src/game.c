#include "game.h"

void init_game(GameState *g, Floor *f, Player *p, Background *b, Score *s)
{
    g->gravity = GRAVITY;
    g->floor = f;
    g->player = p;
    g->background = b;
    g->score = s;
}
void game_update_state(GameState *g, float deltaTime)
{
    g->deltaTime = deltaTime;
}

void game_sounds(GameState *g, Sound deathSound, Sound backgroundMusic)
{
    // Background Music
    {
        if (!IsSoundPlaying(backgroundMusic))
        {
            SetSoundVolume(backgroundMusic, 0.05);
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
            SetSoundVolume(deathSound, 0.5);
            PlaySound(deathSound);
        }
    }
}