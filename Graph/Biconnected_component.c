#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_VERTICES 30
#define MIN2(x,y) ((x) < (y) ? (x) : (y))

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*  low(u) = min {   
*                  dfn(u) ,
*                  min{low(w) | w is a child of u} ,
*                  min{dfn(w) | (u,w) is a back edge}
*                }
*/

typedef struct adjNode* nodePointer;
typedef struct adjNode {
    int vertex;
    nodePointer link;
}adjNode;
nodePointer graph[MAX_VERTICES];

typedef struct{
  int x;
  int y;
}Stack;
Stack stack[MAX_VERTICES];
int top = 0;

bool articulation_point[MAX_VERTICES];
bool visited[MAX_VERTICES];
int low[MAX_VERTICES];
int dfn[MAX_VERTICES];
int num, nodeNum;

void push(int x, int y){
  top++;
  stack[top].x = x;
  stack[top].y = y;
}

void pop(int* x, int* y){
  *x = stack[top].x;
  *y = stack[top].y;
  top--;
}

void  initialize(void)
{
  int i;
  for(i = 0; i < nodeNum; i++) {
    visited[i] = false;
    articulation_point[i] = false;
    dfn[i] = low[i] = -1;
  }
  num=0;
}

// void dfnlow(int u, int v)
// {
//   nodePointer ptr;
//   int w;
//   dfn[u] = low[u] = num++;
//   for (ptr = graph[u]; ptr; ptr = ptr->link)
//   {
//     w = ptr->vertex;
//     if (dfn[w] < 0)
//     { /* unvisited vertex */
//       dfnlow(w, u);
//       low[u] = MIN2(low[u], low[w]);
//     }
//     else if (w != v) /* (u,w) is a back edge */
//       low[u] = MIN2(low[u], dfn[w]);
//   }
// }

void bicon(int u, int v)
{
  nodePointer ptr;
  int w, x, y;
  dfn[u] = low[u] = num++;
  for (ptr = graph[u]; ptr; ptr = ptr->link)
  {
    w = ptr->vertex;
    // if (v != w && dfn[w] < dfn[u])
    //   push(u, w);
    if (dfn[w] < 0)
    { /* unvisited vertex */
      bicon(w, u);
      low[u] = MIN2(low[u], low[w]);
      if (low[w] >= dfn[u])
      { /* u: articulation point */
        if(v == -1){
          if(ptr->link!=NULL)
            articulation_point[u] = true;
        }
        else
          articulation_point[u] = true;

        // printf("New biconnected component : ");
        // do
        // {
        //   pop(&x, &y);
        //   printf(" <%d, %d>", x, y);
        // } while (!((x == u) && (y == w)));
        // printf("\n");
      } /* if(low[w] >= dfn[u]) */
    }
    else if (w != v)
      low[u] = MIN2(low[u], dfn[w]);
  } /* for (ptr) */
}

void print_result(){
  printf("Articulation Points : ");
  for (int i = 0; i < MAX_VERTICES; i++)
    if (articulation_point[i] == true)
      printf("%-3d", i);

  
  printf("\n------------------------------------------------------");
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////

int createGraph();
void createNewNode();
void free_list();

int main(){
  int cmd;
  while (true)
  {
    cmd = createGraph();
    if (cmd == 0)
      break;
    initialize();
    bicon(0, -1);
    print_result();
    free_list();
    printf("\n\n");
  }
  printf("System exit....\n");
  return 0;
}

void createNewNode(int node1, int node2){
  nodePointer new1, new2;
  new1 = (nodePointer)malloc(sizeof(adjNode));
  new2 = (nodePointer)malloc(sizeof(adjNode));

  if(graph[node1]==NULL) nodeNum++;
  if(graph[node2]==NULL) nodeNum++;

  new1->vertex = node1;
  new1->link = graph[node2];
  graph[node2] = new1;

  new2->vertex = node2;
  new2->link = graph[node1];
  graph[node1] = new2;
}

int createGraph(){
  printf("Enter the connections (ex: 1-3) (Enter \'.\' to finish) (Enter \'e\' to end this system)\n");
  char connection[10];
  int node1, node2;
  while(true){
    scanf("%s", connection);
    if(connection[0]=='.')
      break;
    if(connection[0] == 'e')
      return 0;
    node1 = atoi(strtok(connection, "-"));
    node2 = atoi(strtok(NULL, " "));
    nodePointer temp = graph[node1];
    bool already = false;
    while(temp){
      if(temp->vertex == node2){
        already = true;
        break;
      }
      temp = temp->link;
    }
    if(already == false)
      createNewNode(node1,node2);
  }
  return 1;
}

void free_list(){
  nodePointer now, prev;
  for(int i=0; i<MAX_VERTICES; i++){
    now = graph[i];
    graph[i] = NULL;
    while(now){
      prev = now;
      now = now->link;
      free(prev);
    }
  }
}


/*

0-1
1-2
1-3
2-4
3-4
.
A.P: 1

0-1
1-2
1-3
2-4
4-3
3-5
5-6
5-7
6-7
7-8
7-9
.
A.P: 1,3,5,7

3-1
3-0
3-2
1-2
1-6
1-5
0-2
0-4
2-5
.
A.P: 0,1

*/