#ifndef QUEUE_H
#define QUEUE_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct queue_node {
    void *element;
    int element_size;
    struct queue_node *prev;
    struct queue_node *next;
} q_node;

typedef struct queue_manager
{
    int size;
    q_node *front;
    q_node *rear;

}queue;

/**
 * @brief queue manager creation, return an empty queue
 */
queue *queue_create();

/**
 * @brief queue manager creation, return an empty queue
 */
void queue_init(queue* queue_ptr);

/**
 * @brief Enqueue element at the end of queue
 * @param queue pointer, element pointer, int for element size
 */
bool queue_push_back(queue *queue_ptr, void *element, int element_size);

#endif