#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
  int key;
  struct Node *left;
  struct Node *right;
  int height;
}Node;

typedef struct LinkedList{
  int key;
  struct LinkedList* next;
}LinkedList;

////////////////////////////////////////////////////////////////////////////////////////////////////
#define COUNT 5
// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(Node *root, int space)
{
  // Increase distance between levels
  space += COUNT;
 
  // Process right child first
  if(root->right) print2DUtil(root->right, space);
  else if(root->height != 1) printf("\n\n");
 
  // Print current node after space
  // count

  printf("\n");
  for (int i = COUNT; i < space; i++)
    printf(" ");
  printf("%d\n", root->key);
 
  // Process left child
  if(root->left)  print2DUtil(root->left, space);
  else if(root->height != 1) printf("\n\n");
}
 
// Wrapper over print2DUtil()
void print2D(struct Node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////// My own tree printer /////////////////////////////////////////////////
int pow(int x, int y){
  if(y==0)
    return 1;
  if(y<0)
    return 0;
  int result = x;
  for(int i=0; i<y-1; i++)
    result *= x;
  return result;
}

int series(int s, int e){
  if(s>e)
    return 0;
  int result = 0;
  for(int i=s; i<=e; i++){
    result += pow(2,i);
  }
  return result;
}

bool isCorrect(int k, int i, int x){
  if(i==1)
    return false;
  for(int j=1; j<i; j++){
    if(k%pow(2,x-j)==0)
      return false;
  }
  return true;
}

void printTree(int depth){
  bool flag = false;
  int i, k, x = depth;
  for(i=1; i<=x; i++){ //tree의 height
    for(k=1; k<pow(2,x-1)+series(x-i,x-2); k++){ //tree의 각 height에서 발생하는 print 수
      if(k%(pow(2,x-i))==0 && isCorrect(k,i,x) && flag==false){
        printf("  o");
        flag = true;
      }
      else{
        printf("   ");
        flag = false;
      }
    }
    printf("  o");
    printf("\n");
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////