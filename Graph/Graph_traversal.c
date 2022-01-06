#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 10
#define CITIES_NUM 12

typedef struct adjNode* adjLink;
typedef struct adjNode {
  int cityID;
  adjLink next;
}adjNode;

typedef struct basisNode {
  char cityName[MAX_NAME + 1];
  adjLink next;
}basisNode;

//queue는 BFS에서 사용된다.
typedef struct queueNode* queuePointer;
typedef struct queueNode{
  int cityID;
  queuePointer link;
}queueNode;
queuePointer front = NULL, rear = NULL;

basisNode graph[CITIES_NUM] = {0}; //graph는 adjacency list이다.
bool visited[CITIES_NUM] = {false};

void makeAdjacencyList();
void DFS(int cityID);
void addq(int v);
int deleteq();
void BFS(int cityID);
void free_graph();

int main(void){
  makeAdjacencyList();
  printf("--- DFS ---\n");
  for(int i=0; i<CITIES_NUM; i++){
    if(!visited[i]){
      printf("( ");
      DFS(i);
      printf(")\n");
    }
  }
  for(int i=0; i<CITIES_NUM; i++)
    visited[i] = false;
  printf("\n--- BFS ---\n");
  for(int i=0; i<CITIES_NUM; i++){
    if(!visited[i]){
      printf("( ");
      BFS(i);
      printf(")\n");
    }
  }
  free_graph();
  return 0;
}

void makeAdjacencyList(){
  //////////////////////////////////////////graph 만드는 곳////////////////////////////////////////////
  char* str1[CITIES_NUM] = { "mn", "cd", "ab", "gh", "qr", "ef", "uv", "ij", "kl", "op", "st", "wx" };
  char* str2[12] = {
    "ab-cd", //1
    "wx-uv", //2
    "st-uv", //3
    "mn-kl", //4
    "cd-ef", //5
    "wx-op", //6
    "mn-ij", //7
    "ab-kl", //8
    "cd-kl", //9
    "uv-qr", //10
    "op-qr", //11
    "ef-gh"  //12
  };
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  for(int i=0; i<CITIES_NUM; i++){
    strcpy(graph[i].cityName, str1[i]);
  }
  char *token_1, *token_2;
  char temp[MAX_NAME+1];
  int cityID_1, cityID_2;
  for(int i=0; i<12; i++){
    strcpy(temp, str2[i]);
    token_1 = strtok(temp, "-");
    token_2 = strtok(NULL, " ");
    for(int k=0; k<CITIES_NUM; k++){
      if(!strcmp(graph[k].cityName, token_1))
        cityID_1 = k;
      if(!strcmp(graph[k].cityName, token_2))
        cityID_2 = k;
    }
    adjLink new_1 = (adjLink)malloc(sizeof(adjNode));
    adjLink new_2 = (adjLink)malloc(sizeof(adjNode));
    new_1->cityID = cityID_1;
    new_1->next = graph[cityID_2].next;
    graph[cityID_2].next = new_1;
    new_2->cityID = cityID_2;
    new_2->next = graph[cityID_1].next;
    graph[cityID_1].next = new_2;
  }
}

///////////////////////////////////////////DFS///////////////////////////////////////////////
void DFS(int cityID){
  adjLink nextLink;
  visited[cityID] = true;
  printf("%s ", graph[cityID].cityName);
  for(nextLink = graph[cityID].next; nextLink; nextLink = nextLink->next){
    if(!visited[nextLink->cityID])
      DFS(nextLink->cityID);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////BFS///////////////////////////////////////////////
void addq(int v){
  queuePointer new = (queuePointer)malloc(sizeof(queueNode));
  new->cityID = v;
  new->link = NULL;
  if(front == NULL){ //queue에 아무것도 없을 때
    front = new;
    rear = new;
  }
  else{
    rear->link = new;
    rear = new;
  }
}
int deleteq(){
  if(front == NULL)
    return -1;
  int ID = front->cityID;
  queuePointer temp = front;
  front = front->link;
  free(temp);
  return ID;
}
// #define MY_OWN_CODE
void BFS(int cityID){
#ifdef MY_OWN_CODE
  adjLink temp = graph[cityID].next;
  visited[cityID] = true;
  printf("%s ", graph[cityID].cityName);
  int ID;
  while (temp)
  {
    while (temp)
    {
      if (!visited[temp->cityID])
      {
        addq(temp->cityID);
        visited[temp->cityID] = true;
        printf("%s ", graph[temp->cityID].cityName);
      }
      temp = temp->next;
    }
    ID = deleteq();
    if(ID == -1) break;
    temp = graph[ID].next;
  }
#else
  adjLink w;
  printf("%s ", graph[cityID].cityName);
  visited[cityID] = true;
  addq(cityID);
  while (front)
  {
    cityID = deleteq();
    for (w = graph[cityID].next; w; w = w->next)
      if (!visited[w->cityID])
      {
        printf("%s ", graph[w->cityID].cityName);
        addq(w->cityID);
        visited[w->cityID] = true;
      }
  }
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////

void free_graph(){
  adjLink now, next;
  for(int i=0; i<CITIES_NUM; i++){
    now = graph[i].next;
    next = graph[i].next;
    while(next){
      now = next;
      next = next->next;
      free(now);
    }
  }
}

/*
mn -> ij -> kl
cd -> kl -> ef -> ab
ab -> kl -> cd
gh -> ef
qr -> op -> uv
ef -> gh -> cd
uv -> qr -> st -> wx
ij -> mn
kl -> cd -> ab -> mn
op -> qr -> wx
st -> uv
wx -> op -> uv

DFS 결과: (mn에서 시작할 시) -> (mn,ij,kl,cd,ef,gh,ab)  (qr,op,wx,uv,st)
BFS 결과: (mn에서 시작할 시) -> (mn,ij,kl,cd,ab,ef,gh)  (qr에서 시작할 시) -> (qr,op,uv,wx,st)
*/