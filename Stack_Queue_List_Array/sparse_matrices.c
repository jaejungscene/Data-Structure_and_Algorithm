/**
 * Sparse matrix is a matrix that increases spatial efficiency
 * by not representing zero parts of a matrix.
 * And this file suggests a code to improve transpose operation
 * of this kind of sparse matrix.
**/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_INPUT 100

typedef struct sparse_matrices
{
  int row;
  int col;
  int value;
}sparse_matrices;
sparse_matrices* head;

void fastTranspose(sparse_matrices a[]);
void make_sparse_matrices();
void print_sparse_matrices();
int main(){
  sparse_matrices a[9];
  int arr[9][3] = {
    {6,6,8},
    {0,0,15},
    {0,4,91},
    {1,1,11},
    {2,1,3},
    {2,5,28},
    {3,0,22},
    {3,2,-6},
    {5,0,-15},
  };
  for(int i=0; i<9; i++){
    a[i].row = arr[i][0];
    a[i].col = arr[i][1];
    a[i].value = arr[i][2];
  }
  fastTranspose(a);
  for(int i=0; i<9; i++){
    printf("[%d] %d %d %d\n", i, a[i].row, a[i].col, a[i].value);
  }

  // make_sparse_matrices();
  // print_sparse_matrices();
  // free(head);
  return 0;
}

void fastTranspose(sparse_matrices a[]){
  sparse_matrices b[9];
  for(int i=0; i<9; i++){
    b[i].row = a[i].row;
    b[i].col = a[i].col;
    b[i].value = a[i].value;
  }

  int numCols = a[0].col, numTerms = a[0].value;
  int rowTerms[MAX_INPUT]={0}, startingPos[MAX_INPUT]={0};
  int position;
  for(int i=1; i<=numTerms; i++) { rowTerms[a[i].col]++;}
  startingPos[0] = 1;
  for(int i=1; i<numTerms; i++) { startingPos[i] = startingPos[i-1]+rowTerms[i-1]; }
  a[0].row = b[0].col;
  a[0].col = b[0].row;
  for(int i=1; i<=numTerms; i++){
    position = startingPos[b[i].col];
    startingPos[b[i].col]++;
    a[position].row = b[i].col;
    a[position].col = b[i].row;
    a[position].value = b[i].value;
  }
}


void make_sparse_matrices(){
  char input[MAX_INPUT];
  printf("---------enter---------\n");
  scanf("%[^.]s",input);
  int i=0;
  bool flag = false;
  int value_count = 0;
  int row_count = 0;
  int col_count = 0;
  while(input[i]){
    if('0'<input[i] && input[i]<='9' && flag==false){
      value_count++;
      flag = true;
    }
    else {
      flag = false;
    }
    i++;
  }
  head = (sparse_matrices*)malloc(sizeof(sparse_matrices)*(value_count+1));
  char* token = input;
  int temp;
  i=1;
  for(int j=0; input[j]; j++){
    if(input[j]=='\n'){
      input[j] = '\0';
      temp = j+1;
      break;
    }
  }
  while(*token != '\0'){
    char* token1 = strtok(token, " ");
    col_count = 0;
    while(token1){
      if(atoi(token1)!=0){
        head[i].row = row_count;
        head[i].col = col_count;
        head[i].value = atoi(token1);
      }
      col_count++;
      token1 = strtok(NULL, " ");
    }
    row_count++;
    token = &input[temp];
    for(int j=temp; input[j]; j++){
      if(input[j]=='\n'){
        input[j] = '\0';
        temp = j+1;
        break;
      }
    }
  }
  printf("qwjker");
  head[0].value = value_count;
  head[0].row = row_count;
  printf("alksjfd");
  head[0].col = col_count;
  printf("aksdf");
}

void print_sparse_matrices(){
  for(int i=0; i<head[0].value; i++){
    printf("[%d] %d  %d  %d", i, head[i].row, head[i].col, head[i].value);
  }
}


/*
15  0  0  0  91 0
0   11 0  0  0  0
0   3  0  0  0  28
22  0  -6 0  0  0
0   0  0  0  0  0
-15 0  0  0  0  0
.


a[0] 6 6 8
a[1] 0 0 15
a[2] 0 3 22
a[3] 0 5 -15
a[4] 1 1 11
a[5] 1 2 3
a[6] 2 3 -6
a[7] 4 0 91
a[8] 5 2 28
*/