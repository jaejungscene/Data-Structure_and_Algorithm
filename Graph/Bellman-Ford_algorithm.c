/////////////////     directed graph   ////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CITIES 20
#define MAX_NAME 10
#define MAX_COST 1000000

typedef struct adjNode* adjLink;
typedef struct adjNode {
    int cityID;
    int cost;
    adjLink next;
}adjNode;

typedef struct basisNode {
    char cityName[MAX_NAME + 1];
    adjLink next;
}basisNode;

typedef struct treeNode* treePointer;
typedef struct treeNode
{
    int cityID;
    treePointer leftChild;
    treePointer rightChild;
} treeNode;

//function frame
void input_cities();
treePointer newNode(int k);
treePointer insert(treePointer node, int k);
void make_BST();
int search_BST(treePointer node, char* cityName);
void add_adjList(int cityID_1, int cityID_2, int cost);
void initialize_adjMatrix();
void make_adjList_adjMatrix();
void free_BST(treePointer node);
void free_list();
void reset();

void print_path(int s, int e, int distance[], int pi[]);
void search_shortest_path();

int choose(int distance[], bool found[]);
void Dijkstra(int v, int distance[], int pi[]);

bool it_is_same(int dist[], int dist_temp[]);
void Bellman_Ford(int start, int distance[], int pi[]);

//global variable
int cities_num = 0;
basisNode graph[MAX_CITIES] = { 0 };
treePointer treeHead = NULL;
int graph_Matrix[MAX_CITIES][MAX_CITIES] = {0};

int main(void) {
    bool built_path = false;
    int selection;
    printf("도시 간 최소 비용 경로 안내 서비스에 오신 것을 환영합니다.\n");
    while (1) {
        printf("-----------------------\n");
        printf("원하는 기능을 선택하세요\n1:입력 2:검색 3:종료\n");
        scanf("%d", &selection);
        if (selection == 1) {
            reset();
            input_cities();
            make_BST();
            make_adjList_adjMatrix();
            built_path = true;
        }
        else if (selection == 2) {
            if (built_path == false) {
                printf("아직 도시 간 도로 구축 데이터베이스가 만들어지지 않았습니다.\n");
                continue;
            }
            search_shortest_path();
        }
        else if (selection == 3)
            break;
        else {
            printf("잘못된 선택입니다.\n");
            continue;
        }
    }
    printf("서비스를 종료합니다\n");
    return 0;
}

////////////////////////////////////   Bellman-Ford  /////////////////////////////////////////
bool it_is_same(int dist[], int dist_temp[]){
    bool result = true;
    for(int i=0; i<cities_num; i++){
        if(dist[i] != dist_temp[i])
            result = false;
        dist[i] = dist_temp[i];
    }
    return result;
}

