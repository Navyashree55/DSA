#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};

struct Node* createNode(char c) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->ch = c;
    newNode->freq = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* queue[100];
int front = -1, rear = -1;

void enqueue(struct Node* node) {
    queue[++rear] = node;
}

struct Node* dequeue() {
    return queue[++front];
}

int isEmpty() {
    return front == rear;
}

int searchAndIncrement(struct Node* root, char c) {
    if (!root) return 0;
    if (root->ch == c) {
        root->freq++;
        return 1;
    }
    int found = searchAndIncrement(root->left, c);
    if (found) return 1;
    return searchAndIncrement(root->right, c);
}

struct Node* buildTree(char* str) {
    if (strlen(str) == 0) return NULL;
    struct Node* root = createNode(str[0]);
    enqueue(root);

    for (int i = 1; i < strlen(str); i++) {
        if (searchAndIncrement(root, str[i]))
            continue;

        struct Node* temp = queue[front + 1];
        if (!temp->left) {
            temp->left = createNode(str[i]);
            enqueue(temp->left);
        } else if (!temp->right) {
            temp->right = createNode(str[i]);
            enqueue(temp->right);
            dequeue(); // Move to next parent
        }
    }
    return root;
}

void levelOrder(struct Node* root) {
    front = rear = -1;
    enqueue(root);
    while (!isEmpty()) {
        struct Node* temp = dequeue();
        printf("(%c, %d) ", temp->ch, temp->freq);
        if (temp->left) enqueue(temp->left);
        if (temp->right) enqueue(temp->right);
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    struct Node* root = buildTree(str);

    printf("Level Order Traversal (char, freq):\n");
    levelOrder(root);

    return 0;
}
