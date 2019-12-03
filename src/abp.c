#include "../include/abp.h"

TnodoABP *insere_ABP(TnodoABP *a, char palavra[])
{
    if (a == NULL)
    {
        a = (TnodoABP *)malloc(sizeof(TnodoABP));
        strcpy(a->palavra, palavra);
        a->esq = NULL;
        a->dir = NULL;
        a->frequencia = 1;
    }
    else if (strcmp(palavra, a->palavra) < 0){
        a->esq = insere_ABP(a->esq, palavra);
     }
    else if (strcmp(palavra, a->palavra) > 0){
        a->dir = insere_ABP(a->dir, palavra);
    }
    else{
        (a->frequencia)++;
    }
    return a;
}

int altura_ABP(TnodoABP *a)
{
    int altEsq, altDir;

    if (a == NULL)
        return 0;
    else
    {
        altEsq = altura_ABP(a->esq);
        altDir = altura_ABP(a->dir);
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
        if (strcmp(a->palavra,palavra) == 0)
        {

            return a; //achou então retorna o ponteiro para o nodo
        }
        if (strcmp(palavra, a->palavra) < 0)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //se não achou
}
