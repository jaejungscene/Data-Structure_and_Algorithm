#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>

void fail(char *pat)
{
    int failure[strlen(pat)];
    int i;
    int n = strlen(pat);
    failure[0] = -1;
    for (int j = 1; j < n; j++)
    {
        i = failure[j - 1];
        while (pat[j] != pat[i + 1] && i >= 0)
            i = failure[i];
        if (pat[j] == pat[i + 1])
            failure[j] = i + 1;
        else
            failure[j] = -1;
    }

    for(int j = 0; j<n; j++){
        printf("%3c", pat[j]);
    }
    printf("\n");
    for(int j = 0; j<n; j++){
        printf("%3d", failure[j]);
    }
}

int main()
{
    char str[25]={"aabcddaabbaabcddaabcdda"};
    fail(str);
    return 0;
}