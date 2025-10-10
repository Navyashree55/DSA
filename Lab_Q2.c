#include <stdio.h>
#include <string.h>

#define SIZE 10

char undoStack[SIZE][20];
char redoStack[SIZE][20];
int topUndo = -1, topRedo = -1;

// Push to stack
void push(char stack[SIZE][20], int *top, char op[]) {
    if (*top == SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    (*top)++;
    strcpy(stack[*top], op);
}

// Pop from stack
void pop(char stack[SIZE][20], int *top, char op[]) {
    if (*top == -1) {
        op[0] = '\0';
        return;
    }
    strcpy(op, stack[*top]);
    (*top)--;
}

// Perform new operation
void perform(char op[]) {
    push(undoStack, &topUndo, op);
    topRedo = -1; // clear redo stack when new op done
    printf("Performed operation: %s\n", op);
}

// Undo operation
void undo() {
    char op[20];
    pop(undoStack, &topUndo, op);

    if (strlen(op) == 0) {
        printf("Nothing to undo.\n");
        return;
    }

    push(redoStack, &topRedo, op);
    printf("Undone. ");
    if (topUndo >= 0)
        printf("Next Operation that can be undone is = %s\n", undoStack[topUndo]);
    else
        printf("No more operations to undo.\n");
}

// Redo operation
void redo() {
    char op[20];
    pop(redoStack, &topRedo, op);

    if (strlen(op) == 0) {
        printf("Nothing to redo.\n");
        return;
    }

    push(undoStack, &topUndo, op);
    printf("Redo completed. ");
    if (topRedo >= 0)
        printf("Next Operation that can be redone is = %s\n", redoStack[topRedo]);
    else
        printf("No more operations to redo.\n");
}

int main() {
    perform("op1");
    perform("op2");
    perform("op3");

    undo();
    undo();
    redo();
    perform("op4");
    undo();

    return 0;
}
