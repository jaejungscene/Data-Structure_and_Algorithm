#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_USER 20
#define MAX_INFO 45 // user 한명 당 입력될 문자의 크기에 대한 대략적인 한계값

typedef struct userType{
    enum type{customer, seller} type;
    union{//금액의 최대값을 일단 6자리 숫자(999999)로 정함
      int purchase;
      int sales;
    }u;
}userType;

typedef struct USER{
    char name[21]; //이름<=20
    char phoneNum[14]; //휴대폰번호(-포함)=13
    userType typeInfo;
}USER;

void printInfo(int count, USER user[]);
int main(){
    USER user[MAX_USER] = {0};
    char strBuf[MAX_INFO] = {0};
    int count = 0;//실제 입력된 총 user 수

    printf("고객 정보를 {<이름> <고객유형(대문자로)> <휴대폰번호(-와 함께)> <금액>} 이와 같은 형식으로 입력해 주십세요!\n\n");

    for(int i=0; i<MAX_USER; i++){//고객 생성
        fgets(strBuf, MAX_INFO, stdin); //마지막\n도 같이 옮겨준다.
        if(strBuf[0]=='-' && strBuf[1]=='-'){
            break;
        }

        char* token = strtok(strBuf, " ");//현재 token은 <고객이름>
        strncpy(user[i].name, token, 20);

        token = strtok(NULL, " ");//현재 token은 <고객유형>
        if(token[0] == 'C'){
            user[i].typeInfo.type = customer;
        }
        else if(token[0] == 'S'){
            user[i].typeInfo.type = seller;
        }

        token = strtok(NULL, " ");//현재 token은 <전화번호>
        strncpy(user[i].phoneNum, token, 13);
        
        token = strtok(NULL, " \n");//현재 token은 <금액>
        int size = strlen(token); //입력된 금액이 몇자리 숫자인지 저장
        if(user[i].typeInfo.type == customer){
            user[i].typeInfo.u.purchase = 0;
            for(int j=0; j<size; j++){ //문자로 입력된 금액(최대 6개의 문자)을 int형으로 전환하여 저장
                user[i].typeInfo.u.purchase += (token[j]-'0')*pow(10,size-j-1);
            }
        }
        else if(user[i].typeInfo.type == seller){
            user[i].typeInfo.u.sales = 0;
            for(int j=0; j<size; j++){ //문자로 입력된 금액(최대 6개의 문자)을 int형으로 전환하여 저장
                user[i].typeInfo.u.sales += (token[j]-'0')*pow(10,size-j-1);
            }
        }

        count++;
    }

    printInfo(count, user);
    
    printf("<<<<<<--system exit-->>>>>>\n");
    return 0;
}


void printInfo(int count, USER user[]){
    int temp = 0;

    
    int max_C = -1;
    int min_C = 1000000;//7자리
    int maxIndex_C = -1;
    int minIndex_C = MAX_USER;
    int typeCount_C = 0;//customer 고객 고객수(평균값 계산을 위해)
    double sum_C = 0;

    int max_S = -1;
    int min_S = 1000000;//7자리
    int maxIndex_S = -1;
    int minIndex_S= MAX_USER;
    int typeCount_S = 0;//seller 고객 고객수(평균값 계산을 위해)
    double sum_S = 0;//seller 고객들의 총 판매금액(평균값 계산을 위해)

    for(int i=0; i<count; i++){

        if(user[i].typeInfo.type == customer){
            typeCount_C++;
            temp = user[i].typeInfo.u.purchase;
            sum_C += (double)temp;
            if(max_C<=temp){//값이 값을 때는 나중에 나온 사람을 출력해주기위해 '=' 붙임
                max_C = temp;
                maxIndex_C = i;
            }
            if(min_C>=temp){//값이 값을 때는 나중에 나온 사람을 출력해주기위해 '=' 붙임
                min_C = temp;
                minIndex_C = i;
            }
        }

        if(user[i].typeInfo.type == seller){
            typeCount_S++;
            temp = user[i].typeInfo.u.sales;
            sum_S += (double)temp;
            if(max_S<=temp){//값이 값을 때는 나중에 나온 사람을 출력해주기위해 '=' 붙임
                max_S = temp;
                maxIndex_S = i;
            }
            if(min_S>=temp){//값이 값을 때는 나중에 나온 사람을 출력해주기위해 '=' 붙임
                min_S = temp;
                minIndex_S = i;
            }
        }
    }

    if(typeCount_C==0){ 
        printf("최저 구매자: (none)\n");
        printf("최대 구매자: (none)\n");
        printf("평균 구매액: 0.0\n");
    }
    else{
        printf("최저 구매자: %s %d\n", user[minIndex_C].name, min_C);
        printf("최대 구매자: %s %d\n", user[maxIndex_C].name, max_C);
        printf("평균 구매액: %.1f\n", sum_C/typeCount_C);
    }

    if(typeCount_S==0){ 
        printf("최저 판매자: (none)\n");
        printf("최대 판매자: (none)\n");
        printf("평균 판매액: 0.0\n");
    }
    else{
        printf("최저 판매자: %s %d\n", user[minIndex_S].name, min_S);
        printf("최대 판매자: %s %d\n", user[maxIndex_S].name, max_S);
        printf("평균 판매액: %.1f\n", sum_S/typeCount_S);
    }
}

