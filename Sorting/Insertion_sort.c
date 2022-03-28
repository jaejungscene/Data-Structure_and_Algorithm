#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void Insertion_sort(int* A, int n){
  int key, i, j;
  for(j=1; j<n; j++){
    key = A[j];
    i = j-1;
    while(i>0 || A[i]>key){
      A[i+1] = A[i];
      i = i-1;
    }
    A[i+1] = key;
  }
}

void printer(int A[], int n){
  for(int i=0; i<n; i++){
    printf("%3d", A[i]);
  }
  printf("\n");
}

int main(){
  int A[11] = {9,8,7,6,5,5,4,3,2,1,0};
  printer(A, sizeof(A)/sizeof(A[0]));
  Insertion_sort(A, sizeof(A)/sizeof(A[0]));
  printer(A, sizeof(A)/sizeof(A[0]));
  return 0;
}