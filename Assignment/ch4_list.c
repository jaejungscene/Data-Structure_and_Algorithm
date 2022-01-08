#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(a, b) a = (listPointer)malloc(b);
#define MAX_SIZE 30

typedef enum Result{True, False}Result; //result가 True이면 결과가 성공적으로 도출되었다는 의미

typedef struct listNode* listPointer;
typedef struct listNode{
    int data;
    listPointer link;
}listNode;

char get_request();
void add_data(listPointer* start, listPointer* avail);
Result add_data_process(listPointer* start, listPointer temp);
void delete_data(listPointer* start, listPointer *avail);
void result_print(char request, Result result); //a,d만이 해당
void order_Allprint(listPointer first);
void reverse_Allprint(listPointer first);
void all_free(listPointer first);

// void test(listPointer avail){ //extra(확인을 위해 avail list 출력)
//     int count=0;
//     if(avail==NULL){
//         printf("avail List가 비어있습니다.\n");
//         return;
//     }
//     while(avail!=NULL){
//         count++;
//         printf("%d  ",avail->data);
//         avail = avail->link;
//     }
//     printf("(%d개)\n", count);
// }

int main(void){
    listPointer first=NULL, avail=NULL;
    char request;

    while(1){
        request = get_request();
        if(request == 'a')
            add_data(&first, &avail);
        else if(request == 'd')
            delete_data(&first, &avail);
        else if(request == 'p')
            order_Allprint(first);
        else if(request == 'r')
            reverse_Allprint(first);
        else if(request == 'q')
            break;
        // else if(request == 's') //extra (확인을 위해 avail list 출력)
        //     test(avail);
        else
            printf("이해할 수 없는 명령어 입니다.\n");
        printf("\n------------------------\n\n");
    }
    all_free(first);
    all_free(avail);
    printf("프로그램을 종료합니다. 감사합니다.\n");

    return 0;
}

char get_request(){
    char str[5];
    printf("*명령어를 입력하세요\n");
    printf("(a: 데이터 추가, d: 데이터 삭제, p: 정순 출력, r: 역순 출력, q: 종료)\n");
    scanf("%s", str);
    if(strlen(str)==1)
        return str[0];
    else   
        return '\0';
}

void add_data(listPointer* start, listPointer* avail){
    Result result;
    listPointer temp;

    if((*avail)==NULL){
        MALLOC(temp, sizeof(*temp));
        result = add_data_process(start, temp);
    }
    else{
        temp = (*avail);
        (*avail) = (*avail)->link;
        result = add_data_process(start, temp);
        if(result == False){//avail에서 빌린 값을 다시 복구
            temp->link =(*avail);
            (*avail) = temp;
        }
    }
    result_print('a', result);
}

Result add_data_process(listPointer* start, listPointer temp){
    Result result;
    printf("추가할 데이터를 입력하세요:");
    scanf("%d", &(temp->data));
    if((*start)==NULL){ //list에 어떤 chain도 없을 경우
        result = True;
        temp->link = (*start);
        (*start) = temp;
    }
    else{
        listPointer now = (*start);
        listPointer prev = (*start);
        while(now!=NULL && now->data < temp->data){
            prev = now;
            now = now->link;
        }
        if(now!=NULL && now->data==temp->data){ //list 내에 같은 데이터가 있을 경우
            result = False;
        }
        else{ //list내에 정상적으로 데이터를 넣는 경우
            result = True;
            temp->link = now;
            if(prev==now)//temp가 list에서 가장 작은 값인 경우
                (*start) = temp;
            else //일반적인 경우
                prev->link = temp;
        }
    }
    return result;
}

void delete_data(listPointer* start, listPointer *avail){
    Result result;
    int data;
    listPointer now = (*start);
    listPointer prev = (*start);
    if((*start)==NULL){ //함수 종료
        printf("List가 비어있습니다.\n");
        return;
    }
    printf("삭제할 데이터를 입력하세요:");
    scanf("%d", &data);
    while(now!=NULL && (now->data)!=data){
        prev = now;
        now = now->link;
    }
    if(now==NULL){//list에 삭제할 데이터가 없을 경우
        result = False;
    }
    else{//정상적으로 list에서 데이터가 삭제될 경우
        result = True;
        if(prev==(*start) && now==(*start)){ //
            if(now->link==NULL){ //list에 데이터가 하나밖에 없을 경우
                now->link = (*avail);
                (*avail) = now;
                (*start) = NULL;
            }
            else{//list의 시작 노드가 바뀌하는 경우
                (*start) = now->link;
                now->link = (*avail);
                (*avail) = now;
            }
        }
        else{//일반적인 경우
            prev->link = now->link;
            now->link = (*avail);
            (*avail) = now;
        }
    }
    result_print('d',result);
}

void result_print(char request, Result result){
    if(result == True){ //a,d 상관없이
        printf("성공했습니다.\n");
    }
    if(request == 'a' && result == False){
        printf("중복된 데이터입니다.\n");
    }
    if(request == 'd' && result == False){
        printf("해당하는 데이터가 없습니다.\n");
    }
}

void order_Allprint(listPointer first){
    if(first==NULL){//함수 종료
        printf("List가 비어있습니다.\n");
        return;
    }
    while(first!=NULL){
       printf("%d  ",first->data);
       first = first->link;
    }
    printf("\n");
}

void reverse_Allprint(listPointer first){
    int stack[MAX_SIZE];
    int top=0;
    if(first==NULL){//함수 종료
        printf("List가 비어있습니다.\n");
        return;
    }
    while(first!=NULL && top<MAX_SIZE){
        stack[top] = first->data;
        first = first->link;
        top++;
    }
    while(top>0){
        top--;
        printf("%d  ", stack[top]);
    }
    printf("\n");
}

void all_free(listPointer first){
    listPointer temp;
    if (first != NULL){
        temp = first->link;
        while(1){
            free(first);
            first = temp; 
            if(temp==NULL){break;}
            temp = temp->link;
        }
    }
}