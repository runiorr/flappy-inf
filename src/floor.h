#ifndef FLOOR_H
#define FLOOR_H

#include "raylib.h"
#include "constants.h"

typedef struct Floor
{
    Texture2D texture;
    float scrollSpeed;
    float scrollOffset;
} Floor;

void init_floor(Floor *f, Texture2D floorTexture);
void floor_draw(void *g, Floor *f);

#endif /* FLOOR_H */