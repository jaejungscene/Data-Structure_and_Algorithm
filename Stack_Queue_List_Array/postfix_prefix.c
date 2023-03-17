//핵심은 stack에는 우선순위가 높은 연산자가 위에 와야 한다는 것이다!
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define EXPR_SIZE 100

typedef enum {lparen, plus, minus, times, divide, mod, rparen, operand}precedence;
typedef struct Stack{
  char token;
  precedence value;
}Stack;
Stack stack[EXPR_SIZE]; int top = -1;
char expr[EXPR_SIZE];
char transExpr[EXPR_SIZE]; int n=0;
static int isp[] =  {0, 12, 12, 13, 13, 13}; //이미 stack에 들어가 괄호 안을 분석할 때는 '('의 우선순위가 가장 낮아 중요도가 가장 낮음. 
static int icp[] =  {20, 12, 12, 13, 13, 13};  //처음의 '('는 우선순위가 가장 높아 중요도가 가장 높음.


////////////////////////////////자료구조 강의자료에 교재 코드 확인////////////////////////////////////////
void push(char token, precedence value){
  top++;
  if(top >= EXPR_SIZE){
    top--;
    return;
  }
  stack[top].token = token;
  stack[top].value = value;
}

precedence getToken(char c){
  switch(c){
    case '(': return lparen; break;
    case ')': return rparen; break;
    case '+': return plus; break;
    case '-': return minus; break;
    case '*': return times;
    case '/': return divide; break;
    case '%': return mod; break;
    default : return operand; break;
  }
}

void makePostfix(){
  for(int i=0; expr[i]; i++){
    precedence value = getToken(expr[i]);
    if(value == operand){
      transExpr[n] = expr[i];
      n++;
    }
    else if(value == rparen){
      while(stack[top].value != lparen) { transExpr[n] = stack[top].token; n++; top--; }
      top--;
    }
    else{
      while(top>-1 && isp[stack[top].value] >= icp[value]) {
        transExpr[n] = stack[top].token;
        n++; top--;
      }
      push(expr[i],value);
    }
  }
  while(top>-1){
    transExpr[n] = stack[top].token;
    n++; top--;
  }
}
////////////////////////////////////////////////////////////////////////////////////////////


int evaluate_postfix(){
  int localStack[EXPR_SIZE];
  int localTop = -1; 
  for(int i=0; i<n; i++){
    if(getToken(transExpr[i]) == operand){
      localTop++;
      localStack[localTop] = transExpr[i]-'0';
    }
    else{
      int rear = localStack[localTop]; localTop--;
      int front = localStack[localTop];

      switch(transExpr[i]) {
        case '+': localStack[localTop] = front+rear; break;
        case '-': localStack[localTop] = front-rear; break;
        case '*': localStack[localTop] = front*rear; break;
        case '/': localStack[localTop] = front/rear; break;
        case '%': localStack[localTop] = front%rear; break;
      }
    }
  }
  return localStack[0];
}

int evaluate_prefix(int* num){
  char temp = transExpr[*num];
  (*num)++;
  if(getToken(temp) == operand){
    return temp-'0';
  }
  else{
    switch(temp) {
      case '+': return evaluate_prefix(num) + evaluate_prefix(num);
      case '-': return evaluate_prefix(num) - evaluate_prefix(num);
      case '*': return evaluate_prefix(num) * evaluate_prefix(num);
      case '/': return evaluate_prefix(num) / evaluate_prefix(num);
      case '%': return evaluate_prefix(num) % evaluate_prefix(num);
    }
  }
}

int main(){
  printf("Enter expression (without spaces)\n");
  scanf("%s", expr);
  makePostfix();
  printf("\n%s\n", transExpr);
  printf("reault : %d\n", evaluate_postfix());

  int k = 0;
  strcpy(transExpr, "-+7*52/84");
  k = evaluate_prefix(&k);
  printf("\n%s\nresult : %d\n", transExpr, k);
}

/*
in : 7+5*2-8/4
pre : -+7*52/84
post : 752*+84/-

a*(b+c-d)%e  -->  abc+d-*e%
*/