#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20
#define TRUE 1
#define FALSE 0
#define MALLOC(a,b) a = (nodePointer)malloc(a,b);

typedef struct node* nodePointer;
typedef struct node{
    int data;
    nodePointer link;
}node;

int main(void){
    short int out[MAX_SIZE]; //seq[i]를 들렀는지(0) 안들렀는지(1) 알려줌
    nodePointer seq[MAX_SIZE]; //인덱스는 숫자를 의미, 인덱스와 eqivalent한 숫자들을 linked list로 묶음
    nodePointer x,y,top;
    int i,j,n;
    printf("Enter the size (<= %d): ", MAX_SIZE); 
    scanf("%d", &n);

    /* set */
    for (i=0; i<n; i++) {
        out[i]=TRUE; seq[i]=NULL;
    }
    printf("Enter a pair of numbers (-1 -1 to quit): ");
    scanf("%d%d", &i, &j);

    /* phase 1: input the equivalence class */ 
    while (i >= 0)
    {
        x = (nodePointer)malloc(sizeof(*x));
        x->data = j;
        x->link = seq[i];
        seq[i] = x;
        x = (nodePointer)malloc(sizeof(*x));
        x->data = i;
        x->link = seq[j];
        seq[j] = x;
        printf("Enter a pair of numbers (-1 -1 to quit): ");
        scanf("%d%d", &i, &j);
    }

    /* phase 2: print out the equivalent classes */
    for (i = 0; i < n; i++)
    {
        if (out[i])
        {
            printf("\nNew class: %5d", i);
            out[i] = FALSE;
            x = seq[i];
            top = NULL;
            for (;;)
            {
                while (x)
                {
                    j = x->data;
                    if (out[j]) //방문 하지 않았다면(out[j]==0)
                    {
                        printf("%5d", j);
                        out[j] = FALSE;
                        y = x->link;
                        x->link = top; //stack에 쌓아 놓는다.
                        top = x; //stack의 꼭대기 현재의 값을 쌓는다.
                        x = y;
                    }
                    else
                        x = x->link;
                }
                if (!top)
                    break;
                x = seq[top->data];
                top = top->link;
            } /* for (;;) */
        } /* for(i) */
    }

    return 0;
}
