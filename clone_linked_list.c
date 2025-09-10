#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* random;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->random = NULL;
    return newNode;
}

struct Node* cloneList(struct Node* head) {
    if (!head) return NULL;

    struct Node* curr = head;
    while (curr) {
        struct Node* temp = createNode(curr->data);
        temp->next = curr->next;
        curr->next = temp;
        curr = temp->next;
    }

    curr = head;
    while (curr) {
        if (curr->random)
            curr->next->random = curr->random->next;
        curr = curr->next->next;
    }

    struct Node* cloneHead = head->next;
    struct Node* clone = cloneHead;
    curr = head;

    while (curr) {
        curr->next = clone->next;
        if (clone->next) clone->next = clone->next->next;
        curr = curr->next;
        clone = clone->next;
    }

    return cloneHead;
}

void printList(struct Node* head) {
    while (head) {
        printf("Data: %d", head->data);
        if (head->random)
            printf(", Random: %d", head->random->data);
        printf("\n");
        head = head->next;
    }
}

int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);

    head->random = head->next->next;
    head->next->random = head;
    head->next->next->random = head->next;

    printf("Original List:\n");
    printList(head);

    struct Node* cloned = cloneList(head);

    printf("\nCloned List:\n");
    printList(cloned);

    return 0;
}