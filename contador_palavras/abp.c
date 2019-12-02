#include "../include/abp.h"



TnodoABP* insereArvore(TnodoABP *a, char palavra)
{
    if (a == NULL)
    {
        a = (TnodoABP*) malloc(sizeof(TnodoABP));
        strcpy(a->palavra,palavra);
        a->esq = NULL;
        a->dir = NULL;
        return a;
    }
    else if (strcmp(palavra, a->palavra) < 0)
        a->esq = insereArvore(a->esq,palavra);
    else if (strcmp(palavra, a->palavra) > 0)
        a->dir = insereArvore(a->dir,palavra);
    return a;
}


int alturaABP (TnodoABP *a)
{
    int altEsq, altDir;

    if (a == NULL)
        return 0;
    else
    {
        altEsq = altura (a->esq);
        altDir = altura (a->dir);
        if (altEsq > altDir)
            return (1 + altEsq);
        else
            return (1 + altDir);
    }
}


int conta_nodosABP(TnodoABP *a)
{
    int cont = 0;

    if(a==NULL)
        return cont++;
    else
    {
        cont = 1 + conta_nodos(a->dir) + conta_nodos(a->esq);
    }

}


TnodoABP* consultaABP(TnodoABP *a, char palavra[])
{

    while (a != NULL)
    {

        if ((strcmp(a->palavra,palavra) == 0 )
        {
            return a;     //achou então retorna o ponteiro para o nodo
        }

        if ((strcmp(a->palavra,palavra) < 0)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //se não achou
}

