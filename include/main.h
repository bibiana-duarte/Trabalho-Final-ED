#include <stdio.h>
#include <ctype.h>
#include "../include/avl.h"
#include "../include/abp.h"

#define COMPARACOES 0
#define ROTACOES 0
#define MAX_FILENAME_LENGTH 20
#define SUCCESS 0
#define ERROR -1
#define MAX_STRING_LENGTH 1000



void contador_ABP(int x, int y, TnodoABP *a){

if(a->frequencia <= y || a->frequencia >= x )
    printf("%s - %d", a->palavra,a->frequencia);
    contador_ABP(x,y,a->dir);
    contador_ABP(x,y,a->esq);


}



