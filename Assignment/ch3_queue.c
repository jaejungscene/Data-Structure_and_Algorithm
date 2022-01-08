#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_USER 5
#define MAX_NAME 20

typedef struct User{
    char name[MAX_NAME+1];
}User;

User UserInfo[MAX_USER+1];
int front = 0;
int rear = 0;
int userNum = 0;

void addUser();
void deleteUser();
int main(){
    int temp = 0;

    while(1){
        printf("진료 관리 서비스에 오신 것을 환영합니다. 원하는 기능의 번호를 선택해 주세요.\n");
        printf("1.병원 도착  2.진료 완료  3.서비스 종료\n");
        scanf("%d", &temp);

        if(temp == 1)
            addUser();
        else if(temp == 2)
            deleteUser();
        else if(temp == 3)
            break;
        else {
            printf("번호를 잘못 입력하셨습니다.\n");
            printf("---------------\n");
        }
    }
    printf("서비스를 종료합니다.\n");
    printf("감사합니다.\n");

    return 0;
}

void deleteUser(){
    if(userNum == 0){
        printf("대기 중인 환자가 없습니다.\n");
    }
    else if(userNum == 1){
        front = (front+1)%(MAX_USER+1);
        memset(UserInfo[front].name,0,sizeof(UserInfo[front].name));
        printf("대기 중인 환자가 없습니다.\n");
        userNum = userNum - 1;
    }
    else{
        front = (front+1)%(MAX_USER+1);
        memset(UserInfo[front].name,0,sizeof(UserInfo[front].name));
        printf("%s 님이 진료 대기 입니다.\n", UserInfo[(front+1)%(MAX_USER+1)].name);
        userNum = userNum - 1;    
    }
    printf("감사합니다.\n");
    printf("---------------\n");
}

void addUser(){
    int temp = 0;
    char name[MAX_NAME+1] = {0};

    if(userNum == MAX_USER){
        printf("새 진료 접수가 불가능합니다.\n");
    }
    else{
        while(1){
        printf("현재 대기자 수는 %d명입니다. 다음에서 원하는 기능의 번호를 선택해 주세요.\n", userNum);
            printf("1.대기자 등록  2.취소\n");
            scanf("%d", &temp);

            if (temp == 1){
                rear = (rear + 1) % (MAX_USER + 1);
                printf("대기자의 이름을 입력해 주세요: ");
                scanf("%s", UserInfo[rear].name);
                userNum++;
                break;
            }
            else if (temp == 2){
                break;
            }
            else{
                printf("번호를 잘못 입력하셨습니다.\n");
            }
        }
    }
    printf("감사합니다.\n");
    printf("---------------\n");
}