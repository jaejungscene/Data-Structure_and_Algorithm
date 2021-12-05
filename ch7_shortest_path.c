#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CITIES 20
#define MAX_NAME 10

typedef struct adjNode* adjLink;
typedef struct adjNode{
    short cityID;
    adjLink next;
}adjNode;

typedef struct basisNode{
    char cityName[MAX_NAME+1];
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
bool input_cities();
treePointer newNode(int k);
treePointer insert(treePointer node, int k);
void make_BST();
short search_BST(treePointer node, char* cityName);
void add_adjList(short cityID_1, short cityID_2);
void make_adjacency_list();
void dfs(short cityID);
void connected_result();
void free_BST(treePointer node);
void free_list();
void reset();

//global variable
short cities_num = 0;
bool visited[MAX_CITIES] = {false};
basisNode graph[MAX_CITIES] = {0};
treePointer treeHead = NULL;

int main(void){
    printf("도시 간 최소 비용 경로 안내 서비스에 오신 것을 환영합니다.\n")
    while(1){
        printf("-----------------------\n원하는 기능을 선택하세요\n");
        if(input_cities()==false) break; //프로그램 종료
        make_BST();
        make_adjacency_list();
        connected_result();

        reset();
    }
    printf("서비스를 종료합니다\n");
    return 0;
}

bool input_cities(){
    char input[(MAX_CITIES*MAX_NAME)+MAX_CITIES];
    char* token;
    int count;
    while(1){
        printf("도시 수를 입력해 주세요\n");
        scanf("%d%*c", &cities_num);
        if(cities_num == 0) return false; //프로그램 종료 신호
        printf("도시 이름을 입력해 주세요\n");
        scanf("%[^\n]s", input);

        count = 0;
        token = strtok(input, " ");
        while(token){ //입력한 도시 수가 일치하는지 확인하면서, 동시에 ajacency list의 biasis가 되는 Node들을 넣는다.
            if(count < cities_num){
                strcpy(graph[count].cityName, token);
                graph[count].next = NULL;
            }
            count++;
            token = strtok(NULL, " ");
        }
        if(count == cities_num)
            break;
        else{
            if (count > cities_num)
                printf("제시된 도시 수보다 도시 이름의 갯수가 더 <많>습니다\n");
            else//count < cities_num
                printf("제시된 도시 수보다 도시 이름의 갯수가 더 <적>습니다\n");
            continue;
        }
    }
    return true;
}

treePointer newNode(int k){
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
    if ( strcmp(graph[k].cityName, graph[node->cityID].cityName) < 0 )
        node->leftChild = insert(node->leftChild, k);
    else
        node->rightChild = insert(node->rightChild, k);
    /* return the (unchanged) node pointer*/
    return node;
}

void make_BST(){
    for(int i=0; i<cities_num; i++){
        treeHead = insert(treeHead, i);
    }
}

short search_BST(treePointer node, char* cityName){
    if(!node) return -1; //tree에 입력받은 cityName이 없는 경우
    if(!strcmp(cityName, graph[node->cityID].cityName))//tree에서 입력받은 cityName을 찾을 경우
        return node->cityID;
    if(strcmp(cityName, graph[node->cityID].cityName) < 0)
        return search_BST(node->leftChild, cityName);
    else
        return search_BST(node->rightChild, cityName);
}

void add_adjList(short cityID_1, short cityID_2){
    adjLink new_1 = (adjLink)malloc(sizeof(*new_1));
    adjLink new_2 = (adjLink)malloc(sizeof(*new_2));

    new_1->cityID = cityID_1;
    new_1->next = NULL;
    new_1->next = graph[cityID_2].next;
    graph[cityID_2].next = new_1;

    new_2->cityID = cityID_2;
    new_2->next = NULL;
    new_2->next = graph[cityID_1].next;
    graph[cityID_1].next = new_2;
}

void make_adjacency_list(){
    char relation[(MAX_NAME*2)+2] = {0};
    char *token;
    short cityID_1, cityID_2;
    bool duplicate; //중복된 정보를 판단하기 위해
    adjLink temp; //중복된 정보를 판단하기 위해

    printf("도시 간 도로 구축 상황을 입력하세요\n");
    while(1){
        scanf("%s", relation);
        if(!strcmp(relation, ".")) break; //도시 구축 정보 입력 완료
        token = strtok(relation, "-");
        cityID_1 = search_BST(treeHead, token);
        token = strtok(NULL, " ");
        cityID_2 = search_BST(treeHead, token);
        if(cityID_1 == -1 || cityID_2 == -1){ //존재하지 않는 도시 이름이 입력된 경우
            printf("도시 이름이 잘못 입력되었습니다\n");
            continue;
        }
        temp = graph[cityID_1].next;
        duplicate = false;
        while(temp){//현재까지 만들어진 adjacency list에서 중복된 값이 있는지 확인
            if(temp->cityID == cityID_2){//중복된 값이 존재할 경우
                duplicate = true;
                break;
            }
            temp = temp->next;
        }
        if(duplicate == true){
            printf("중복된 정보입니다\n");
            continue;
        }
        add_adjList(cityID_1, cityID_2); //adjacency List에 추가
    }
}

void dfs(short cityID){
    adjLink nextLink;
    visited[cityID] = true;
    printf("%s ", graph[cityID].cityName);
    for(nextLink = graph[cityID].next; nextLink; nextLink = nextLink->next){
        if(!visited[nextLink->cityID])
            dfs(nextLink->cityID);
    }
}

void connected_result(void){
    int connection_num = 0;
    short cityID_num[MAX_CITIES] = {0};
    for(int i=0; i<cities_num; i++){
        if(!visited[i]){
            if(i>0) printf("  ,  ( ");
            else    printf("( ");
            dfs(i);
            printf(")");
            cityID_num[connection_num] = (short)i;
            connection_num++;
        }
    }
    if(connection_num > 1){
        printf(" 로 분리됩니다\n");
        printf("이 도로 구축은 전체 도시들을 연결하지 못하고 있습니다\n다음의 도로를 추천합니다\n");
        for(int i=0; i<connection_num-1; i++){
            printf("%s-%s\n", graph[cityID_num[i]].cityName, graph[cityID_num[i+1]].cityName);
        }
    }
    else{
        printf("\n성공적인 도로 구축 계획입니다\n");
    }
}

void free_list(adjLink now){
    adjLink prev;
    while(now){
            prev = now;
            now = now->next;
            free(prev);
    }
}

void free_BST(treePointer node){
    if(node){
        free_BST(node->leftChild);
        free_BST(node->rightChild);
        free(node);
    }
    return;
}

void reset(){
    free_BST(treeHead);
    treeHead = NULL;
    for(int i=0; i<cities_num; i++){
        free_list(graph[i].next);
        visited[i] = false;
    }
    cities_num = 0;
}

/*
12

mn cd ab gh qr ef uv ij kl op st wx

ab-cd
wx-uv
st-uv
mn-kl
cd-ef
wx-op
mn-ij
ab-kl
cd-kl
uv-qr
op-qr
ef-gh
.
---------------
9

ZY XW TS VU RQ PO NM LK JI

NM-LK
ZY-XW
TS-ZY
PO-VU
ZY-TS

LK-JI
JI-NM
XW-TS
RQ-VU
PO-RQ
.
--------------
NM-LK
ZY-XW
TS-ZY
PO-VU
LK-JI
VU-NM
JI-NM
XW-TS
RQ-VU
PO-RQ
ZY-VU
.
*/