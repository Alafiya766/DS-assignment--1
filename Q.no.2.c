#include <stdio.h>
#include <stdlib.h>

// Node structure for the circular queue
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Circular Queue structure
typedef struct CircularQueue {
    Node *front;
    Node *rear;
} CircularQueue;

// Function to create a new node
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

// Initialize the circular queue
void initializeQueue(CircularQueue *q) {
    q->front = NULL;
    q->rear = NULL;
}

// Enqueue operation
void enQueue(CircularQueue *q, int value) {
    Node *newNode = createNode(value);
    if (q->front == NULL) {
        // Queue is empty
        q->front = newNode;
        q->rear = newNode;
        newNode->next = q->front; // Point to itself
    } else {
        // Queue is not empty
        newNode->next = q->front;
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Dequeue operation
int deQueue(CircularQueue *q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1; // Indicates an error
    }
    
    Node *temp = q->front;
    int value = temp->data;
    
    if (q->front == q->rear) {
        // Only one node in the queue
        q->front = NULL;
        q->rear = NULL;
    } else {
        // More than one node in the queue
        q->front = q->front->next;
        q->rear->next = q->front;
    }
    
    free(temp);
    return value;
}

// Get front item
int getFront(CircularQueue *q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1; // Indicates an error
    }
    return q->front->data;
}

// Get rear item
int getRear(CircularQueue *q) {
    if (q->rear == NULL) {
        printf("Queue is empty\n");
        return -1; // Indicates an error
    }
    return q->rear->data;
}

// Main function for testing the Circular Queue
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
