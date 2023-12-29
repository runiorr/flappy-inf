#include <stdio.h>
#include "sprite.h"

Rectangle load_frame_rec(Texture2D texture, int n_sprites)
{
    Rectangle frameRec = {0.0f, 0.0f, texture.width / n_sprites, texture.height};
    return frameRec;
}

Texture2D *load_textures(Image image, int n_sprites)
{
    Texture2D tmpTexture = LoadTextureFromImage(image);
    Rectangle frameRec = load_frame_rec(tmpTexture, n_sprites);
    Texture2D *textures = (Texture2D *)malloc(n_sprites * sizeof(Texture2D));

    for (int i = 0; i < n_sprites; i++)
    {
        frameRec.x = (float)(i + 1) * (tmpTexture.width / n_sprites);
        Image croppedImage = ImageFromImage(image, frameRec);
        Texture2D frameTexture = LoadTextureFromImage(croppedImage);
        UnloadImage(croppedImage);
        textures[i] = frameTexture;
    }
    UnloadTexture(tmpTexture);
    return textures;
}