/*   prof code
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_USERS 100
#define MAX_NAME_LEN 20
#define MAX_PHONE_LEN 14
#define TYPE_CONSUMER 'C'
#define TYPE_SELLER 'S'
#define MAX_STR 20
#define MIN_VAL 0
#define MAX_VAL 99999999

typedef union
{
    int purchase;
    int sales;
} bizRecord;

typedef struct
{
    char name[MAX_NAME_LEN];
    char type;
    char phone[MAX_PHONE_LEN];
    bizRecord record;
} User;

typedef struct
{
    int val;
    char name[MAX_NAME_LEN];
} UserInfo;

typedef struct
{
    int count;
    float average;
    UserInfo min_user;
    UserInfo max_user;
} Summary;

void print_record(User *p)
{
    printf("name %s ", p->name);
    printf("%c ", p->type);
    printf("%s ", p->phone);
    if (p->type == TYPE_SELLER)
        printf("%d\n", p->record.sales);
    else if (p->type == TYPE_CONSUMER)
        printf("%d\n", p->record.purchase);
    return;
}

int read_data(User *user_list)
{
    int size = 0;
    User *pUser;
    int val;
    char type;
    char name[MAX_NAME_LEN], phone[MAX_PHONE_LEN];

    pUser = user_list;
    printf("고객정보를 입력해 주세요 (<이름> <고객 유형> <전화번호> <금액>):\n");
    while (1)
    {
        if (size >= MAX_USERS)
        {
            printf("이 프로그램은 최대 %d명까지만 입력받을 수 있습니다.", MAX_USERS);
            break;
        }

        scanf("%s", name);
        if (strcmp(name, "--") == 0)
        {
            break;
        }
        else
        {
            strcpy(pUser->name, name);
        }

        scanf(" %c %s %d", &type, phone, &val);
        if (type != TYPE_CONSUMER && type != TYPE_SELLER)
        {
            printf("%c은 유효하지 않는 유저 타입입니다.", type);
        }
        else
        {
            size++;
            pUser->type = type;
            strcpy(pUser->phone, phone);
            if (type == TYPE_CONSUMER)
            {
                pUser->record.purchase = val;
            }
            else if (type == TYPE_SELLER)
            {
                pUser->record.sales = val;
            }
            // print_record(pUser);
            pUser++;
        }
    }
    return size;
}

void initialize_data(Summary *sum)
{
    strcpy(sum->min_user.name, "(none)");
    sum->min_user.val = MAX_VAL;
    strcpy(sum->max_user.name, "(none)");
    sum->max_user.val = MIN_VAL;
    sum->average = 0.0;
    return;
}

void process_data(User *users, int max_count, char type, Summary *summary)
{
    int i, j;
    User *pUser = users;
    int sum = 0, user_count = 0;

    for (i = 0; i < max_count; i++)
    {
        if (pUser->type == type && type == TYPE_CONSUMER)
        {
            if (pUser->record.purchase <= summary->min_user.val)
            {
                strcpy(summary->min_user.name, pUser->name);
                summary->min_user.val = pUser->record.purchase;
            }
            if (pUser->record.purchase >= summary->max_user.val)
            {
                strcpy(summary->max_user.name, pUser->name);
                summary->max_user.val = pUser->record.purchase;
            }
            sum += pUser->record.purchase;
            user_count++;
        }
        else if (pUser->type == type && type == TYPE_SELLER)
        {
            if (pUser->record.sales <= summary->min_user.val)
            {
                strcpy(summary->min_user.name, pUser->name);
                summary->min_user.val = pUser->record.sales;
            }
            if (pUser->record.sales >= summary->max_user.val)
            {
                strcpy(summary->max_user.name, pUser->name);
                summary->max_user.val = pUser->record.sales;
            }
            sum += pUser->record.sales;
            user_count++;
        }
        pUser++;
    }
    if (user_count)
    {
        summary->average = (float)sum / user_count;
    }
    else
    {
        summary->average = 0.0;
    }

    summary->count = user_count;
    return;
}

void print_results(Summary sum, char *msg)
{
    char announce[MAX_STR];
    memset(announce, 0, sizeof(announce));
    printf("%s%s%s %s ", "최소", msg, "자", sum.min_user.name);
    if (sum.count)
    {
        printf("%d\n", sum.min_user.val);
    }
    else
    {
        printf("\n");
    }
    printf("%s%s%s %s ", "최대", msg, "자", sum.max_user.name);
    if (sum.count)
    {
        printf("%d\n", sum.max_user.val);
    }
    else
    {
        printf("\n");
    }
    printf("%s%s%s %.1f\n", "평균", msg, "액", sum.average);
    return;
}

int main()
{

    Summary seller_sum, consumer_sum;
    int count;
    User users[MAX_USERS] = {0};

    initialize_data(&consumer_sum);
    initialize_data(&seller_sum);

    count = read_data(users);

    process_data(users, count, TYPE_CONSUMER, &consumer_sum);
    process_data(users, count, TYPE_SELLER, &seller_sum);

    print_results(consumer_sum, "구매");
    print_results(seller_sum, "판매");

    return 0;
}
*/



/* 
James S 010-2345-1237 58
Luke C 010-4245-8233 81
Rosemary C 010-8372-3237 39
George S 010-3325_4237 42
Allen C 010-2867-1242 34
--

James C 010-2345-1237 58
Luke C 010-4245-8233 81
Rosemary C 010-8372-3237 39
George C 010-3325_4237 42
Allen C 010-2867-1242 34
--

James S 010-2345-1237 58
Luke S 010-4245-8233 81
Rosemary S 010-8372-3237 39
George C 010-3325_4237 42
Allen S 010-2867-1242 34
--

James S 010-2345-1237 81
Luke S 010-4245-8233 80
Rosemary C 010-8372-3237 39
George C 010-3325_4237 42
Allen S 010-2867-1242 81
--
*/