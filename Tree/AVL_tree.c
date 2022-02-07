#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "tree_printer.h"

// Create Node
// typedef struct Node {
//   int key;
//   struct Node *left;
//   struct Node *right;
//   int height;
// }Node;

// Calculate height
int height(Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Create a node
Node *newNode(int key) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1; //처음엔 무조건 1
  return (node);
}

// Right rotate
Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate
Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
Node *insertNode(Node *node, int key) {
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL)
    return newNode(key);

  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left),height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && key < node->left->key) //LL rotation과 같다.
    return rightRotate(node);

  if (balance < -1 && key > node->right->key) //RR rotation과 같다.
    return leftRotate(node);

  if (balance > 1 && key > node->left->key) { //LR rotation과 같다.
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) { //RL rotation과 같다.
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

Node *minValueNode(Node *node) {
  Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

// Delete a nodes
Node *deleteNode(Node *root, int key) {
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      Node *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    }
    else {
      Node *temp = minValueNode(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

// Print the tree
void printPreOrder(Node *root) {
  if (root) {
    printf("(%d,%d) ", root->key, root->height);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

void freeTree(Node* now){
  if(now){
    freeTree(now->left);
    freeTree(now->right);
    free(now);
  }
}

Node *root = NULL;
int main() {

  root = insertNode(root, 2);
  root = insertNode(root, 1);
  root = insertNode(root, 7);
  root = insertNode(root, 4);
  root = insertNode(root, 5);
  root = insertNode(root, 3);
  root = insertNode(root, 8);

  // printPreOrder(root);
  print2D(root);

  root = deleteNode(root, 3);

  printf("\nAfter deletion");
  // printPreOrder(root);
  print2D(root);
  freeTree(root);

  return 0;
}