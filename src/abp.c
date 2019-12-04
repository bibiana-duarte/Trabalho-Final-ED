#include "../include/abp.h"

TnodoABP *insere_ABP(TnodoABP *a, char palavra[])
{
    // TnodoABP *raiz = a;

    if (a == NULL)
    {
        a = (TnodoABP *)malloc(sizeof(TnodoABP));
        strcpy(a->palavra, palavra);
        a->esq = NULL;
        a->dir = NULL;
        a->frequencia = 1;
    }
    else if (strcmp(palavra, a->palavra) < 0)
    {
        a->dir = insere_ABP(a->dir, palavra);
    }
    else if (strcmp(palavra, a->palavra) > 0)
    {
        a->esq = insere_ABP(a->esq, palavra);
    }
    else
    {
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

TnodoABP *consulta_ABP(TnodoABP *a, char *palavra)
{
    while (a != NULL)
    {
        if (strcmp(a->palavra,palavra) == 0)
        {

            return a; //achou então retorna o ponteiro para o nodo
        }
        if (strcmp(palavra, a->palavra) < 0)
            a = a->dir;
        else
            a = a->esq;
    }
    return NULL; //se não achou
}


void contador_ABP(int x, int y, TnodoABP *a,FILE *arq)
{

    if(a == NULL)
        return;

    if(a->frequencia <= y && a->frequencia >= x )
    {

        fprintf(arq, "%s - ",a->palavra);
        fprintf(arq, "%d\n",a->frequencia);

    }
    contador_ABP(x,y,a->dir,arq);
    contador_ABP(x,y,a->esq,arq);


}

int FB_ABP (TnodoABP *a)
{
    if(a==NULL)
        return 0;


    a->FB = altura_ABP(a->esq) - altura_ABP(a->dir);

    FB_ABP(a->esq);
    FB_ABP(a->dir);
}

int* fator_balanceamento2(TnodoABP *a, int *maior) // Fator balncemanto da árvore
{

    if (a == NULL)
        return 0;

    if (abs(a->FB) > abs(maior))
        maior = a->FB;

    fator_balanceamento2(a->dir, maior);
    fator_balanceamento2(a->esq, maior);

    return maior;
}


