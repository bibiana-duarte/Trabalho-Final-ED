#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "avl.c"


nodoAVL* inicializa_AVL()
{
    return NULL;
}


int conta_nodos_AVL(nodoAVL *arv)
{
    if(a == NULL)
        return 0;
    else
        return (1 + conta_nodos_AVL(a->dir) + conta_nodos_AVL(a->esq));
}


int altura(nodoAVL *arv)
{
    int alt_esq, alt_dir;
    if (a == NULL)
        return 0;
    else
    {
        alt_esq = altura_AVL(arv->esq);
        alt_dir = altura_AVL(arv->dir);
        if (alt_esq > alt_dir)
            return (1 + alt_esq);
        else
            return (1 + alt_dir);
    }
}


int calcula_fator(nodoAVL *arv)
{
    return (altura(arv->esq) - altura(arv->dir));
}


int fator_balanceamento(nodoAVL *arv)
{
    int fb_dir, fb_esq;
    int maior;

    if(a == NULL)
        return 0;

    fb_dir = fator_balanceamento(arv->dir);
    fb_esq = fator_balanceamento(arv->esq);
    maior = arv->FB;

    if(maior < fb_dir)
        maior = fb_dir;

    if(maior < fb_esq)
        maior = fb_esq;

    return maior;

}


void desenha(nodoAVL *a, int nivel)
{
    int x;

    if (a !=NULL)
    {
        for (x=1; x<=nivel; x++)
            printf("=");
        printf("%d FB= %d\n", a->info, calcula_FB(a));
        if (a->esq != NULL) desenha(a->esq, (nivel+1));
        if (a->dir != NULL) desenha(a->dir, (nivel+1));
    }
}




nodoAVL* rotacao_direita(nodoAVL *n)
{
    nodoAVL* aux;

    aux = n->esq;
    n->esq = aux->dir;
    aux->dir = n;
    n->FB = 0;
    n = aux;



    return n;
}


nodoAVL* rotacao_esquerda(nodoAVL *n)
{
    nodoAVL* aux;

    aux = n->dir;
    n->dir = aux->esq;
    aux->esq = n;
    n->FB = 0;
    n = aux;



    return aux;
}


nodoAVL* rotacao_dupla_direita (nodoAVL* n)
{
    nodoAVL* aux1, *aux2;

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


nodoAVL* rotacao_dupla_esquerda (nodoAVL* n)
{
    nodoAVL *aux1, *aux2;

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


nodoAVL* caso1 (nodo* arv, int *ok)
{
    nodo *aux;

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

nodoAVL* caso2 (nodoAVL *arv, int *ok)
{
    nodo *aux;

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

nodoAVL* insere_AVL(nodoAVL *a, char palavra[], int *ok)
{

    if (a == NULL)   //Chegou no fim da árvore, insere o nodo
    {
        a = (nodo*) malloc(sizeof(nodo));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (x < a->info)
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
    else
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

    return a;
}

nodoAVL* consulta_AVL(nodoAVL *a, char palavra[] )
{

    while (a != NULL)
    {

        if (a->info == palavra )
        {
            return a;     //achou então retorna o ponteiro para o nodo
        }

        if (a->info > chave)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //se não achou
}
