#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

struct Queue {
    int head, tail, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity);

bool queueFull(struct Queue* queue);

bool queueEmpty(struct Queue* queue);

void push(struct Queue* queue, struct Process* process);

//struct Queue* pop(struct Queue* queue);
void pop(struct Queue* queue);

struct Queue* head(struct Queue* queue);

struct Queue* tail(struct Queue* queue);

void queueStatus(struct Queue* queue);

#endif // QUEUE_H