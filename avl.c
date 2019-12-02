#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "contador_palavras.h"

TnodoAVL* inicializa_AVL()
{
    return NULL;
}


int conta_nodos_AVL(TnodoAVL *a)
{
    if(a == NULL)
        return 0;
    else
        return (1 + conta_nodos_AVL(a->dir) + conta_nodos_AVL(a->esq));
}


int altura(TnodoAVL *a)
{
    int alt_esq, alt_dir;
    if (a == NULL)
        return 0;
    else
    {
        alt_esq = altura(a->esq);
        alt_dir = altura(a->dir);
        if (alt_esq > alt_dir)
            return (1 + alt_esq);
        else
            return (1 + alt_dir);
    }
}


int calcula_fator(TnodoAVL *arv)
{
    return (altura(arv->esq) - altura(arv->dir));
}


int fator_balanceamento(TnodoAVL *a)
{
    int fb_dir, fb_esq;
    int maior;

    if(a == NULL)
        return 0;

    fb_dir = fator_balanceamento(a->dir);
    fb_esq = fator_balanceamento(a->esq);
    maior = a->FB;

    if(maior < fb_dir)
        maior = fb_dir;

    if(maior < fb_esq)
        maior = fb_esq;

    return maior;

}

/*
void desenha(TnodoAVL *a, int nivel)
{
    int x;

    if (a !=NULL)
    {
        for (x=1; x<=nivel; x++)
            printf("=");
        printf("%s FB= %d\n", a->palavra, calcula_FB(a));
        if (a->esq != NULL) desenha(a->esq, (nivel+1));
        if (a->dir != NULL) desenha(a->dir, (nivel+1));
    }
}

*/


TnodoAVL* rotacao_direita(TnodoAVL* n)
{
    TnodoAVL* aux;

    aux = n->esq;
    n->esq = aux->dir;
    aux->dir = n;
    n->FB = 0;
    n = aux;



    return n;
}


TnodoAVL* rotacao_esquerda(TnodoAVL *n)
{
    TnodoAVL* aux;

    aux = n->dir;
    n->dir = aux->esq;
    aux->esq = n;
    n->FB = 0;
    n = aux;



    return aux;
}


TnodoAVL* rotacao_dupla_direita (TnodoAVL* n)
{
    TnodoAVL* aux1, *aux2;

    aux1 = n->esq;
    aux2 = aux1->dir;
    aux1->dir = aux2->esq;
    aux2->esq = aux1;
    n->esq = aux2->dir;
    aux2->dir = n;

    if (aux2->FB == 1)
        n->FB = -1;
    else
        n->FB = 0;
    if (aux2->FB == -1)
        aux1->FB = 1;
    else
        aux1->FB = 0;
    n = aux2;


    return n;
}


TnodoAVL* rotacao_dupla_esquerda (TnodoAVL* n)
{
    TnodoAVL *aux1, *aux2;

    aux1 = n->dir;
    aux2 = aux1->esq;
    aux1->esq = aux2->dir;
    aux2->dir = aux1;
    n->dir = aux2->esq;
    aux2->esq = n;
    if (aux2->FB == -1)
        n->FB = 1;
    else
        n->FB = 0;
    if (aux2->FB == 1)
        aux1->FB = -1;
    else
        aux1->FB = 0;
    n = aux2;
    return n;
}


TnodoAVL* caso1 (TnodoAVL* arv, int *ok)
{
    TnodoAVL *aux;

    aux = arv->esq;
    if (aux->FB == 1)
    {
        arv = rotacao_direita(arv);
    }
    else
    {
        arv = rotacao_dupla_direita(arv);
    }

    arv->FB = 0;
    *ok = 0;

    return arv;
}

TnodoAVL* caso2 (TnodoAVL *arv, int *ok)
{
    TnodoAVL *aux;

    aux = arv->dir;
    if (arv->FB == -1)
    {
        arv = rotacao_esquerda(arv);
    }
    else
    {
        arv = rotacao_dupla_esquerda(arv);
    }
    arv->FB = 0;
    *ok = 0;

    return arv;
}


TnodoAVL* insere_AVL(TnodoAVL *a, char palavra[], int *ok)
{

    if (a == NULL)   //Chegou no fim da árvore, insere o nodo
    {
        a = (TnodoAVL*) malloc(sizeof(TnodoAVL));
        strcpy(a->palavra,palavra);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if ( (strcmp(palavra,a->palavra)) < 0)
    {
        a->esq = insere_AVL(a->esq, palavra, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case  0:
                a->FB = 1;
                break;
            case  1:
                a = caso1(a,ok);
                break;
            }
        }
    }
    else if ( strcmp(palavra,a->palavra) > 0)
    {
        a->dir = insere_AVL(a->dir,palavra,ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case  1:
                a->FB = 0;
                *ok = 0;
                break;
            case  0:
                a->FB = -1;
                break;
            case -1:
                a = caso2(a,ok);
                break;
            }
        }
    }

    else
    {
        (a->frequencia)++;
    }

    return a;
}



/*
nodoAVL* consulta_AVL(nodoAVL *a, char palavra[] )
{

    while (a != NULL)
    {

        if (a->palavra == palavra )
        {
            return a;     //achou então retorna o ponteiro para o nodo
        }

        if (a->palavra > chave)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //se não achou
} */
