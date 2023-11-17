#include "raylib.h"
#include <stdlib.h>

#ifndef SPRITE_H
#define SPRITE_H

typedef struct Sprite
{
    Texture2D texture;
    int n_sprites;
    Rectangle rec;
} Sprite;

Rectangle load_frame_rec(Texture2D texture, int frame_number);

#endif /* SPRITE_H */
