#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(a, b) a = (NODE*)malloc(sizeof(b));

typedef struct NODE* listPointer;
typedef struct NODE{
    int data;
    listPointer next;
}NODE;

listPointer create();
void insert(listPointer* first, listPointer x);
void allFree(listPointer first);
void printList(listPointer first);

int main(){
    listPointer first = create();
    printList(first);
    insert(&first, first);
    printList(first);

    allFree(first);
    return 0;
}

listPointer create(){
    listPointer first;
    MALLOC(first, *first);
    first->data = 1;
    first->next = NULL;
    return first;
}

void insert(listPointer* first, listPointer x){
    listPointer temp;
    MALLOC(temp, *temp);
    temp->data = 56;
    if(*first){
        temp->next = x->next;
        x->next = temp;        
    }
    else{
        temp->next = NULL;
        *first = temp;
    }
}

void printList(listPointer first){
    printf("The List contains: ");
    while(first){
        printf("%4d", first->data);
        first = first->next;
    }
    printf("\n\n");
}

void allFree(listPointer first){
    listPointer temp;
    while(first){
        temp = first;
        first = first->next;
        free(temp);
    }
    printf("ALL FREE!!\n");
}