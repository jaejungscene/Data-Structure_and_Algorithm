#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//절대 삭제하지 마세요. 중요한 코드!!!!!!!!!!
#define INPUT_STREAM_CLEAR int c; while ((c = getchar()) != '\n' && c != EOF){}
////////////////////////////////////

#define SIZE 10000
float data[SIZE][SIZE];
int main(){
  int i, j;
  float sum;
  clock_t before;
  double result;

  for(i=0; i<SIZE; i++)
    for(j=0; j<SIZE; j++)
      data[i][j] = i*j;

  sum = 0.0;
  before = clock();
  for(i=0; i<SIZE; i++)
    for(j=0; j<SIZE; j++)
      sum += data[i][j];
  result = (double)(clock()-before) / CLOCKS_PER_SEC;
  printf("Processing Time : %7.5f\n", result);

  sum = 0.0;
  before = clock();
  for(j=0; j<SIZE; j++)
    for(i=0; i<SIZE; i++)
      sum += data[i][j];
  result = (double)(clock()-before) / CLOCKS_PER_SEC;
  printf("Processing Time : %7.5f\n", result);

  return 0;
}