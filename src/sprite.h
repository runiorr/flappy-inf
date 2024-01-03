#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

Rectangle load_frame_rec(Texture2D texture, int n_sprites);

Texture2D *load_textures(Image image, int n_sprites);

void unload_textures(Texture2D *textures, int n_sprites);

#endif /* SPRITE_H */
