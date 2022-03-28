// soft linked  ../Sorting/Mege_Sort.c  -> ../Divide_and_Conquer/Merge_sort.c

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_INT 2147483647

void Merge(int A[], int p, int q, int r){
  int n1 = (q-p) + 1;
  int n2 = (r-q);
  int i; int j;
  int* L = (int*)malloc(sizeof(int)*(n1+2));
  int* R = (int*)malloc(sizeof(int)*(n2+2));
  for(i=1; i<=n1; i++)  L[i] = A[(p+i)-1];
  for(j=1; j<=n2; j++)  R[j] = A[q+j];
  L[n1+1] = MAX_INT;
  R[n2+1] = MAX_INT;
  i = 1; j = 1;
  
  for(int k=p; k<=r; k++){
    if(L[i]<R[j]){
      A[k] = L[i];
      i++;
    }
    else{
      A[k] = R[j];
      j++;
    }
  }

  free(L);
  free(R);
}

void MergeSort(int A[], int p, int r){
  if(p<r){
    int q = p + (r-p)/2;
    MergeSort(A, p, q);
    MergeSort(A, q+1, r);
    Merge(A, p, q, r);
  }
}

int main(){
  int A[] = {-10000,9,8,7,6,5,5,4,3,0,2,1}; 

  printf("before : ");
  for(int i=1; i<=11; i++)
    printf("%4d", A[i]);
  MergeSort(A,1,11);
  printf("\nafter  : ");
  for(int i=1; i<=11; i++)
    printf("%4d", A[i]);

  return 0;
}