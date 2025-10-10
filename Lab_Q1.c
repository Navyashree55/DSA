#include <stdio.h>
#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

// Function to check if queue is full
int isFull() {
    return (front == 0 && rear == SIZE - 1) || (rear == (front - 1) % (SIZE - 1));
}

// Function to check if queue is empty
int isEmpty() {
    return (front == -1);
}

// Add call to queue
void enqueue(int call_id) {
    if (isFull()) {
        printf("Queue is full. Please wait.\n");
        return;
    }

    if (front == -1)
        front = rear = 0;
    else if (rear == SIZE - 1 && front != 0)
        rear = 0;
    else
        rear++;

    queue[rear] = call_id;
    printf("Call added: %d\n", call_id);
}

// Remove call from queue
void dequeue() {
    if (isEmpty()) {
        printf("No customers in queue.\n");
        return;
    }

    printf("Removed customer: %d\n", queue[front]);

    if (front == rear)
        front = rear = -1;
    else if (front == SIZE - 1)
        front = 0;
    else
        front++;
}

// Display customers in queue
void displayQueue() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Customers in queue: ");
    if (rear >= front) {
        for (int i = front; i <= rear; i++)
            printf("%d ", queue[i]);
    } else {
        for (int i = front; i < SIZE; i++)
            printf("%d ", queue[i]);
        for (int i = 0; i <= rear; i++)
            printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    enqueue(101);
    enqueue(102);
    enqueue(103);
    enqueue(104);
    enqueue(105);
    enqueue(106); // overflow

    displayQueue();

    dequeue();
    displayQueue();

    enqueue(106);
    enqueue(107);
    displayQueue();

    return 0;
}
