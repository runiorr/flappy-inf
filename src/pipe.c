#include <stdio.h>
#include "pipe.h"
#include "pubsub.h"

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
		Pipe pipe;
		_random_pipe(pipeManager, &pipe, i);
		pipeManager->pipes[i] = pipe;
	}
}

void _random_pipe(PipeManager *pipeManager, Pipe *pipe, int i)
{
	float topPipeHeight = GetRandomValue(0, GetScreenHeight() / 2);
	pipe->topPipeStart = (0 - GetScreenHeight()) + topPipeHeight;
	pipe->bottomPipeStart = topPipeHeight + pipeManager->gap;
	pipe->x = (GetScreenWidth() / 2) + (pipeManager->offset * i);
	pipe->jumped = false;
	pipe->visible = true;
}

void pipe_movement(void *g, PipeManager *pipeManager)
{
	GameState *gameState = (GameState *)g;

	// TODO: PARAR AO MORRER
	if (gameState->player->alive)
	{
		for (int i = 0; i < MAX_PIPE_COUNT; i++)
		{
			// Atualizar posição dos tubos
			pipeManager->pipes[i].x -= pipeManager->obstacleVelocity;

			// TODO: Adicionar animacao para ele sumindo
			// Verifique se o tubo foi passado para gerar novo
			// Quando o cano chegar no eixo X = 0, ele ira se tornar o ultimo cano da lista
			// E um novo cano sera gerado em sua posicao da lista, com novos valores
			if (pipeManager->pipes[i].x == 0)
			{
				pipeManager->pipes[LAST_PIPE].bottomPipeStart = pipeManager->pipes[i].bottomPipeStart;
				pipeManager->pipes[LAST_PIPE].topPipeStart = pipeManager->pipes[i].topPipeStart;
				pipeManager->pipes[LAST_PIPE].x = pipeManager->pipes[i].x;
				_random_pipe(pipeManager, &pipeManager->pipes[i], 0);
				pipeManager->pipes[i].x = GetScreenWidth() + (2 * pipeManager->offset);
			}

			// Verifica se acertou cano
			if (_pipe_collision(gameState, pipeManager, pipeManager->pipes[i]))
			{
				// Publish(EVENT_COLLISION, PIPE, gameState);
				_player_dead(gameState->player);
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

bool _pipe_collision(GameState *gameState, PipeManager *pipeManager, Pipe pipe)
{
	Player *p = gameState->player;
	// Menos 20%
	int playerWidth = p->current.width - (p->current.width / 10 * 2);
	int playerHeight = p->current.height - (p->current.height / 10 * 2);

	// Offset para erro da posicao X
	int pipeX = pipe.x + 40;
	// Menos 20%
	int pipeWidth = pipeManager->topPipeTexture.width - (pipeManager->topPipeTexture.width / 10 * 2);

	int topPipeY = pipe.topPipeStart + 20;
	int topPipeHeight = pipeManager->topPipeTexture.height;

	int bottomPipeY = pipe.bottomPipeStart + 30;
	int bottomPipeHeight = pipeManager->bottomPipeTexture.height;

	Rectangle player = {p->position.x, p->position.y, playerWidth, playerHeight};
	Rectangle bottomPipe = {pipeX, bottomPipeY, pipeWidth, bottomPipeHeight};
	Rectangle topPipe = {pipeX, topPipeY, pipeWidth, topPipeHeight};

	return (CheckCollisionRecs(bottomPipe, player) || CheckCollisionRecs(topPipe, player));
}