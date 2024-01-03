#include <stdlib.h>
#include <string.h>
#include "pubsub.h"

// Maximum number of subscribers
#define MAX_SUBSCRIBERS 10

// Structure to represent a subscriber
typedef struct
{
    SubscriberCallback callback;
    char eventType[50];
} Subscriber;

// Array to store subscribers
static Subscriber subscribers[MAX_SUBSCRIBERS];
static int numSubscribers = 0;

// Function to subscribe to a specific event type with a callback function
void Subscribe(const char *eventType, SubscriberCallback callback)
{
    // Ensure we haven't reached the maximum number of subscribers
    if (numSubscribers < MAX_SUBSCRIBERS)
    {
        // Add the subscriber to the array
        subscribers[numSubscribers].callback = callback;
        strncpy(subscribers[numSubscribers].eventType, eventType, sizeof(subscribers[numSubscribers].eventType));
        numSubscribers++;
    }
}

// Function to publish an event with optional data
void Publish(const char *eventType, const char *eventData, void *additionalData)
{
    // Iterate through subscribers and notify those interested in the event type
    for (int i = 0; i < numSubscribers; ++i)
    {
        if (strcmp(subscribers[i].eventType, eventType) == 0)
        {
            // Call the subscriber's callback function with the event data and additional data
            subscribers[i].callback(eventData, additionalData);
        }
    }
}

// void HandleCollision(const char *eventData, void *g)
// {
//     GameState *gameState = (GameState *)g;

//     if (strcmp(eventData, PIPE) == 0)
//     {
//         printf("[%s] - [%s] -> Player has hit a pipe!\n", EVENT_COLLISION, PIPE);
//         _player_dead(gameState->player);
//     }
//     else if (strcmp(eventData, GROUND) == 0)
//     {
//         printf("[%s] - [%s] -> Player has hit the floor!\n", EVENT_COLLISION, GROUND);
//         _player_dead(gameState->player);
//     }
// }

// void HandleMovement(const char *eventData, void *g)
// {
// GameState *gameState = (GameState *)g;

// if (strcmp(eventData, GRAVITY) == 0)
// {
// printf("[%s] - [%s] -> Applying gravity to objects!\n", EVENT_MOVEMENT, GRAVITY);
// if (gameState->player->alive)
// _player_gravity(gameState->player, gameState->gravity);
// }
// }