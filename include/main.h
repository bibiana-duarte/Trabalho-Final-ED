#include <stdio.h>
#include <ctype.h>
#include "../include/avl.h"
#include "../include/abp.h"
#include <locale.h>
#include <time.h>
#define MAX_FILENAME_LENGTH 20
#define SUCCESS 0
#define ERROR -1
#define MAX_STRING_LENGTH 1000


char* limpa(char *p)
{
    int i;

    for(i=0; i<strlen(p); i++)
    {
        if((p[i] < 48) || (p[i]>172))
            p[i] = p[i+1];
    }
return p;
}



