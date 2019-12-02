#include "../include/abp.h"

TnodoABP *insere_arvore(TnodoABP *a, char palavra)
{
    if (a == NULL)
    {
        a = (TnodoABP *)malloc(sizeof(TnodoABP));
        strcpy(a->palavra, palavra);
        a->esq = NULL;
        a->dir = NULL;
        return a;
    }
    else if (strcmp(palavra, a->palavra) < 0)
        a->esq = insere_arvore(a->esq, palavra);
    else if (strcmp(palavra, a->palavra) > 0)
        a->dir = insere_arvore(a->dir, palavra);
    return a;
}

int altura_ABP(TnodoABP *a)
{
    int altEsq, altDir;

    if (a == NULL)
        return 0;
    else
    {
        altEsq = altura(a->esq);
        altDir = altura(a->dir);
        if (altEsq > altDir)
            return (1 + altEsq);
        else
            return (1 + altDir);
    }
}

int conta_nodos_ABP(TnodoABP *a)
{

    if (a == NULL)
        return 0;
    else
    {
        return 1 + conta_nodos_ABP(a->dir) + conta_nodos_ABP(a->esq);

    }
}

TnodoABP *consulta_ABP(TnodoABP *a, char palavra[])
{

    while (a != NULL)
    {

        if ((strcmp(a->palavra,palavra)) == 0 )

        {
            return a; //achou ent�o retorna o ponteiro para o nodo
        }

        if (strcmp(a->palavra, palavra) < 0)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //se n�o achou
}
