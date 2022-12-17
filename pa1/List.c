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
    if(L->cursor != NULL) {
        return L->index;
    }
    else {
        return -1;
    }
}

int front(List L) {
    if(L == NULL) {
        printf("List Error: Calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling front() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->front)->data;
}

int back(List L){
    if(L == NULL) {
        printf("List Error: Calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling back() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->back)->data;
}

int get(List L) { 
    if(L == NULL) {
        printf("List Error: Calling get() on a NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling get() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0) {
        printf("List Error: Calling get() with an invalid index\n");
        exit(EXIT_FAILURE);
    }
    return (L->cursor)->data; 
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
        L->cursor = NULL;
        L->index = -1;
        L->length = 0;
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
    if(L->index < 0) {
        printf("List Error: Calling set() with invalid index value (-1)\n");
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
    L->index = 0;
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
    L->index = L->length - 1;
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
    if(L->cursor == NULL) {
        return;
    }
    else if(L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
    }
    else {
        L->cursor = (L->cursor)->prev;
        L->index--;
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
    if(L->cursor == NULL) {
        return;
    }
    else if(L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }
    else {
        L->cursor = (L->cursor)->next;
        L->index++;
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
    if(L->cursor == L->front) {
        Node front = L->front;
        L->front = N;
        N->next = front;
        front->prev = N;
        L->length++;
        L->index++;
    }
    else {
        Node prev = (L->cursor)->prev;
        prev->next = N;
        (L->cursor)->prev = N;
        N->next = L->cursor;
        N->prev = prev;
        L->length++;
        L->index++;
    }
}

void insertAfter(List L, int x) {
    if(L == NULL) {
        printf("List Error: Calling insertAfter() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling insertAfter() with empty list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0) {
        printf("List Error: Calling insertAfter() with invalid cursor index (-1)\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if(L->cursor == L->back) {
        Node back = L->back;
        L->back = N;
        N->prev = back;
        back->next = N;
        L->length++;
    }
    else {
        Node next = (L->cursor)->next;
        next->prev = N;
        (L->cursor)->next = N;
        N->prev = (L->cursor);
        N->next = next;
        L->length++;
    }
}

void deleteFront(List L) {
    if(L == NULL) {
        printf("List Error: Calling insertBefore() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling insertBefore() with empty list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->front) {
        L->cursor = (L->front)->next;
        L->index++;
    }
    Node old_front = L->front;
    L->front = (L->front)->next;
    (L->front)->prev = NULL;
    freeNode(&old_front);
    L->length--;
    L->index--;
}

void deleteBack(List L) {
    if(L == NULL) {
        printf("List Error: Calling insertBefore() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling insertBefore() with empty list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->back) {
        L->cursor = (L->back)->prev;
        L->index--;
    }
    Node old_back = L->back;
    L->back = (L->back)->prev;
    (L->back)->next = NULL;
    freeNode(&old_back);
    L->length--;
}

void delete(List L) {
    if(L == NULL) {
        printf("List Error: Calling delete() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling delete() with empty list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0) {
        printf("List Error: Calling delete() with an invalid index (-1)\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->front) {
        deleteFront(L);
        return;
    }
    else if(L->cursor == L->back) {
        deleteBack(L);
        return;
    }
    else {
        Node old = L->cursor;
        Node old_prev = (L->cursor)->prev;
        Node old_next = (L->cursor)->next;
        old_prev->next = old_next;
        old_next->prev = old_prev;
        freeNode(&old);
        L->cursor = NULL;
        L->index = -1;
        L->length--;
    }
}

//print function
void printList(FILE* out, List L) {
    Node N = NULL;
    if(L->length == 0) {
        printf("List Error: Calling printList() on a NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    for(N = L->front; N != NULL; N = N->next) {
        fprintf(out, "%d", (L->cursor)->data);
    }
    fprintf(out, "\n");
}

List copyList(List L) {
    if(L == NULL) {
        printf("List Error: calling copyList() on a NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    List copied_List = newList();
    Node curr_node = L->front;
    for(int i = 0; i < length(L); i++) {
        append(copied_List, curr_node->data);
        curr_node = curr_node->next;
    }
    return copied_List;
}