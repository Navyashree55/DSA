#include <stdio.h>
#include <stdlib.h>

struct Node {
    int songID;
    struct Node* next;
};

struct Node* createNode(int songID) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->songID = songID;
    newNode->next = NULL;
    return newNode;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d", head->songID);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

struct Node* reversePlaylistSegment(struct Node* head, int m, int n) {
    if (!head || m == n) return head;

    struct Node dummy;
    dummy.next = head;
    struct Node* prev = &dummy;

    for (int i = 1; i < m; i++)
        prev = prev->next;

    struct Node* start = prev->next;
    struct Node* then = start->next;

    for (int i = 0; i < n - m; i++) {
        start->next = then->next;
        then->next = prev->next;
        prev->next = then;
        then = start->next;
    }

    return dummy.next;
}

int main() {
    int n, m, k;
    printf("Enter number of songs: ");
    scanf("%d", &n);

    struct Node* head = NULL;
    struct Node* tail = NULL;
    for (int i = 0; i < n; i++) {
        int id;
        printf("Enter song ID %d: ", i + 1);
        scanf("%d", &id);
        struct Node* newNode = createNode(id);
        if (head == NULL)
            head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    printf("Enter m and n (positions to reverse): ");
    scanf("%d %d", &m, &k);

    printf("Original Playlist: ");
    printList(head);

    head = reversePlaylistSegment(head, m, k);

    printf("Modified Playlist: ");
    printList(head);

    return 0;
}
