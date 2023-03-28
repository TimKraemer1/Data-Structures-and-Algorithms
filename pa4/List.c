//Tim Kraemer
//CruzID: tikraeme
//pa4

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "List.h"

typedef struct NodeObj* Node;
typedef struct NodeObj {
    void* data;
    Node prev;
    Node next;
} NodeObj;

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

Node newNode(void* data) {
    Node N = malloc(sizeof(NodeObj));
    assert( N != NULL );
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

void freeNode(Node* pN) {
    if(pN && *pN) {
        free(*pN);
        *pN = NULL;
    }
}

//List Constructor
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    assert(L != NULL);
    L->front = NULL;
    L->cursor = NULL;
    L->back = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

//List Destructor
void freeList(List* pL) {
    if(pL && *pL) {
        if(length(*pL) != 0) {clear(*pL);}
        free(*pL);
        *pL = NULL;
    }
}

//returns List length
int length(List L) {
    if(L == NULL) {
        printf("List Error: Calling index() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

//returns List index
int index(List L) {
    if(L == NULL) {
        printf("List Error: Calling index() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

//returns data from front node in the List
void* front(List L) {
    if(L == NULL) {
        printf("List Error: Calling front() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0) {
        printf("List Error: Calling front() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->front)->data;
}

//returns data from the back node in the List
void* back(List L) {
    if(L == NULL) {
        printf("List Error: Calling back() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0) {
        printf("List Error: Calling back() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->back)->data;
}

//return data from the cursor node in the List
void* get(List L) {
    if(L == NULL) {
        printf("List Error: Calling get() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0) {
        printf("List Error: Calling get() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0) {
        printf("List Error: Calling get() with an invalid index value\n");
	exit(EXIT_FAILURE);
    }
    return (L->cursor)->data;
}

//clears the List so that it becomes empty, sets cursor as undefined and index to -1
void clear(List L) {
    if(L == NULL) {
        printf("List Error: Calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length > 0) {
        Node M = L->front;
        Node M_next = NULL;
        for(int i = 0; i < L->length; i++) {
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

//changes the value of the node that the cursor is currently on in List
void set(List L, void* x) {
    if(L == NULL) {
        printf("List Error: Calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling set() on an empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0) {
        printf("List Error: Calling set() with inalid index value (-1)\n");
        exit(EXIT_FAILURE);
    }
    (L->cursor)->data = x;
}

//moves the cursor to the front of the list
void moveFront(List L) {
    if(L == NULL) {
        printf("List Error: Calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0){
        L->cursor = L->front;
        L->index = 0;
    }
}

//moves the cursor to the back of the List
void moveBack(List L) {
    if(L == NULL) {
        printf("List Error: Calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0) {
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
}

//moves cursor to the node before the cursor
void movePrev(List L) {
    if(L == NULL) {
        printf("List Error: Calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0) {
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
}

//moves cursor to the node after the cursor
void moveNext(List L) {
    if(L == NULL) {
        printf("List Error: Calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) > 0) {
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
}

//inserts new element into List. If List is not empty, inserts element before first element
void prepend(List L, void* x) {
    if(L == NULL) {
        printf("List Error: Calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if(length(L) == 0) {
        L->back = N;
        L->front = N;
    }
    //if List is not empty
    else {
        Node temp = L->front;
        L->front = N;
        N->next = temp;
        temp->prev = N;
    }
    L->length++;
    if(L->cursor != NULL) {
        L->index++;
    }
}

//inserts new element into List. If List is not empty, inserts element after last element
void append(List L, void* x) {
    if(L == NULL) {
        printf("List Error: Calling prepend on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if(length(L) == 0) {
        L->back = N;
        L->front = N;
    }
    else {
        Node temp = L->back;
        L->back = N;
        N->prev = temp;
        temp->next = N;
    }
    L->length++;
}

//inserts element before cursor element in List
void insertBefore(List L, void* x) {
    if(L == NULL) {
        printf("List Error: Calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0) {
        printf("List Error: Calling insertBefore() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0) {
        printf("List Error: Calling insertBefore() with invalid cursor index (-1)\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->front) {
        prepend(L, x);
    }
    else {
        Node N = newNode(x);
        Node prev = (L->cursor)->prev;
        prev->next = N;
        (L->cursor)->prev = N;
        N->next = L->cursor;
        N->prev = prev;
        L->length++;
        L->index++;
    }
}

//inserts element after cursor element in List
void insertAfter(List L, void* x) {
    if(L == NULL) {
        printf("List Error: Calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling insertAfter() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0) {
        printf("List Error: Calling insertAfter() with invalid cursor index (-1)\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->back) {
        append(L, x);
    }
    else {
        Node N = newNode(x);
        Node next = (L->cursor)->next;
        next->prev = N;
        (L->cursor)->next = N;
        N->prev = (L->cursor);
        N->next = next;
        L->length++;
    }
}

//deletes front element of List
void deleteFront(List L) {
    if(L == NULL) {
        printf("List Error: Calling deleteFront() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling deleteFront() with empty list reference\n");
        exit(EXIT_FAILURE);
    }
    int lengthList = length(L);
    Node old_Front = L->front;

    //check if list is only 1 element
    if(lengthList == 1) {
        L->cursor = NULL;
        L->front = NULL;
        L->back = NULL;
        L->index = -1;
        L->length--;
        freeNode(&old_Front);
        return;
    }

    L->length--;
    L->front = old_Front->next;
    (L->front)->prev = NULL;
    //if cursor is pointing to the front, set it to null
    if(L->cursor != old_Front) {
        L->index--;
    }
    else {
        L->index = -1;
        L->cursor = NULL;
    }
    freeNode(&old_Front);
}

//deletes back element of List
void deleteBack(List L) {
	if(L == NULL) {
        printf("List Error: Calling deleteBack() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling deleteBack() with empty list reference\n");
        exit(EXIT_FAILURE);
    }
    int listLen = length(L);
    Node old_back = L->back;

    //check if List has only 1 element
    if(listLen == 1) {
        L->cursor = NULL;
        L->front = NULL;
        L->back = NULL;
        L->index = -1;
        L->length--;
        freeNode(&old_back);
        return;
    }

    L->length--;
    L->back = old_back->prev;
    (L->back)->next = NULL;
    if(L->cursor == old_back) {
        L->index = -1;
        L->cursor = NULL;
    }
    freeNode(&old_back);
}

//deletes cursor element of List
void delete(List L) {
    if(L == NULL) {
        printf("List Error: Calling deleteFront() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->length == 0) {
        printf("List Error: Calling deleteFront() with empty list reference\n");
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
