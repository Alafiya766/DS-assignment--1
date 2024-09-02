#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct CircularQueue {
    Node *front;
    Node *rear;
} CircularQueue;

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void initializeQueue(CircularQueue *q) {
    q->front = NULL;
    q->rear = NULL;
}

void enQueue(CircularQueue *q, int value) {
    Node *newNode = createNode(value);
    if (q->front == NULL) {
        // Queue is empty
        q->front = newNode;
        q->rear = newNode;
        newNode->next = q->front; 
    } else {
        // Queue is not empty
        newNode->next = q->front;
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int deQueue(CircularQueue *q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1; 
    }
    
    Node *temp = q->front;
    int value = temp->data;
    
    if (q->front == q->rear) {
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = q->front->next;
        q->rear->next = q->front;
    }
    
    free(temp);
    return value;
}
int getFront(CircularQueue *q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1; 
    }
    return q->front->data;
}
int getRear(CircularQueue *q) {
    if (q->rear == NULL) {
        printf("Queue is empty\n");
        return -1; 
    }
    return q->rear->data;
}
int main() {
    CircularQueue q;
    initializeQueue(&q);

    enQueue(&q, 10);
    enQueue(&q, 20);
    enQueue(&q, 30);

    printf("Front item: %d\n", getFront(&q));
    printf("Rear item: %d\n", getRear(&q));

    printf("Dequeued: %d\n", deQueue(&q));
    printf("Front item after dequeue: %d\n", getFront(&q));
    printf("Rear item after dequeue: %d\n", getRear(&q));

    return 0;
}
