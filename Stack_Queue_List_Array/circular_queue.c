/**
 * implementation of simple appilication using circular queue
 * you only add integer to the queue in this implementation.
 * if you want to increase the size of the queue,
 * rewrite the defined MAX_QUEUE_SIZE number.
*/
#include <stdio.h>
#define MAX_QUEUE_SIZE 3

typedef union element{
    int integer;
    double floating;
}element;

element queue[MAX_QUEUE_SIZE];
int front=0, rear=0;

void queueFull()
{
    fprintf(stderr, "Error: \"addq\" is not valid. queue is full!!!\n");
}

void queueEmpty()
{
    fprintf(stderr, "Error: \"deleteq\" is not valid. queue is empty!!!\n");
}

void addq(element item)
{
    int temp = rear;
    rear = (rear+1) % MAX_QUEUE_SIZE;
    if (front == rear){
        queueFull(); /* print error and exit */
        rear = temp;
        return;
    }
    queue[rear] = item; 
    printf("element is successfully \"added\" to queue\n");
}

void deleteq(){
    if (front == rear){
        queueEmpty();
        return;
    }
    front = (front+1) % MAX_QUEUE_SIZE;
    queue[front].integer = -9999;
    printf("element is successfully \"deleted\" to queue\n");
}

void printAll()
{
    if(front == rear){
        queueEmpty();
        return;
    }
    int i = front;
    int flag = 0;
    printf("front |");
    for(; i!=rear;){
        i=(i+1)%MAX_QUEUE_SIZE;
        printf(" %d |", queue[i].integer);
    }
    printf(" rear\n");
}

int main(int argc, char *argv[])
{
    int command;
    element added;
    int i = 0;
    while (1) {
        printf("(1)deleteq, (2)addq, (3)printAll >> ");
        scanf("%d", &command);
        if(command == 1){
            deleteq();
        }
        else if(command == 2){
            printf("enter element >> ");
            scanf("%d", &added.integer);
            addq(added);
        }
        else if(command == 3){
            printAll();
        }
        else    break;
        printf("\n");
    }
    printf("\n------- finish -------\n");
    return 0;
}