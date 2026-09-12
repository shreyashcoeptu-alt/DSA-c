#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 2

typedef struct {
    int *data;
    int top;      // Index of topmost element (-1 when empty)
    int capacity; // Total allocated slots
} DynamicStack;

// Initialize stack with a small base capacity
bool initStack(DynamicStack *s) {
    s->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    if (!s->data) {
        perror("Failed to allocate initial memory");
        return false;
    }
    s->top = -1;
    s->capacity = INITIAL_CAPACITY;
    return true;
}

bool isEmpty(const DynamicStack *s) {
    return s->top == -1;
}

int size(const DynamicStack *s) {
    return s->top + 1;
}

// Internal helper: resize buffer safely using a temporary pointer
static bool resize(DynamicStack *s, int newCapacity) {
    int *temp = (int *)realloc(s->data, newCapacity * sizeof(int));
    if (!temp) {
        perror("Reallocation failed");
        return false;
    }
    s->data = temp;
    s->capacity = newCapacity;
    printf("[Resize] Capacity changed to %d\n", s->capacity);
    return true;
}

// Push: double capacity if buffer is full
bool push(DynamicStack *s, int val) {
    if (s->top + 1 == s->capacity) {
        if (!resize(s, s->capacity * 2)) {
            return false;
        }
    }
    s->data[++(s->top)] = val;
    return true;
}

// Pop: shrink capacity by half if usage drops to 1/4 (hysteresis)
bool pop(DynamicStack *s, int *poppedValue) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return false;
    }

    *poppedValue = s->data[(s->top)--];

    // Shrink if size <= 25% of capacity, but stay at/above INITIAL_CAPACITY
    if (s->top + 1 > 0 && s->top + 1 <= s->capacity / 4 && s->capacity / 2 >= INITIAL_CAPACITY) {
        resize(s, s->capacity / 2);
    }

    return true;
}

// Peek topmost element without removing
bool peek(const DynamicStack *s, int *topValue) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return false;
    }
    *topValue = s->data[s->top];
    return true;
}

void display(const DynamicStack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack (top -> bottom, size %d/%d): ", s->top + 1, s->capacity);
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

void freeStack(DynamicStack *s) {
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

int main(void) {
    DynamicStack s;
    if (!initStack(&s)) return 1;

    printf("--- Pushing Elements ---\n");
    for (int i = 10; i <= 60; i += 10) {
        push(&s, i);
        display(&s);
    }

    printf("\n--- Peeking ---\n");
    int val;
    if (peek(&s, &val)) {
        printf("Current top: %d\n", val);
    }

    printf("\n--- Popping Elements ---\n");
    while (!isEmpty(&s)) {
        pop(&s, &val);
        printf("Popped: %d | ", val);
        display(&s);
    }

    freeStack(&s);
    return 0;
}