#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* link;
} Node;

Node* create_node(int data, Node* link) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->link = link;
    return newnode;
}

void insert(Node** head, int data) {
    Node* newnode = create_node(data, *head);
    *head = newnode;
}

void print_list(Node* head) {
    Node* cur = head;
    while (cur != NULL) {
        printf("%d -> ", cur->data);
        cur = cur->link;
    }
    printf("NULL\n");
}
