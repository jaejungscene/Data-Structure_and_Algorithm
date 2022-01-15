#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node* treePointer;
typedef struct node{
  char data;
  treePointer leftChild, rightChild;
}node;

void inorder(treePointer ptr){//LVR
  if(ptr){
    inorder(ptr->leftChild);
    printf("%c", ptr->data);
    inorder(ptr->rightChild);
  }
  return;
}

void preorder(treePointer ptr){//VLR
  if(ptr){
    preorder(ptr->leftChild);
    preorder(ptr->rightChild);
    printf("%c", ptr->data);
  }
  return;
}

void postorder(treePointer ptr){//LRV
  if(ptr){
    printf("%c", ptr->data);
    postorder(ptr->leftChild);
    postorder(ptr->rightChild);
  }
  return;
}

treePointer treeHead;

int main(){
  treeHead = (treePointer)malloc(sizeof(node));
  treeHead->data = 'a';
  printf("%c\n", treeHead->data);
}

/*
in : 7+5*2-8/4
pre : -+7*52/84
post : 752*+84/-

a*(b+c-d)%e  -->  abc+d-*e%
*/