#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "RoundRobin.h"
#include "Queue.h"

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->head = queue->size = 0;
    queue->tail = capacity - 1;
    queue->array = (struct Queue*)malloc(queue->capacity * sizeof(struct Queue));

    return queue;
}

bool queueFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

bool queueEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void push(struct Queue* queue, struct Process* process) {
    if (queueFull(queue)) {
        return;
    }

    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->array[queue->tail] = process;
    queue->size += 1;
}

void pop(struct Queue* queue) {
    if (queueEmpty(queue)) {
        return;
    }

    queue->head = (queue->head + 1) % queue->capacity;
    queue->size -= 1;
}

struct Queue* head(struct Queue* queue) {
    if (queueEmpty(queue)) {
        return INT_MIN;
    }

    return queue->array[queue->head];
}

struct Queue* tail(struct Queue* queue) {
    if (queueEmpty(queue)) {
        return INT_MIN;
    }

    return queue->array[queue->tail];
}

void queueStatus(struct Queue* queue) {
    for (int i = 0; i < queue->size; i++) {
        printf("Queue index %d contains value %d\n", i, queue->array[i]);
    }
}