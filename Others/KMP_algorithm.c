#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_LEN

int failure[MAX_LEN];

void createFailFunc(char *pat)
/********************************************************
 * DESCRIPTION
 *     create failure function of 'pat'
 ********************************************************/
{
    int i = 0;
    int n = strlen(pat);
    failure[0] = -1;
    for (int j = 1; j < n; j++){
        i = failure[j - 1];
        while (pat[j] != pat[i + 1] && i >= 0)
            i = failure[i];
        if (pat[j] == pat[i + 1])
            failure[j] = i + 1;
        else
            failure[j] = -1;
    }
}

int patternMatch(char* string, char* pattern)
/********************************************************
 * DESCRIPTION
 *     Find the first pattern that matches.
 *     And returns the first index of the matched pattern in 'string'.
 ********************************************************/
{
    int i=0; int j=0;
    int lens = strlen(string);
    int lenp = strlen(pattern);
    while(i<lens && j<lenp){
        if(string[i] == pattern[j]){i++; j++;}
        else if(j == 0) i++;
        else j = failure[j-1]+1;
    }
    return (j==lenp ? i-lenp : -1);
}

int main()
{
    char string[100]={"aabcddaab'jaejung'cddaabcddfaa'jaejung'asdfa"};
    char pattern[100] = {"jaejung"};
    createFailFunc(pattern);
    int startp = patternMatch(string, pattern);

    printf("start point about \'%s\': %d\n", pattern, startp);
    for(int i=startp; i<startp+strlen(pattern); i++){
        printf("%c", string[i]);
    }
    printf("\n");
    return 0;
}