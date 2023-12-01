#include "raylib.h"
#include <stdlib.h>

#ifndef SPRITE_H
#define SPRITE_H

// typedef struct Sprite
// {
//     Texture2D texture;
//     int n_sprites;
//     Rectangle rec;
// } Sprite;

Rectangle load_frame_rec(Texture2D texture, int n_sprites);
Texture2D *load_textures(Image image, int n_sprites);

#endif /* SPRITE_H */
