#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_VERTIECS 30

int parent[MAX_VERTIECS];

void initialize(){
  for(int i=0; i<MAX_VERTIECS; i++)
    parent[i] = -1;
}

void SimpleUnion(int i, int j){
  parent[i] = j;
}

int SimpleFind(int i){
  for(; parent[i]>=0; i=parent[i]);
  return i;
}

void weightedUnion(int i, int j){
  //if the number of nodes in tree i is less than the number in tree j then make j the parent of i
  if (parent[i] < 0 && parent[j] < 0){
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j]){
      parent[i] = j; // make j the new root
      parent[j] = temp;
    }
    else{
      parent[j] = i; // make i the new root
      parent[i] = temp;
    }
  }
  else
    weightedUnion(SimpleFind(i), SimpleFind(j));
}

int collapsingFind(int i){
  //if j is a node on the path from i to its root then make j a child of the root
  //purpose : Compressing the tree and reduce the time complexity of "find" operation
  int root, trail, lead;
  for(root = i; parent[root]>=0; root = parent[root]);
  for(trail = i; trail!=root; trail=lead){
    lead = parent[trail];
    parent[trail] = root;
  }return root;
}

void print(){
  for(int i=0; i<MAX_VERTIECS; i++)
    printf("%4d", parent[i]);
  printf("\n");
}

int main(void){
  initialize();

  weightedUnion(0,5);
  print();
  weightedUnion(2,3);
  print();
  weightedUnion(3,5);
  print();

  printf("\n\n");
  parent[0] = -8;
  parent[1] = 7;
  parent[2] = 7;
  parent[3] = 2;
  parent[4] = 0;
  parent[5] = 2;
  parent[6] = 0;
  parent[7] = 0;
  int temp = collapsingFind(5);
  print();


  return 0;
}