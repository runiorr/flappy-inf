#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "constants.h"
#include "sprite.h"

typedef struct Player
{
	Texture2D *textures;
	Texture2D current;
	Vector2 position;
	Vector2 velocity;
	float jumpSpeed;
	bool alive;
	int spinDegree;
	float tiltAngle;
	Color color;
} Player;

void init_player(Player *p, Image playerImage);
void deload_player(Player *p);
// TODO: refatorar funcoes
void player_update_frame(Player *p, int currentFrame);
void player_update_position(Player *p);
void player_animation(Player *p);

#endif /* PLAYER_H */