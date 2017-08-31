#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdint.h>
#include <stdlib.h>

#define QUEUE_DEF(T)\
typedef struct _queue_item_##T {\
    struct _queue_item_##T* next;\
    T value;\
} queue_item_##T;\
typedef struct {\
    size_t len;\
    queue_item_##T* head;\
    queue_item_##T* tail;\
} queue_##T;\
queue_##T queue_new_##T();\
void queue_push_##T(queue_##T* queue, queue_item_##T item);\
void queue_pop_##T(queue_##T* queue);\
queue_item_##T* queue_peek_##T(queue_##T* queue);\
queue_item_##T queue_value_##T(T value);
    
#define QUEUE(T)\
\
queue_##T queue_new_##T() {\
    return (queue_##T) {\
        .head = NULL,\
        .tail = NULL,\
    };\
}\
\
void queue_push_##T(queue_##T* queue, queue_item_##T item) {\
    queue_item_##T* qi = malloc(sizeof(queue_item_##T));\
    *qi = item;\
    \
    if (queue->head == NULL || queue->tail == NULL) {\
        queue->head = qi;\
        queue->tail = qi;\
    } else {\
        queue->tail->next = qi;\
        queue->tail = qi;\
    }\
    \
    queue->len++;\
}\
\
void queue_pop_##T(queue_##T* queue) {\
    if (!queue->len) return;\
    \
    queue_item_##T* item = queue->head;\
    queue->head = queue->head->next;\
    free(item);\
    queue->len--;\
}\
\
queue_item_##T* queue_peek_##T(queue_##T* queue) {\
    return queue->head;\
}\
\
queue_item_##T queue_value_##T(T value) {\
    return (queue_item_##T) {\
        .next = NULL,\
        .value = value,\
    };\
}

#endif