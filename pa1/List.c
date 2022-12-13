#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

//private Node type
typedef struct NodeObj* Node;

//private NodeObj type
typedef struct NodeObj{
    int data;
    Node next;
    Node prev;
} NodeObj;

//private StackObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

//Node Constructor
Node newNode(int node_data){
    Node N = malloc(sizeof(NodeObj));
    N->data = node_data;
    N->next = NULL;
    return(N);
}

//Node Destructor
void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

//List Constructor
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    L->front = NULL;
    L->back = NULL;
    return(L);
}

//List Destructor
void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        if(length(*pL) != 0) {clear(*pL);}
        free(*pL);
        *pL = NULL;
    }
}

int length(List L) {
    return L->length;
}

int index(List L) {
    return L->index;
}

int front(List L) {
    if(L->length > 0) {
        return (L->front)->data;
    }
    //if the length is less than 0, return EXIT_FAILURE (will never happen)
    printf("List Error: Calling front() on NULL list reference\n");
    return(EXIT_FAILURE);
}

int back(List L){
    if(L->length > 0) {
        return (L->back)->data;
    }
    //if the length is less than 0
    return -1;
}

bool equals(List A, List B) {
    if(A == NULL || B == NULL){
        printf("List Error: Calling equals() on NULL List reference(s)\n");
        exit(EXIT_FAILURE);
    }

    bool eq = A->length == B->length;
    Node N, M;
    N = A->front;
    M = B->front;

    while(eq && N != NULL) {
        eq = N->data == M->data;
        N = N->next;
        M = M->next;
    }
    return eq;
}

void clear(List L) {
    if(L == NULL) {
        printf("List Error: Calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length > 0) {
        Node M = L->front;
        Node M_next = NULL;
        for(int i = 0; i < L->length; i++){
            M_next = M->next;
            freeNode(&M);
            M = M_next;
        }
        L->front = NULL;
        L->back = NULL;
        L->index = -1;
        L->length = 0;
        L->index = 0;
    }
}

void set(List L, int x) {
    if(L == NULL) {
        printf("List Error: Calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: List length = 0 while calling set()\n");
        exit(EXIT_FAILURE);
    }
    (L->cursor)->data = x;
}

void moveFront(List L) {
    if(L == NULL) {
        printf("List Error: Calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling moveFront() with empty List reference\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->front;
}

void moveBack(List L) {
    if(L == NULL) {
        printf("List Error: Calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling moveBack() with empty List reference\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->back;
}

void movePrev(List L) {
    if(L == NULL) {
        printf("List Error: Calling movePrev() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling movePrev() with empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor != NULL) {
        L->cursor = (L->cursor)->prev;
    }
}

void moveNext(List L) {
    if(L == NULL) {
        printf("List Error: Calling moveNext() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling moveNext() with empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor != NULL) {
        L->cursor = (L->cursor)->next;
    }
}

void prepend(List L, int x) {
    if(L == NULL) {
        printf("List Error: Calling prepend on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if(L->length == 0) {
        L->back = N;
        L->front = N;
    }
    if(L->length > 0) {
        Node temp = L->front;
        L->front = N;
        N->next = temp;
        temp->prev = N;
    }
    L->length++;
}

void append(List L, int x) {
    if(L == NULL) {
        printf("List Error: Calling prepend on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if(L->length == 0) {
        L->back = N;
        L->front = N;
    }
    if(L->length > 0) {
        Node temp = L->back;
        L->back = N;
        N->prev = temp;
        temp->next = N;
    }
    L->length++;
}

void insertBefore(List L, int x) {
    if(L == NULL) {
        printf("List Error: Calling insertBefore() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling insertBefore() with empty list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0) {
        printf("List Error: Calling insertBefore() with invalid cursor index (-1)\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    Node prev = (L->cursor)->prev;
    prev->next = N;
    (L->cursor)->prev = N;
    N->prev = prev;
    N->next = (L->cursor);
    L->length++;
}