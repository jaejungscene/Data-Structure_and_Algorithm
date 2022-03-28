#define MAX_VERTICES 30
int nodeNum=0;

typedef struct adjNode* nodePointer;
typedef struct adjNode {
    int vertex;
    int cost;
    nodePointer link;
}adjNode;
nodePointer graph[MAX_VERTICES];
nodePointer spanningGraph[MAX_VERTICES];
bool visited[MAX_VERTICES];

void  initialize(void)
{
  int i;
  for(i = 0; i < nodeNum; i++) {
    visited[i] = false;
  }
}

void createNewNode(int node1, int node2, int cost){
  nodePointer new1, new2;
  new1 = (nodePointer)malloc(sizeof(adjNode));
  new2 = (nodePointer)malloc(sizeof(adjNode));

  if(graph[node1]==NULL) nodeNum++;
  if(graph[node2]==NULL) nodeNum++;

  new1->vertex = node1;
  new1->cost = cost;
  new1->link = graph[node2];
  graph[node2] = new1;

  new2->vertex = node2;
  new2->cost = cost;
  new2->link = graph[node1];
  graph[node1] = new2;
}

int createGraph(){
  printf("Enter the connections like {v}-{v}-{cost} (Enter \'.\' to finish) (Enter \'e\' to end this system)\n");
  char connection[10];
  int node1, node2, cost;
  while(true){
    scanf("%s", connection);
    if(connection[0]=='.')
      break;
    if(connection[0] == 'e')
      return 0;
    node1 = atoi(strtok(connection, "-"));
    node2 = atoi(strtok(NULL, "-"));
    cost = atoi(strtok(NULL, " "));
    nodePointer temp = graph[node1];
    bool already = false;
    while(temp){ //중복입력 detect
      if(temp->vertex == node2){
        already = true;
        break;
      }
      temp = temp->link;
    }
    if(already == false)
      createNewNode(node1,node2,cost);
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

void DFS_for_result(int v, int* num){
  nodePointer nextLink;
  visited[v] = true;
  (*num)++;
  if(*num == nodeNum) printf("%d", v);
  else  printf("%d-", v);
  for(nextLink = spanningGraph[v]; nextLink; nextLink = nextLink->link){
    if(!visited[nextLink->vertex])
      DFS_for_result(nextLink->vertex, num);
  }
}

void print_result(){
  for(int i=0; i<nodeNum; i++){
    visited[i] = false;
  }
  int num = 0;
  DFS_for_result(0, &num);
}
