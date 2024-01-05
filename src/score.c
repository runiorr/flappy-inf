#include "score.h"

void init_score(Score *score)
{
    score->value = 0;
    score->position = (Vector2){10, 10};
    score->font = GetFontDefault();
    score->color = WHITE;
}

void score_update(Score *score)
{
    score->value += SCORE_VALUE;
}

void score_animation(Score *score)
{
    DrawText(TextFormat("%05d", score->value), score->position.x, score->position.y, 50, score->color);
}
