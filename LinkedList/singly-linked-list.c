#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};
struct Node *head = NULL;
struct Node *createNode(int data){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
};

void displayNodes(struct Node *head){
    struct Node *temp = head;
    while(temp!=NULL){
        printf("%d ->", temp->data);
        temp = temp->next;
    }
    printf("NULL");
}

void insertAtEnd(int data){
    struct Node *newNode = createNode(data);
    if(head == NULL){
        head = newNode;
        return;
    }
    struct Node *temp = head;
    while(temp->next != NULL){
        temp = temp->next; 
    }
    temp->next = newNode;

}


int main(){

    insertAtEnd(10);
    insertAtEnd(20);
    insertAtEnd(30);

    displayNodes(head);

    return 0;

}