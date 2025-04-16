#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* link;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void init(Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->link = NULL;
    if (q->rear) q->rear->link = node;
    else q->front = node;
    q->rear = node;
}

int dequeue(Queue* q) {
    if (!q->front) return -1;
    Node* tmp = q->front;
    int data = tmp->data;
    q->front = q->front->link;
    if (!q->front) q->rear = NULL;
    free(tmp);
    return data;
}