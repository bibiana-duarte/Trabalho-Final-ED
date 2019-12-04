#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct nodoABP
{
        char palavra[100];
        int frequencia;
        struct nodoABP *esq;
        struct nodoABP *dir;
};

typedef struct nodoABP TnodoABP;

TnodoABP *insere_ABP(TnodoABP *a, char palavra[]);
int altura_ABP(TnodoABP *a);
int conta_nodos_ABP(TnodoABP *a);
TnodoABP *consulta_ABP(TnodoABP *a, char palavra[]);
void contador_ABP(int x, int y, TnodoABP *a,FILE *arq);
