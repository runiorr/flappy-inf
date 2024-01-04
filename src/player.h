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

void player_update_frame(Player *p, int *framesCounter, int *currentFrame);

void player_movement(void *g, Player *p);

void player_animation(Player *p, float deltaTime);

void _player_update_position(Player *p, float deltaTime);

void _player_jump(Player *p);

void _player_gravity(Player *p, float gravity, float deltaTime);

bool _player_hits_floor(Player *p);

void _player_dead(Player *p);

#endif /* PLAYER_H */