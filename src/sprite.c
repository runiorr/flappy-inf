#include <stdio.h>
#include "../include/sprite.h"

Rectangle load_frame_rec(Texture2D texture, int frame_number)
{
    Rectangle frameRec = {0.0f, 0.0f, texture.width / frame_number, texture.height};
    return frameRec;
};
