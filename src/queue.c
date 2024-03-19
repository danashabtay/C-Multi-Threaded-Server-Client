#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

// Struct to represent a single item in the queue
struct QueueItem
{
    int data;
    struct timeval arrival;
    QueueItem next;
};

// Struct to represent the queue itself
struct Queue
{
    QueueItem head;
    QueueItem tail;
    int size;     // Current size of the queue
    int capacity; // Maximum capacity of the queue
};

// Create a new queue with the specified capacity
Queue queue_create(int capacity)
{
    Queue queue = (Queue)malloc(sizeof(*queue));
    if (queue == NULL)
    {
        exit(EXIT_FAILURE);
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

int queue_size(Queue queue)
{
    return queue->size;
}

// Destroy the queue and free its memory
void queue_destroy(Queue queue)
{
    if(queue == NULL){
        return;
    }
    QueueItem current = queue->head;
    QueueItem next = NULL;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}

// Check if the queue is empty
bool queue_is_empty(Queue queue)
{
    if(queue == NULL){
        return 0;
    }
    return queue->size == 0;
}

// Check if the queue is full
bool queue_is_full(Queue queue)
{
    if(queue == NULL){
        return false;
    }
    if (queue->size == queue->capacity)
    {
        return true;
    }
    return false;
}

// Enqueue a new item into the queue
void queue_enqueue(Queue queue, int data, struct timeval arrival)
{
    if(queue == NULL){
        return;
    }
    if (queue_is_full(queue))
        return;

    QueueItem new_item = (QueueItem)malloc(sizeof(*new_item));
    if (new_item == NULL)
    {
        exit(EXIT_FAILURE);
    }
    new_item->data = data;
    new_item->arrival = arrival;
    new_item->next = NULL;

    if (queue_is_empty(queue))
    {
        queue->head = new_item;
        queue->tail = new_item;
    }
    else
    {
        queue->tail->next = new_item;
        queue->tail = new_item;
    }
    queue->size++;
}

// Dequeue an item from the queue
int queue_dequeue(Queue queue)
{
    if(queue == NULL){
        return -1;
    }
    if (queue_is_empty(queue))
        return -1;

    QueueItem temp = queue->head;
    int data = temp->data;
    queue->head = temp->next;
    free(temp);
    queue->size--;

    if (queue_is_empty(queue))
    {
        queue->tail = NULL;
    }

    return data;
}

// Print the contents of the queue (for debugging purposes)
void queue_print(Queue queue)
{
    if(queue == NULL){
        return;
    }
    printf("Queue: ");
    QueueItem current = queue->head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Return the arrival time of the head item in the queue
struct timeval queue_head_arrival_time(Queue queue)
{
    if(queue == NULL){
        struct timeval empty_time = {0};
        return empty_time;
    }
    if (queue_is_empty(queue))
    {
        struct timeval empty_time = {0};
        return empty_time;
    }
    return queue->head->arrival;
}

// Find the index of a value in the queue
int queue_find(Queue queue, int value)
{
    if(queue == NULL){
        return -1;
    }
    if (queue_is_empty(queue))
        return -1;
    int index = 0;
    QueueItem current = queue->head;
    while (current != NULL)
    {
        if (current->data == value)
        {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; // Value not found
}

// Dequeue an item from the queue at the specified index
int dequeue_index(Queue queue, int index)
{
    if(queue == NULL){
        return -1;
    }
    if (queue_is_empty(queue))
        return -1;
    if (index < 0 || index >= queue->size)
    {
        return -1; // Invalid index
    }
    if(index == 0){
        return queue_dequeue(queue);
    }

    QueueItem current = queue->head;
    QueueItem previous = NULL;
    int i = 0;
    while (i < index)
    {
        previous = current;
        current = current->next;
        i++;
    }
    int data = current->data;
    if (previous == NULL)
    {
        queue->head = current->next;
    }
    else
    {
        previous->next = current->next;
    }
    if (current == queue->tail)
    {
        queue->tail = previous;
    }
    free(current);
    queue->size--;

    return data;
}