#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 10

typedef enum Group{G1, G2, G3}Group; //R-Type = {G1=(add,sub,and) / G2=(sll, srl)}  I-Type = {G3=(addi, andi, lw, sw)}

void assembler(char* input, char* machineCode);
void int_to_strBin(int n, int len, char* bin);
void match_register(char* token, char* bin);
void initialize(char (*machineCode)[33]);
Group match_instruction(char* token, char* machineCode);

int main(void){
    char input[20];
    char machineCode[MAX_LINE][33] = {0};
    int count;
    initialize(machineCode);
    printf("Enter MIPS Assembly below line-by-line\n");
    printf("if you want to quit, enter (q)\n");
    printf("------------------------------------------\n");
    for(count=0; ;count++){
        scanf("%[^\n]s", input);
        if(strlen(input)==1 && input[0]=='q')
            break;
        assembler(input, machineCode[count]);
        scanf("%*c");
    }
    printf("\nMIPS machine code corresponding to above MIPS Assembly\n");
    printf("------------------------------------------------------------\n");
    for(int i=0; i<count; i++){
        printf("%s\n", machineCode[i]);
    }
    return 0;
}

void initialize(char (*machineCode)[33]){
    for(int i=0; i<MAX_LINE; i++){//initialize as '0'
        for(int j=0; j<32; j++){
            machineCode[i][j] = '0';
        }
    }
}

void assembler(char* input, char* machineCode){
    char* token;
    char bin[17];
    Group group;

    token = strtok(input, " ");
    group = match_instruction(token, machineCode);

    token = strtok(NULL, " "); //G1,G2 = (token=rd)   G3 = (token=rt)
    match_register(token, bin);
    if(group==G1 || group==G2){
        strncpy(&machineCode[16], bin, 5);
    }
    else if(group==G3){
        strncpy(&machineCode[11], bin, 5);
    }

    token = strtok(NULL, " "); //G1,G3 = (token=rs)   G2 = (token=rt)
    match_register(token, bin);
    if(group==G1 || group==G3){
        strncpy(&machineCode[6], bin, 5);
    }
    else if(group==G2){
        strncpy(&machineCode[11], bin, 5);
    }

    token = strtok(NULL, " "); //G1 = (token=rt)   G2 = (token=shamt)   G3 = (token=immediate)
    if(group==G1){
        match_register(token, bin);
        strncpy(&machineCode[11], bin, 5);
    }
    else{
        int temp = strtol(token, NULL, 0); //converting string to decimal number
        if(group==G2){
            int_to_strBin(temp, 5, bin);
            strncpy(&machineCode[21], bin, 5);
        }
        if(group==G3){
            int_to_strBin(temp, 16, bin);
            strncpy(&machineCode[16], bin, 16);
        }
    }
}

void int_to_strBin(int n, int len, char* bin){
    int mod;
    int i=len-1;
    if (n != 0){
        while (n != 1){ //fill binary from the back to the front
            mod = n % 2;
            n = n / 2;
            if (mod == 1)
                bin[i] = '1';
            else
                bin[i] = '0';
            i--;
        }
        bin[i] = '1';
    }
    else{
        bin[i] = '0';
    }

    for(int k=0; k<i; k++){ //fill the remaining part with '0'
        bin[k] = '0';
    }
}

void match_register(char* token, char* bin){
    int n;
    if(!strcmp(token, "zero")) n=0;
    else if(!strcmp(token, "at")) n=1;
    else if(!strcmp(token, "t8")) n=24;
    else if(!strcmp(token, "t9")) n=25;
    else if(!strcmp(token, "gp")) n=28;
    else if(!strcmp(token, "sp")) n=29;
    else if(!strcmp(token, "fp")) n=30;
    else if(!strcmp(token, "ra")) n=31;
    else
    {
        switch (token[0])
        {
        case 'v':
            n = 2 + (token[1] - '0');
            break;
        case 'a':
            n = 4 + (token[1] - '0');
            break;
        case 't':
            n = 8 + (token[1] - '0');
            break;
        case 's':
            n = 16 + (token[1] - '0');
            break;
        case 'k':
            n = 26 + (token[1] - '0');
            break;
        }
    }
    int_to_strBin(n, 5, bin);
}

Group match_instruction(char* token, char* machineCode){
    Group group;
    char temp[7];

    if(!strcmp(token, "add") || !strcmp(token, "sub") || !strcmp(token, "and")){
        if(!strcmp(token, "add"))
            strcpy(temp, "100000");
        if(!strcmp(token, "sub"))
            strcpy(temp, "100010");
        if(!strcmp(token, "and"))
            strcpy(temp, "100100");
        
        group = G1;
        strncpy(&machineCode[26], temp, 6);
    }

    if(!strcmp(token, "sll") || !strcmp(token, "srl")){
        if(!strcmp(token, "sll"))
            strcpy(temp, "000000");
        if(!strcmp(token, "srl"))
            strcpy(temp, "000010");
        
        group = G2;
        strncpy(&machineCode[26], temp, 6);
    }

    if(!strcmp(token, "addi") || !strcmp(token, "andi") || !strcmp(token, "lw") || !strcmp(token, "sw")){
        if(!strcmp(token, "addi"))
            strcpy(temp, "001000");
        if(!strcmp(token, "andi"))
            strcpy(temp, "001100");
        if(!strcmp(token, "lw"))
            strcpy(temp, "100011");
        if(!strcmp(token, "sw"))
            strcpy(temp, "101011");
        
        group = G3;
        strncpy(machineCode, temp, 6);
    }

    return group;
}
/*
lw t0 s7 16
sll t1 t0 2
add t2 t1 s6
lw t3 t2 0
sub s0 s1 t3
q

sll t2 s0 4
srl t0 t1 5
q
*/