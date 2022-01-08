#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(a, b) a = (treePointer)malloc(b);
#define MAX_INPUT 20

typedef enum nodeType{operator, operand, node_error}nodeType;
typedef enum inputType{normal, terminate, input_error}inputType;
typedef struct node* treePointer;
typedef struct node{
    char data;
    nodeType type;
    treePointer left;
    treePointer right;
}node;

nodeType match_data(char data);
inputType examin_expr(char *expr, int len);
treePointer createNode(char data);
treePointer createTree(char expr[]);
int calculation(treePointer ptr);
void free_tree(treePointer ptr);

void test_inorder_print(treePointer ptr){ //<-----------------test
    if(ptr){
        test_inorder_print(ptr->left);
        printf("%3c", ptr->data);
        test_inorder_print(ptr->right);
    }
    return;
}

int main(void){
    treePointer treeHead = NULL;
    char expr[MAX_INPUT+1] = {"+*ADE"};
    inputType exprType;

    while(1){
        printf("수식을 입력하시오(종료 시 q를 입력하시오):");
        scanf("%s", expr);
        exprType = examin_expr(expr, strlen(expr));

        if(exprType == input_error){
            printf("잘못된 문자를 사용하였습니다.\n\n");
        }
        else if(exprType == normal){
            int result = 0;
            treeHead = createTree(expr);
            result = calculation(treeHead);
            test_inorder_print(treeHead); //<-----------------------test
            printf("\n");                  //<-----------------------test
            printf("계산 결과는 %d입니다.\n\n", result);
            free_tree(treeHead);
        }
        else if(exprType == terminate){
            printf("프로그램을 종료합니다.\n");
            break;
        }
    }
    return 0;
}

nodeType match_data(char data){
    if(data=='+' || data=='-' || data=='*' || data=='/'){
        return operator;
    }
    else if('0'<= data && data<='9'){
        return operand;
    }
    else{
        return node_error;
    }
}

inputType examin_expr(char *expr, int len){ //expression이 정상적인 expression인지 검사
    if(expr[0]=='q' && len==1){
        return terminate;
    }
    int i, operatorNum=0, operandNum=0;
    for(i=0; i<len; i++){
        if(match_data(expr[i])==node_error){
            break;
        }
        if(match_data(expr[i])==operand){
            operandNum++;
        }
        if(match_data(expr[i])==operator){
            operatorNum++;
        }
    }
    if(i==len && (operatorNum+1)==operandNum)
    { //input값이 정상적일 경우(이항연산자 밖에 없으므로 정상적인 expression이라면 "operator개수+1"과 "operand개수"는 같아야 한다)
        return normal;
    }
    else { //input값이 이상한 값이 있을 경우
        return input_error;
    }
}

treePointer createNode(char data){
    treePointer temp;
    MALLOC(temp, sizeof(*temp));
    if(operator == match_data(data)){
        temp->type = operator;
    }
    else if(operand == match_data(data)){
        temp->type = operand;
    }
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int calculation(treePointer ptr){ //함수의 argument(tree)는 무조건 오류가 없는 정상적인 tree이다.
    if(ptr->type == operator){ //따라서 무조건 ptr->type은 operator 또는 operand이다.
        switch(ptr->data){
            case '+':
                return calculation(ptr->left) + calculation(ptr->right);
            case '-':
                return calculation(ptr->left) - calculation(ptr->right);
            case '*':
                return calculation(ptr->left) * calculation(ptr->right);
            case '/':
                return calculation(ptr->left) / calculation(ptr->right);
        }
    }
    else { //ptr->type == operand
        int data = ptr->data - '0';
        return data;
    }
}


treePointer createTree(char expr[]){ //함수의 argument(given expression)는 무조건 오류가 없는 정상적인 expression이다.
    treePointer ptr = createNode(*expr);
    if(ptr->type == operator){
        ptr->left = createTree(expr+1);
        if(match_data(*(expr+1)) == operand) //다음 번째 expression의 문자가 operand이면 
        {
            ptr->right = createTree(expr+2);
        }
        else //다음 번째 expression의 문자 operator이면
        { //이미 만들어진 left의 subtree에서 가장 오른쪽 문자에(leaf node) 다음 문자가 right child가 되어야 한다.
            treePointer subtree = ptr->left;
            while(subtree->right){
                subtree = subtree->right;
            }
            expr = expr+2;
            while(subtree->data != *(expr)){ //바로 다음 번째 expression의 문자는 이미 검증이된 상태
                expr = expr+1;
            }
            ptr->right = createTree(expr+1);
        }
        return ptr;
    }
    else { //ptr->type == operand
        return ptr;
    }
}

void free_tree(treePointer ptr){
    if(ptr){
        free_tree(ptr->left);
        free_tree(ptr->right);
        printf("free : %c\n", ptr->data); //<-------------------test
        free(ptr);
    }
    return;
}

/*

++3*426
-+*235/84
+7/-/*54264
*+27+45
*+-/62*1542

*/