#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

void insertEnd(int data) {
    struct Node *newNode = createNode(data);

    // Empty list
    if (head == NULL) {
        head = newNode;
        newNode->next = head;
        newNode->prev = head;
        return;
    }

    // Find last node
    struct Node *temp = head;

    while (temp->next != head) {
        temp = temp->next;
    }

    // Insert at end
    newNode->prev = temp;
    newNode->next = head;

    temp->next = newNode;
    head->prev = newNode;
}

void displaylist() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;

    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(back to head)\n");
}

int main() {

    insertEnd(12);
    insertEnd(15);
    insertEnd(20);

    displaylist();

    return 0;
}