void Bellman_Ford(int start, int distance[], int pi[]) {
    int dist_temp[MAX_CITIES] = {0};
    distance[start] = 0; pi[start] = start;
    for(int i=0; i<cities_num; i++){ //initialize
        if(i!=start){
            distance[i] = graph_Matrix[start][i];
            if(distance[i] != MAX_COST)
                pi[i] = start;
            else
                pi[i] = -1;
        }
    }
    int min;
    do{
        for (int u = 0; u < cities_num; u++){
            if (u != start){
                min = distance[u];
                for (int i = 0; i < cities_num; i++){
                    if(min > distance[i]+graph_Matrix[i][u]){
                        min = distance[i]+graph_Matrix[i][u];
                        pi[u] = i;
                    }
                }
                dist_temp[u] = min;
            }
        }
    } while (!it_is_same(distance, dist_temp));
}
////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////   Dijkstra   //////////////////////////////////////////
int choose(int distance[], bool found[]) {
    int i, min = MAX_COST, minpos = -1;
    for (i = 0; i < cities_num; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void Dijkstra(int v, int distance[], int pi[]) {
    int i, u, w;
    bool found[MAX_CITIES];
    adjLink temp = graph[v].next;

    for (int i = 0; i < cities_num; i++) {
        found[i] = false;
        pi[i] = -1;
        distance[i] = MAX_COST; //MAX_COST == 2147483647
    }
    while (temp) {
        distance[temp->cityID] = temp->cost;
        pi[temp->cityID] = v;
        temp = temp->next;
    }

    found[v] = true;
    distance[v] = 0;
    pi[v] = v;
    for (i = 0; i < cities_num - 2; i++) {
        u = choose(distance, found); //한 노드의 shortest path 결정
        if (u == -1)//더 이상 v에서 갈 수 없는 경로가 존재할 경우
            break;
        found[u] = true;
        temp = graph[u].next;
        while (temp) {
            if (!found[temp->cityID])
                if (distance[u] + (temp->cost) < distance[temp->cityID]) {
                    distance[temp->cityID] = distance[u] + (temp->cost);
                    pi[temp->cityID] = u;
                }
            temp = temp->next;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
void print_path(int s, int e, int distance[], int pi[]) {
    int stack[MAX_CITIES - 2];
    int top = 0, temp = e;
    while (s != pi[temp]) {
        stack[top] = pi[temp];
        top++;
        temp = pi[temp];
    }
    printf("Path:%s-", graph[s].cityName);
    top--;
    while (top >= 0) {
        printf("%s-", graph[stack[top]].cityName);
        top--;
    }
    printf("%s ", graph[e].cityName);
    printf("Cost:%d\n", distance[e]);
}

void search_shortest_path() {
    char cityName[MAX_NAME + 1];
    int Dijkstra_distance[MAX_CITIES], Dijkstra_pi[MAX_CITIES];
    int Bellman_Ford_distance[MAX_CITIES], Bellman_Ford_pi[MAX_CITIES];
    int start, destination;

    while (1) {
        printf("**출발 도시 이름을 입력하세요.\n");
        scanf("%s", cityName);
        start = search_BST(treeHead, cityName);
        if (start == -1) {
            printf("잘못된 도시 이름입니다\n");
            continue;
        }
        Dijkstra(start, Dijkstra_distance, Dijkstra_pi);
        Bellman_Ford(start, Bellman_Ford_distance, Bellman_Ford_pi);

        //// test ////
        for(int i=0; i<cities_num; i++)
            printf("%d ", Dijkstra_pi[i]);
        printf("\n");
        for(int i=0; i<cities_num; i++)
            printf("%d ", Bellman_Ford_pi[i]);
        printf("\n");
        //////////////

        break;
    }
    while (1) {
        printf("**도착 도시 이름을 입력하세요 (종료 시 '.'입력)\n");
        scanf("%s", cityName);
        if (!strcmp(cityName, ".")) break;
        destination = search_BST(treeHead, cityName);
        if (destination == -1) {
            printf("잘못된 도시 이름입니다\n");
            continue;
        }
        if (Bellman_Ford_pi[destination] == -1 || Dijkstra_pi[destination] == -1) {
            printf("경로가 없습니다\n");
            continue;
        }
        printf("Dijkstra>>      "); print_path(start, destination, Dijkstra_distance, Dijkstra_pi);
        printf("Bellman-Ford>>  "); print_path(start, destination, Bellman_Ford_distance, Bellman_Ford_pi);
        printf("\n");
    }
    printf("**검색을 종료합니다\n");
}
//////////////////////////////////////////////////////////////////////////////////////



void input_cities() {
    char input[(MAX_CITIES * MAX_NAME) + MAX_CITIES];
    char* token;
    int count;
    while (1) {
        printf("도시 수를 입력해 주세요\n");
        scanf("%d%*c", &cities_num);
        printf("도시 이름을 입력해 주세요\n");
        scanf("%[^\n]s", input);

        count = 0;
        token = strtok(input, " ");
        while (token) { //입력한 도시 수가 일치하는지 확인하면서, 동시에 ajacency list의 basis가 되는 Node들을 넣는다.
            if (count < cities_num) {
                strcpy(graph[count].cityName, token);
                graph[count].next = NULL;
            }
            count++;
            token = strtok(NULL, " ");
        }
        if (count == cities_num)
            break;
        else {
            if (count > cities_num)
                printf("제시된 도시 수보다 도시 이름의 갯수가 더 많습니다\n");
            else//count < cities_num
                printf("제시된 도시 수보다 도시 이름의 갯수가 더 적습니다\n");
            continue;
        }
    }
}

treePointer newNode(int k) {
    treePointer new = (treePointer)malloc(sizeof(*new));
    new->cityID = (int)k;
    new->leftChild = NULL;
    new->rightChild = NULL;
    return new;
}

treePointer insert(treePointer node, int k)
{
    /* If the tree is empty, return a new node*/
    if (node == NULL)
        return newNode(k);
    /* Otherwise, recur down the tree*/
    if (strcmp(graph[k].cityName, graph[node->cityID].cityName) < 0)
        node->leftChild = insert(node->leftChild, k);
    else
        node->rightChild = insert(node->rightChild, k);
    /* return the (unchanged) node pointer*/
    return node;
}

void make_BST() {
    for (int i = 0; i < cities_num; i++) {
        treeHead = insert(treeHead, i);
    }
}

int search_BST(treePointer node, char* cityName) {
    if (!node) return -1; //tree에 입력받은 cityName이 없는 경우
    if (!strcmp(cityName, graph[node->cityID].cityName))//tree에서 입력받은 cityName을 찾을 경우
        return node->cityID;
    if (strcmp(cityName, graph[node->cityID].cityName) < 0)
        return search_BST(node->leftChild, cityName);
    else
        return search_BST(node->rightChild, cityName);
}

void add_adjList(int cityID_1, int cityID_2, int cost) {
    adjLink new = (adjLink)malloc(sizeof(*new));

    new->cityID = cityID_2;
    new->cost = cost;
    new->next = graph[cityID_1].next;
    graph[cityID_1].next = new;
}

void initialize_adjMatrix(){
    for(int i=0; i<cities_num; i++){
        for(int j=0; j<cities_num; j++){
            if(i!=j)
                graph_Matrix[i][j] = MAX_COST;
            else
                graph_Matrix[i][j] = 0;
        }
    }
}

void make_adjList_adjMatrix() {
    char relation[(MAX_NAME * 2) + 2] = { 0 };
    int cityID_1, cityID_2;
    bool duplicate; //중복된 정보를 판단하기 위해
    adjLink temp; //중복된 정보를 판단하기 위해
    initialize_adjMatrix();

    printf("도시 간 도로 구축 상황을 입력하세요\n");
    while (1) {
        scanf("%s", relation);
        if (!strcmp(relation, ".")) break; //도시 구축 정보 입력 완료
        cityID_1 = search_BST(treeHead, strtok(relation, "-"));
        cityID_2 = search_BST(treeHead, strtok(NULL, "-"));
        if (cityID_1 == -1 || cityID_2 == -1) { //존재하지 않는 도시 이름이 입력된 경우
            printf("도시 이름이 잘못 입력되었습니다\n");
            continue;
        }
        temp = graph[cityID_1].next;
        duplicate = false;
        while (temp) {//현재까지 만들어진 adjacency list에서 입력된 도시를 이미 가지고 있는지 확인
            if (temp->cityID == cityID_2) {
                duplicate = true;
                break;
            }
            temp = temp->next;
        }
        if (duplicate == true) {
            printf("중복된 정보입니다\n");
            continue;
        }
        int cost = atoi(strtok(NULL, " "));
        add_adjList(cityID_1, cityID_2, cost); //adjacency List에 추가
        graph_Matrix[cityID_1][cityID_2] = cost; //adjacency Matrix에 추가
    }
    printf("도시 간 도록 구축 데이터베이스를 만들었습니다\n");
}

void free_list(adjLink now) {
    adjLink prev;
    while (now) {
        prev = now;
        now = now->next;
        free(prev);
    }
}
void free_BST(treePointer node) {
    if (node) {
        free_BST(node->leftChild);
        free_BST(node->rightChild);
        free(node);
    }
    return;
}
void reset() {
    if (cities_num == 0) //이미 초기화 된 상태
        return;
    free_BST(treeHead);
    treeHead = NULL;
    for (int i = 0; i < cities_num; i++)
        free_list(graph[i].next);
    cities_num = 0;
}

/*
9

ef ab kl gh cd ij mn lp qu

ab-cd-10
ab-ef-19
ef-kl-2
kl-ij-21
cd-gh-7
gh-ij-6
ab-kl-23
mn-kl-13
ab-mn-5
gh-ef-5
lp-qu-10
.


5

0 1 2 3 4

0-1-6
0-3-7
1-2-5
1-3-8
1-4--4
2-1--2
3-2--3
3-4-9
4-0-2
4-2-7
.

*/