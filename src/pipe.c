#include "pipe.h"
#include <stdio.h>

void init_pipe_manager(PipeManager *pipeManager, Texture2D bottomPipeTexture, Texture2D topPipeTexture)
{
	const int GAP = 200;
	const int OBSTACLE_VELOCITY = 4;

	pipeManager->bottomPipeTexture = bottomPipeTexture;
	pipeManager->topPipeTexture = topPipeTexture;
	pipeManager->offset = 300;

	pipeManager->gap = GAP;
	// pipeManager->incGap = inc_gap;
	// pipeManager->difMaxHeight = dif_max_height;
	// pipeManager->incDifMaxHeight = inc_dif_max_height;
	pipeManager->obstacleVelocity = OBSTACLE_VELOCITY;
	// pipeManager->incObstacleVelocity = inc_obstacle_velocity;

	for (int i = 0; i < MAX_PIPE_COUNT; i++)
	{
		pipeManager->pipes[i] = _generate_pipe(pipeManager, i);
	}
}

Pipe _generate_pipe(PipeManager *pipeManager, int i)
{
	float topPipeHeight = GetRandomValue(0, GetScreenHeight() / 2);

	Pipe pipe;
	pipe.topPipeStart = (0 - GetScreenHeight()) + topPipeHeight;
	pipe.bottomPipeStart = topPipeHeight + pipeManager->gap;
	pipe.x = (GetScreenWidth() / 2) + (pipeManager->offset * i);
	pipe.jumped = false;
	pipe.visible = true;

	return pipe;
}

void pipe_update_position(void *g, PipeManager *pipeManager)
{
	GameState *game = (GameState *)g;

	// TODO: PARAR AO MORRER
	if (game->player->alive)
	{
		for (int i = 0; i < MAX_PIPE_COUNT; i++)
		{
			// Atualizar posição dos tubos
			pipeManager->pipes[i].x -= pipeManager->obstacleVelocity;

			// Verifique se o tubo foi passado para gerar novo
			if (pipeManager->pipes[i].x <= 0)
			{
				pipeManager->pipes[i].x = GetScreenWidth() + (2 * pipeManager->offset);
			}
		}
	}
}

void pipe_draw(PipeManager *pipeManager)
{
	for (int i = 0; i < MAX_PIPE_COUNT; i++)
	{
		Pipe pipe = pipeManager->pipes[i];
		Vector2 topPipe = (Vector2){pipe.x, pipe.topPipeStart};
		Vector2 bottomPipe = (Vector2){pipe.x, pipe.bottomPipeStart};

		DrawTextureEx(pipeManager->topPipeTexture, topPipe, 0.0, 1.0, WHITE);
		DrawTextureEx(pipeManager->bottomPipeTexture, bottomPipe, 0.0, 1.0, WHITE);
	}
}

// bool CheckCollision(void)
// {
//     // TODO: Implemente a lógica de detecção de colisão aqui
// }
