#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(a, b) a = (NODE*)malloc(b);

typedef struct NODE* listPointer;
typedef struct NODE{
    int data;
    listPointer llink;
    listPointer rlink;
}NODE;

listPointer create();
void insert(listPointer* first, listPointer x);
void delete(listPointer* first, listPointer trail, listPointer x);
void allFree(listPointer first);
void printList(listPointer first);

int main(){
    listPointer first = create();
    int temp;
    while(1){
        printf("(1)printList, (2)insert, (3)delete, (4)exit: ");
        scanf("%d",&temp);
        switch(temp){
            case 1:
                printList();
                break;
            case 2:
                printf("Enter a number inserted: ");
                insert(&frist, first);
                break;
            case 3:
                printf("Enter a number deleted: ");
                delete(&first,);
                break;
            case 4:
                allFree(first);
                break;
            default:
                printf("the number you entered is incorrect!!");
        }
    }
    return 0;
}

listPointer create(){ //처음노드는 data는 처음노드를 제외한 링크의 크기를 나타낸다.
    listPointer first;
    MALLOC(first, sizeof(*first));
    first->data = 0;
    first->llink = first;
    first->rlink = first;
    return first;
}

void insert(listPointer* first, listPointer x){
    listPointer temp;
    MALLOC(temp, sizeof(*temp));
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

void delete(listPointer* first, listPointer trail, listPointer x){
    if()
    trail->next = x->next;
    free(x);
}

void printList(listPointer first){
    listPointer temp = first;
    printf("The List contains: ");
    printf("%4d", temp->data);
    temp = temp->rlink;
    while(first!=temp){
        printf("%4d", temp->data);
        temp = temp->rlink;
    }
    printf("-------------\n\n");
}

void allFree(listPointer first){
    listPointer temp = first;
    int size = first->data;
    for(int i=0; i<=size; i++){
        temp = first->rlink;
        free(first);
        first = temp;
    }
    printf("ALL FREE!!\nSystemm exit...\n");
}