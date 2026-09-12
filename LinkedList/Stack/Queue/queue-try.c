#include <stdio.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
    int items[MAX];
    int front;
    int rear;
} CircularQueue;

void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

bool isEmpty(CircularQueue *q) {
    return q->front == -1;
}

void enqueue(CircularQueue *q, int val) {
    if (isFull(q)) {
        printf("Queue Full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = val;
}

int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Empty!\n");
        return -1;
    }
    int val = q->items[q->front];
    if (q->front == q->rear) { // Last element removed
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return val;
}