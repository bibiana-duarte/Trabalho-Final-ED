#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "contador_palavras.h"

TnodoAVL *inicializa_AVL();
int conta_nodos_AVL(TnodoAVL *a);
int altura(TnodoAVL *a);
int calcula_fator(TnodoAVL *arv);
int fator_balanceamento(TnodoAVL *a);
//void desenha(TnodoAVL *a, int nivel);
TnodoAVL *rotacao_direita(TnodoAVL *n);
TnodoAVL *rotacao_esquerda(TnodoAVL *n);
TnodoAVL *rotacao_dupla_direita(TnodoAVL *n);
TnodoAVL *rotacao_dupla_esquerda(TnodoAVL *n);
TnodoAVL *caso1(TnodoAVL *arv, int *ok);
TnodoAVL *caso2(TnodoAVL *arv, int *ok);
TnodoAVL *insere_AVL(TnodoAVL *a, char palavra[], int *ok);
//nodoAVL* consulta_AVL(nodoAVL *a, char palavra[]);
