#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CITIES 20
#define MAX_NAME 10
#define INT_MAX 2147483647

typedef struct adjNode* adjLink;
typedef struct adjNode {
    short cityID;
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
    short cityID;
    treePointer leftChild;
    treePointer rightChild;
} treeNode;

//function frame
void input_cities();
treePointer newNode(int k);
treePointer insert(treePointer node, int k);
void make_BST();
short search_BST(treePointer node, char* cityName);
void add_adjList(short cityID_1, short cityID_2, int cost);
void make_adjacency_list();
void shortestPath(short start, int distance[], short pi[]);
short choose(int distance[], bool found[]);
void print_path(short s, short e, int distance[], short pi[]);
void search_shortest_path();
void free_BST(treePointer node);
void free_list();
void reset();

//global variable
short cities_num = 0;
basisNode graph[MAX_CITIES] = { 0 };
treePointer treeHead = NULL;

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
            make_adjacency_list();
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
    new->cityID = (short)k;
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

short search_BST(treePointer node, char* cityName) {
    if (!node) return -1; //tree에 입력받은 cityName이 없는 경우
    if (!strcmp(cityName, graph[node->cityID].cityName))//tree에서 입력받은 cityName을 찾을 경우
        return node->cityID;
    if (strcmp(cityName, graph[node->cityID].cityName) < 0)
        return search_BST(node->leftChild, cityName);
    else
        return search_BST(node->rightChild, cityName);
}

void add_adjList(short cityID_1, short cityID_2, int cost) {
    adjLink new_1 = (adjLink)malloc(sizeof(*new_1));
    adjLink new_2 = (adjLink)malloc(sizeof(*new_2));

    new_1->cityID = cityID_1;
    new_1->cost = cost;
    new_1->next = graph[cityID_2].next;
    graph[cityID_2].next = new_1;

    new_2->cityID = cityID_2;
    new_2->cost = cost;
    new_2->next = graph[cityID_1].next;
    graph[cityID_1].next = new_2;
}

void make_adjacency_list() {
    char relation[(MAX_NAME * 2) + 2] = { 0 };
    short cityID_1, cityID_2;
    bool duplicate; //중복된 정보를 판단하기 위해
    adjLink temp; //중복된 정보를 판단하기 위해

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
        add_adjList(cityID_1, cityID_2, atoi(strtok(NULL, " "))); //adjacency List에 추가
    }
    printf("도시 간 도록 구축 데이터베이스를 만들었습니다\n");
}

short choose(int distance[], bool found[]) {
    int i, min = INT_MAX, minpos = -1;
    for (i = 0; i < cities_num; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void shortestPath(short v, int distance[], short pi[]) {
    short i, u, w;
    bool found[MAX_CITIES];
    adjLink temp = graph[v].next;

    for (int i = 0; i < cities_num; i++) {
        found[i] = false;
        pi[i] = -1;
        distance[i] = INT_MAX; //INT_MAX == 2147483647
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

void print_path(short s, short e, int distance[], short pi[]) {
    short stack[MAX_CITIES - 2];
    short top = 0, temp = e;
    while (s != pi[temp]) {
        stack[top] = pi[temp];
        top++;
        temp = pi[temp];
    }
    printf("%s-", graph[s].cityName);
    top--;
    while (top >= 0) {
        printf("%s-", graph[stack[top]].cityName);
        top--;
    }
    printf("%s-", graph[e].cityName);
    printf("%d\n", distance[e]);
}

void search_shortest_path() {
    char cityName[MAX_NAME + 1];
    short distance[MAX_CITIES], pi[MAX_CITIES];
    short start, destination;

    while (1) {
        printf("출발 도시 이름을 입력하세요.\n");
        scanf("%s", cityName);
        start = search_BST(treeHead, cityName);
        if (start == -1) {
            printf("잘못된 도시 이름입니다\n");
            continue;
        }
        shortestPath(start, distance, pi);
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
        if (pi[destination] == -1) {
            printf("경로가 없습니다\n");
            continue;
        }
        print_path(start, destination, distance, pi);
    }
    printf("**검색을 종료합니다\n");
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

*/