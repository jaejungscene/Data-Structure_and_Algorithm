#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define STR_MAX 50

//err1: 짝이 없는 첫 닫는괄호에 대한 변경사항 출력(shoud have been) -> errInfo에 두개 저장됨
//err2: 마지막에 남은 짝이 없는 닫는괄호들에 대한 오류 출력(redundnt) -> errInfo에 저장되는 개수 알 수 없음
//err3: 짝이 없는 상태로 열린 괄호가 끝났을 시(is not closed) -> errInfo에 저장되는 개수 알 수 없음
typedef enum Type{no_err, err1, err2, err3}Type;

typedef struct Result{
    Type type;
    char errInfo[STR_MAX+1];//err시 출력할 괄호에대한 정보를 갖는다.
}Result;

typedef struct Data{
    char str[STR_MAX+1];
    Result result;
}Data;

void get_str(Data* data);
char pair(char input);
void process_str(Data* data);
void print_result(Data* data);

int main(){
    Data data;

    while(1){
        get_str(&data);
        if(!strcmp(data.str,"q")){
            break;
        }
        process_str(&data);
        print_result(&data);
    }
    printf("** Bye");
    return 0;
}


void get_str(Data* data){
    memset(data->str, NULL, sizeof(data->str));
    memset(data->result.errInfo, NULL, sizeof(data->result.errInfo));
    data->result.type = 0;

    printf("input your string: ");
    scanf("%s", data->str);
}


char pair(char pair){
    switch(pair){
        case '(':
            pair = ')';
            break;
        case '{':
            pair = '}';
            break;
        case '[':
            pair = ']';
            break;
    }
    return pair;
}


void process_str(Data* data){
    char stack[STR_MAX+1] = {0};
    int top = -1;
    char temp[2] = {0};

    for(int i=0; i<strlen(data->str); i++){
        if(data->str[i]=='(' || data->str[i]=='{' || data->str[i]=='['){
            top++;
            stack[top] = data->str[i]; //push
        }
        else if(data->str[i]==')' || data->str[i]=='}' || data->str[i]==']'){
            if(data->str[i] == pair(stack[top])){ //no_err
                stack[top] = NULL; //pull
                top--;
            }
            else if(stack[0] == NULL){ //detect err2
                if(data->result.type!=err2) //불필요한 중복 금지
                    data->result.type = err2;
                temp[0] = data->str[i]; //strcat()함수 활용을 위해
                strcat(data->result.errInfo, temp);
            }
            else{ //detect err1
                data->result.type = err1;
                data->result.errInfo[0] = data->str[i];
                data->result.errInfo[1] = pair(stack[top]);
                break;
            }
        }
    }
    if(stack[0]!=NULL && data->result.type==no_err){ //detect err3
        data->result.type = err3;
        strcpy(data->result.errInfo, stack);
    }
}


void print_result(Data* data){
    switch (data->result.type)
    {
    case no_err:
        printf("Your string is balanced.\n\n");
        break;
    case err1:
        printf("Your is not balanced. \'%c\' should have been \'%c\'.\n\n", data->result.errInfo[0], data->result.errInfo[1]);
        break;
    case err2:
        if(strlen(data->result.errInfo)>=2)
            printf("Your is not balanced. \"%s\" are redundant.\n\n", data->result.errInfo);
        else
            printf("Your is not balanced. \'%c\' is redundant.\n\n", data->result.errInfo[0]);
        break;
    case err3:
        if(strlen(data->result.errInfo)>=2)
            printf("Your is not balanced. \"%s\" are not closed.\n\n", data->result.errInfo);
        else
            printf("Your is not balanced. \'%c\' is not closed.\n\n", data->result.errInfo[0]);
    }
}

/*
hello{this}(parenthesis(is)good)
(hello{this}(parenthesis(is)good))
[g{o}ose)
[g{oo)d]}
[g{o(od)day}]}
[g{o(od)day}]}]]]
[g{o(od)day}
[{[g{o(od)day}
hello}
hello{
*/