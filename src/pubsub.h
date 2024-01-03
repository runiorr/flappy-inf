#ifndef PUBSUB_H
#define PUBSUB_H

// Define a function pointer type for the subscriber callback
typedef void (*SubscriberCallback)(const char *, void *);

// Function to subscribe to a specific event type with a callback function
void Subscribe(const char *eventType, SubscriberCallback callback);

// Function to publish an event with optional data
void Publish(const char *eventType, const char *eventData, void *additionalData);

// Event types
#define EVENT_COLLISION "Collision"
#define EVENT_KEY_PRESSED "KeyPressed"
#define EVENT_MOVEMENT "Movement"

// Messages
#define PIPE "Pipe"
#define GROUND "Ground"
#define SPACE "Space"
#define GRAVITY "Gravity"

// void HandleCollision(const char *eventData, void *g)
// void HandleMovement(const char *eventData, void *g)

#endif // PUBSUB_H