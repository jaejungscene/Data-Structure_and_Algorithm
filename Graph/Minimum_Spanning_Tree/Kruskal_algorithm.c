#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_EDGES 31
#define MAX_VERTIECS 15
/* 
*  1. min heap으로 가장작은 cost를 가지는 edge를 고르다.
*  2. union-find를 이용해 선택된 edge가 cycle을 만드는지 확인하다.
*/

typedef struct adjNode* nodePointer;
typedef struct adjNode {
    int vertex;
    int cost;
    nodePointer link;
}adjNode;

typedef struct{
  int v1, v2;
  int cost;
}Edge;

Edge minHeap[MAX_EDGES+1];
int parent[MAX_VERTIECS]; //union-find
int heapSize;
// int edgeNum;
int nodeNum;

nodePointer spanningGraph[MAX_VERTIECS];
// bool visited[MAX_VERTIECS];

void  initialize(void)
{
  heapSize = 0; nodeNum = 0;
  // edgeNum = 0;
  for(int i = 0; i < MAX_VERTIECS; i++) {
    spanningGraph[i] = NULL;
    parent[i] = -1;
    // visited[MAX_VERTIECS] = false;
  }
}

void swap(Edge* parent, Edge* child){
  Edge temp = *parent;
  *parent = *child;
  *child = temp;
}

void push(int v1, int v2, int cost){
  if(heapSize == MAX_EDGES){
    printf("minHeap is full!!\n\n");
    return;
  }
  else{
    heapSize++;
    minHeap[heapSize].v1 = v1;
    minHeap[heapSize].v2 = v2;
    minHeap[heapSize].cost = cost;
    for(int n=heapSize; (minHeap[n/2].cost > minHeap[n].cost)&&(n>1) ; n/=2){
      swap(&minHeap[n/2], &minHeap[n]);
    }
  }
}

Edge* pop(){
  if(heapSize == 0){
    printf("minHeap is empty!!\n\n");
    return NULL;
  }
  else{
    Edge* temp = (Edge*)malloc(sizeof(Edge));
    temp->v1 = minHeap[1].v1;
    temp->v2 = minHeap[1].v2;
    temp->cost = minHeap[1].cost;
    minHeap[1] = minHeap[heapSize];
    heapSize--;
    int n = 1;
    while((n*2<=heapSize)){
      if((n*2 == heapSize))
        n = n*2;
      else
        n = minHeap[n*2].cost < minHeap[n*2+1].cost ? n*2 : n*2+1;
      if(minHeap[n].cost < minHeap[n/2].cost)
        swap(&minHeap[n], &minHeap[n/2]);
    }
    return temp;
  }
}

int createHeap(){
  printf("Enter the vertex number (or Enter \'0\' to end this system) >> ");
  scanf("%d", &nodeNum);
  if(nodeNum == 0)
    return 0;
  printf("Enter the connections like {v}-{v}-{cost} (Enter \'.\' to finish) (Enter \'e\' to end this system)\n");
  char connection[10];
  int v1, v2, cost;
  while(true){
    scanf("%s", connection);
    if(connection[0]=='.')
      break;
    if(connection[0] == 'e')
      return 0;
    v1 = atoi(strtok(connection, "-"));
    v2 = atoi(strtok(NULL, "-"));
    cost = atoi(strtok(NULL, " "));
    push(v1, v2, cost);
    // edgeNum++;
  }
  return 1;
}

int Find(int i){
  for(; parent[i]>=0; i=parent[i]);
  return i;
}

void Union(int i, int j){
  //if the number of nodes in tree i is less than the number in tree j then make j the parent of i
  if (parent[i] < 0 && parent[j] < 0){
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j]){
      parent[i] = j; // make j the new root
      parent[j] = temp;
    }
    else{
      parent[j] = i; // make i the new root
      parent[i] = temp;
    }
  }
  else
    Union(Find(i), Find(j));
}

void createNewNode(int v1, int v2, int cost){
  nodePointer new1, new2;
  new1 = (nodePointer)malloc(sizeof(adjNode));
  new2 = (nodePointer)malloc(sizeof(adjNode));

  new1->vertex = v1;
  new1->cost = cost;
  new1->link = spanningGraph[v2];
  spanningGraph[v2] = new1;

  new2->vertex = v2;
  new2->cost = cost;
  new2->link = spanningGraph[v1];
  spanningGraph[v1] = new2;
}

void find_minimum_spanning_tree(){
  int n = 0;
  int r1, r2;
  Edge* temp;
  while(n<nodeNum-1){
    temp = pop();
    r1 = Find(temp->v1);
    r2 = Find(temp->v2);
    if(r1==r2) continue;
    Union(temp->v1, temp->v2);
    createNewNode(temp->v1, temp->v2, temp->cost);
    free(temp);
    n++;
  }
}

// void DFS(int v){
//   nodePointer ptr;
//   visited[v] = true;
//   printf("%-3d", v);
//   for(ptr = spanningGraph[v]; ptr; ptr = ptr->link){
//     if(!visited[ptr->vertex])
//       DFS_for_makeing_graph(ptr->vertex);
//   }
// }

void print_result(){
  printf("------ result ------\n");
  int n = 0;
  nodePointer temp;
  for(int i=0; i<MAX_VERTIECS; i++){
    if(n >= nodeNum) break;
    if(spanningGraph[i]!=NULL){
      printf("%d -> ", i);
      temp = spanningGraph[i];
      while(temp){
        printf("%-3d",temp->vertex);
        temp = temp->link;
      }
      printf("\n");
      n++;
    }
  }
  printf("--------------------");
}

void free_list(){
  int n = 0;
  nodePointer now, prev;
  for(int i=0; i<MAX_VERTIECS; i++){
    if(n >= nodeNum) break;
    now = spanningGraph[i];
    while(now){
      prev = now;
      now = now->link;
      free(prev);
    }
    n++;
  }
}



int main(){
  int cmd;
  while (true)
  {
    initialize();
    cmd = createHeap();
    if (cmd == 0)
      break;
    find_minimum_spanning_tree();
    print_result();
    free_list();
    printf("\n\n");
  }
  printf("System exit....\n");
  return 0;
}

/*
========================================
7

0-5-10
0-1-28
5-4-25
4-6-24
6-1-14
1-2-16
2-3-12
3-4-22
3-6-18
.
--------- result --------
0 -> 5 
1 -> 2  6
2 -> 1  3
3 -> 4  2
4 -> 5  3
5 -> 4  0
6 -> 1

========================================
9

0-8-5
0-3-2
0-1-3
1-7-4
2-3-6
2-7-7
3-4-11
4-8-10
4-5-8
5-2-1
5-6-9
.
------- result ------
0 -> 8  1  3  
1 -> 7  0  
2 -> 3  5  
3 -> 2  0  
4 -> 5  
5 -> 6  4  2  
6 -> 5  
7 -> 1  
8 -> 0

=========================================
*/