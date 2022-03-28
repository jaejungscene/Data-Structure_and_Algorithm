#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// pivot is end value of subarray
void swap(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int A[], int p , int r)
{
  int x = A[r];
  int i = p-1;
  int temp;
  for(int j=p; j<=r-1; j++)
  {
    if(A[j]<=x){
      i = i+1;
      swap(&A[j], &A[i]);
    }
  }
  swap(&A[r], &A[i+1]);
  return i+1;
}

void quick_sort(int A[], int p, int r)
{
  if(p < r){
    int q = partition(A, p, r);
    quick_sort(A, p, q-1);
    quick_sort(A, q+1, r);
  }
}

void printer(int A[], int n)
{
  for(int i=1; i<=n; i++){
    printf("%3d", A[i]);
  }
  printf("\n");
}

int main(){
  int A[12] = {-10000,9,8,7,6,5,5,4,3,2,1,0};
  printf("original array = ");
  printer(A,11);
  quick_sort(A, 1, 11);
  printf("sorted arrey   = ");
  printer(A, 11);
  return 0;
}