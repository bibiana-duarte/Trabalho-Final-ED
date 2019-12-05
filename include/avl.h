#ifndef __AVL_H_
#define __AVL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

struct nodoAVL
{
    char palavra[100];
    int FB;
    int frequencia;
    struct nodoAVL *esq;
    struct nodoAVL *dir;
};
typedef struct nodoAVL TnodoAVL;

TnodoAVL *insere_em_AVL(TnodoAVL *nodoAVL, char *palavra);
int quantidade_de_nodos_de_AVL(TnodoAVL *a);
int altura_de_AVL(TnodoAVL *a);
TnodoAVL* consulta_em_AVL(TnodoAVL *a, char *palavra);
void contador_de_AVL(int x, int y, TnodoAVL *a, FILE *arq);
int *FB_de_AVL(TnodoAVL *a, int *maior);
int FB_da_raiz_de_AVL(TnodoAVL *N);
TnodoAVL *rotacao_a_esquerda(TnodoAVL *x);
TnodoAVL *rotacao_a_direita(TnodoAVL *y);

#endif
