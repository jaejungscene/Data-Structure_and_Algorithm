#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ELEMENTS 200
#define MAX_NUM_SIZE 2 
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
/* insertion deletion 모두 구현 */
typedef struct{
  int value;
}element;

element heap[MAX_ELEMENTS];
int heapSize = 0; //0번째는 아무것도 들어가지 않는다.

void swap(element* parent, element* child){
  element temp = *parent;
  *parent = *child;
  *child = temp;
}

void push(int v){
  if(HEAP_FULL(heapSize)){
    printf("heap is full!!\n\n");
    return;
  }
  else{
    heapSize++;
    int n;
    element temp;
    heap[heapSize].value = v;
    for(n=heapSize; (heap[n/2].value < heap[n].value)&&(n>1) ; n/=2){
      swap(&heap[n/2], &heap[n]);
    }
  }
}

void pop(){
  if(heapSize == 0){
    printf("heap is empty!!\n\n");
    return;
  }
  else{
    printf("max value : %d\n\n", heap[1].value);
    element temp;
    int n = 1;
    heap[1] = heap[heapSize];
    heapSize--;

    while((n*2<=heapSize)){
      if((n*2 == heapSize))
        n = n*2;
      else
        n = heap[n*2].value > heap[n*2+1].value ? n*2 : n*2+1;
      if(heap[n].value > heap[n/2].value)
        swap(&heap[n], &heap[n/2]);
    }
    return;
  }
}

void printHeap(){
  if(heapSize == 0){
    printf("heap is empty!!\n\n");
    return;
  }
  for(int i=1; i<=heapSize; i++){
    if(i%2 == 0)
      printf("\n");
    printf("%3d", heap[i].value);
  }
  printf("\n\n");
}

void process_push(){
  char value[MAX_NUM_SIZE+1];
  while(1){
    printf("Enter value\n");
    scanf("%s", value);
    if(value[0]!='.')
      push(atoi(value));
    else
      break;
  }
  printf("\n");
}

int main(){
  int cmd;
  while(1){
    printf("in heap, (1)push  (2)pop  (3)print  (4)exit :");
    scanf("%d", &cmd);

    if(cmd==1){
      process_push();
    }
    else if(cmd==2){
      pop();
    }
    else if(cmd==3){
      printHeap();
    }
    else if(cmd==4){
      break;
    }
    else{
      printf("your response is incorrect!!\n");
    }
  }
  return 0;
}