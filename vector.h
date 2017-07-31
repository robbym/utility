#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdlib.h>
#include <string.h>
#define VECTOR(T)\
typedef struct {\
    size_t cap;\
    size_t len;\
    T* data;\
} vector_##T;\
\
vector_##T vector_init_##T() {\
    void* data = malloc(sizeof(T) * (1 << 4));\
    return (vector_##T) {\
        .cap = (1 << 4),\
        .len = 0,\
        .data = data,\
    };\
}\
\
void vector_free_##T(vector_##T* self) {\
    self->cap = 0;\
    self->len = 0;\
    free(self->data);\
}\
\
void vector_push_##T(vector_##T* self, T val) {\
    if (self->len >= self->cap) {\
        self->cap <<= 1;\
        self->data = realloc(self->data, sizeof(T) * self->cap);\
    }\
\
    self->data[self->len] = val;\
    self->len++;\
}\
\
T vector_pop_##T(vector_##T* self) {\
    if (self->len) {\
        T val = self->data[self->len - 1];\
        self->len--;\
        return val;\
    }\
}\
\
void vector_clear_##T(vector_##T* self) {\
    self->len = 0;\
}\
\
void vector_shrink_##T(vector_##T* self) {\
    while ( (self->cap >> 1) > self->len && self->cap > (1 << 4) ) self->cap >>= 1;\
    self->data = realloc(self->data, sizeof(T) * self->cap);\
}\
\
void vector_insert_##T(vector_##T* self, size_t idx, T val) {\
    if (idx < self->len) {\
        if (self->len >= self->cap) {\
            self->cap <<= 1;\
            self->data = realloc(self->data, sizeof(T) * self->cap);\
        }\
\
        memmove(&self->data[idx+1], &self->data[idx], sizeof(T) * (self->len - idx));\
        self->data[idx] = val;\
        self->len++;\
    }\
}\
void vector_remove_##T(vector_##T* self, size_t idx) {\
    if (idx < self->len) {\
        memmove(&self->data[idx], &self->data[idx+1], sizeof(T) * (self->len - idx - 1));\
        self->len--;\
    }\
}\
\
static T* partition(T* left, T* right, int (*compare) (T*, T*)) {\
    T* pivot = left;\
    left--;\
    right++;\
    for (;;) {\
        do {left++;} while (compare(left, pivot) < 0);\
        do {right--;} while (compare(right, pivot) > 0);\
        if (left >= right) return right;\
        T swap = *left;\
        *left = *right;\
        *right = swap;\
    }\
}\
\
static void quicksort(T* left, T* right, int (*compare) (T*, T*)) {\
    if (left < right) {\
        T* p = partition(left, right, compare);\
        quicksort(left, p, compare);\
        quicksort(p+1, right, compare);\
    }\
}\
\
void vector_sort_##T(vector_##T* self, int (*compare) (T*, T*)) {\
    quicksort(&self->data[0], &self->data[self->len - 1], compare);\
}\

#endif