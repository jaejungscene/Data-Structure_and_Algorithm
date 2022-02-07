#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_INPUT 20

typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
  bool leftThread; /* TRUE if leftChild is thread */
  threadedPointer leftChild;
  char data;
  threadedPointer rightChild;
  bool rightThread; /* TRUE if rightChild is thread */ 
}threadedTree;

threadedPointer root;

threadedPointer getNode(char data){
  threadedPointer temp = (threadedPointer)malloc(sizeof(threadedTree));
  temp->data = data;
  temp->leftChild = NULL;
  temp->leftThread = false; 
  temp->rightChild = NULL;
  temp->rightThread = false;
  return temp;
}

void iterInsert(threadedPointer node){
  threadedPointer prev = root, now;
  bool left_right = true; //left==true  right==false
  now = prev->leftChild;
  while(!(prev->leftThread==true && left_right==true) && !(prev->rightThread==true && left_right==false)){
    if(now->data < node->data){
      prev = now;
      now = now->rightChild;
      left_right = false;
    }
    else{
      prev = now;
      now = now->leftChild;
      left_right = true;
    }
  }
  if(left_right){
    node->leftChild = prev->leftChild;
    node->leftThread = prev->leftThread;
    prev->leftChild = node;
    prev->leftThread = false;
    node->rightThread = true;
    node->rightChild = prev;
  }
  else{
    node->rightChild = prev->rightChild;
    node->rightThread = prev->rightThread;
    prev->rightChild = node;
    prev->rightThread = false;
    node->leftThread = true;
    node->leftChild = prev;
  }
}

void createTree(){
  char input[MAX_INPUT];
  printf("%s\n", input);
  printf("Enter sequence (tree's made by method of inserting of BST)\n");
  scanf("%s", input);
  threadedPointer new;
  for(int i=0; i<strlen(input); i++){
    new = getNode(input[i]);
    iterInsert(new);
  }
}

void inorder(threadedPointer ptr){//LVR
  if(ptr->leftThread==false)
    inorder(ptr->leftChild);
  else
    printf("%3c", (ptr->leftChild)->data);
  printf("%c", ptr->data);
  if(ptr->rightThread==false)
    inorder(ptr->rightChild);
  else
    printf("%-3c", (ptr->rightChild)->data);

  return;
}

threadedPointer insucc(threadedPointer tree)
/* find the inorder successor of tree in a threaded binary tree */{
  threadedPointer temp;
  temp = tree->rightChild;
  if (!tree->rightThread){ /* normal link */
    while (!temp->leftThread)
      temp = temp->leftChild;
  }
  return temp;
}

void tinorder(threadedPointer tree)
/* traverse the threaded binary tree inorder */ {
   threadedPointer temp = tree;
   for (;;) {
      temp = insucc(temp);
      if (temp == tree) break;
      printf("%3c", temp->data);
} }

void freeTree(threadedPointer now){
  if(now->leftThread == false)
    freeTree(now->leftChild);
  if(now->rightThread == false)
    freeTree(now->rightChild);
  free(now);
}

int main(){
  root = (threadedPointer)malloc(sizeof(threadedTree));
  root->data = '@';
  root->leftChild = root; root->leftThread = true; //처음에 노드를 추가할 때 편리하게 하기 위해
  root->rightChild = root; root->rightThread = false;

  createTree();

  printf("--- tinorder ---\n");
  tinorder(root->leftChild);
  printf("\n--- inorder ---\n");
  inorder(root->leftChild);

  freeTree(root->leftChild);
  free(root);
}

/*
EACBDGF
      (root == @)
          /
        E
    /       \
  /           \
A               G
  \           /
    \       F
      C     
    /   \
  B       D

*/