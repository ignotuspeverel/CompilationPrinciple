
#include "queue.h"


/*
   @brief queue manager creation, return an empty queue
*/
queue *queue_create() {
    queue *ptr_queue;
    ptr_queue = (queue *) malloc(sizeof(queue));
    if (NULL == ptr_queue) return NULL;
    ptr_queue->front = NULL;
    ptr_queue->rear = NULL;
    ptr_queue->size = 0;
    return ptr_queue;
}

/*
   @brief Initiate a queue which is already created
*/
void queue_init(queue *ptr_queue) {
    ptr_queue->front = NULL;
    ptr_queue->rear = NULL;
    ptr_queue->size = 0;
}

/*
   @brief Enqueue element at the end of queue
   @param queue pointer, element pointer, int for element size
*/
bool queue_push_back(queue *queue_ptr, void *element, int element_size) {
    q_node *node;
    node = (q_node *) malloc(sizeof(q_node));
    if (node == NULL) {
        printf("Allocation error for qNode");
        return false;
    }
    node->element = malloc((size_t) element_size);
    if (node->element == NULL) {
        printf("Allocation error for node->element");
       return false; 
    }
    memcpy(node->element, element, (size_t) element_size);
    node->element_size = element_size;

    node->next = node;
    if (queue_ptr->rear != NULL) {
        node->prev = queue_ptr->rear;
    } else {
        node->prev = node;
    }

    if (queue_ptr->rear == NULL) {
        queue_ptr->rear = node;
    } else {
        queue_ptr->rear->next = node;
    }
    queue_ptr->rear = node;
    if (queue_ptr->front == NULL) {
        queue_ptr->front = node;
    }

    queue_ptr->size += 1;
    return true;
}