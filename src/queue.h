#ifndef QUEUE_H
#define QUEUE_H

#include <sys/time.h>
#include <stdbool.h>

typedef struct Queue *Queue;
typedef struct QueueItem *QueueItem;

// Function prototypes
Queue queue_create(int capacity);
int queue_size(Queue queue);
void queue_destroy(Queue queue);
bool queue_is_empty(Queue queue);
bool queue_is_full(Queue queue);
void queue_enqueue(Queue queue, int data, struct timeval arrival);
int queue_dequeue(Queue queue);
void queue_print(Queue queue);
struct timeval queue_head_arrival_time(Queue queue);
int queue_find(Queue queue, int value);
int dequeue_index(Queue queue, int index);

#endif /* QUEUE_H */