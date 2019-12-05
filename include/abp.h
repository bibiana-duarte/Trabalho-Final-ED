#ifndef __ABP_H_
#define __ABP_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct nodoABP
{
        char palavra[100];
        int FB;
        int frequencia;
        struct nodoABP *esq;
        struct nodoABP *dir;
};

typedef struct nodoABP TnodoABP;

TnodoABP *insere_em_ABP(TnodoABP *a, char* palavra);
int quantidade_de_nodos_de_ABP(TnodoABP *a);
int altura_de_ABP(TnodoABP *a);
TnodoABP *consulta_em_ABP(TnodoABP *a, char* palavra);
void contador_de_ABP(int x, int y, TnodoABP *a, FILE *arq);
int *FB_de_ABP(TnodoABP *a, int *maior);

#endif
