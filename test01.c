#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_INPUT 20
#define INPUT_STREAM_CLEAR int c; while((c=getchar())!= '\n' && c!=EOF){}

typedef struct basisNode{
    char cityName[11];
    // adjLink link;
}basisNode;

short num = 5;
typedef enum Type {adjacent_node, BST_node}Type;

char* getstr(){
    char* str = (char*)malloc(sizeof(10));
    strcpy(str, "hello");
    return str;
}

int main(void){
    printf("%s\n", "hasldf");

    return 0;
}
