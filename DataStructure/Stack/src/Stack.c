#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data ;
    struct Node* next ;
} Node;

typedef struct {
    Node* top;
} Stack;

void init(Stack* s){
    s->top = NULL ;
}

int is_empty(Stack* s){
    return s->top = NULL;
}

// 가장 최근에 push된 node가 top
void push(Stack* s , int item){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = item;
    new_node->next = s->top;
    s->top = new_node;
}

int pop(Stack* s){
    if(is_empty(s)){
        printf("Stack is empty\n");
        exit(1);
    }

    Node* temp = s->top;
    int value = temp->data;
    s->top = temp->next;
    free(temp);
    return value;
}

int peek(Stack* s){
    if(is_empty(s)){
        printf("Stack is empty\n");
        exit(1);
    }
    return s->top->data;
}

int size(Stack* s){
    int count = 0 ;
    Node* current = s->top;
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}