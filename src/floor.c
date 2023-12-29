#include "floor.h"

void floor_draw(Texture2D floorTexture)
{
    DrawTexture(floorTexture, 0, SCREEN_HEIGHT - floorTexture.height, WHITE);
}