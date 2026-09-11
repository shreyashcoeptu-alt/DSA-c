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

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
        newNode->prev = head;
        return;
    }

    struct Node *temp = head;

    while (temp->next != head) {
        temp = temp->next;
    }

    newNode->prev = temp;
    newNode->next = head;

    temp->next = newNode;
    head->prev = newNode;
}

void insertAtIndex(int data, int index) {
    struct Node *newNode = createNode(data);

    // Empty list
    if (head == NULL) {
        if (index == 0) {
            head = newNode;
            newNode->next = head;
            newNode->prev = head;
        }
        return;
    }

    // Insert at beginning
    if (index == 0) {
        struct Node *last = head->prev;

        newNode->next = head;
        newNode->prev = last;

        last->next = newNode;
        head->prev = newNode;

        head = newNode;
        return;
    }

    // Find node at index
    struct Node *temp = head;

    for (int i = 0; i < index - 1; i++) {
        temp = temp->next;

        if (temp == head) {
            printf("Invalid index\n");
            free(newNode);
            return;
        }
    }

    newNode->next = temp->next;
    newNode->prev = temp;

    temp->next->prev = newNode;
    temp->next = newNode;
}

void deleteAtIndex(int index) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;

    // Delete first node
    if (index == 0) {

        // Only one node
        if (head->next == head) {
            free(head);
            head = NULL;
            return;
        }

        struct Node *last = head->prev;

        head = head->next;

        last->next = head;
        head->prev = last;

        free(temp);
        return;
    }

    // Find node to delete
    for (int i = 0; i < index; i++) {
        temp = temp->next;

        if (temp == head) {
            printf("Invalid index\n");
            return;
        }
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    free(temp);
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

    printf("Original list:\n");
    displaylist();

    insertAtIndex(50, 1);

    printf("After inserting 50 at index 1:\n");
    displaylist();

    deleteAtIndex(2);

    printf("After deleting index 2:\n");
    displaylist();

    return 0;
}