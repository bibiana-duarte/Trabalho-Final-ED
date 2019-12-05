#include "../include/abp.h"

TnodoABP *insere_em_ABP(TnodoABP *a, char* palavra)
{
    if (a == NULL)
    {
        a = (TnodoABP *)malloc(sizeof(TnodoABP));
        strcpy(a->palavra, palavra);
        a->esq = NULL;
        a->dir = NULL;
        a->frequencia = 1;
    }
    else if (strcmp(palavra, a->palavra) < 0) //Se palavra menor
    {
        a->dir = insere_em_ABP(a->dir, palavra); //
    }
    else if (strcmp(palavra, a->palavra) > 0) //Se palavra menor
    {
        a->esq = insere_em_ABP(a->esq, palavra);
    }
    else
    {
        (a->frequencia)++;
    }
    return a;
}

int quantidade_de_nodos_de_ABP(TnodoABP *a)
{

    if (a == NULL) //Se nodo vazio retorna 0
        return 0;
    else
    {
        return 1 + quantidade_de_nodos_de_ABP(a->dir) + quantidade_de_nodos_de_ABP(a->esq);
    }
}

int altura_de_ABP(TnodoABP *a)
{
    int altEsq, altDir;

    if (a == NULL) // Se nodo vazio retorna 0
        return 0;
    else
    {
        altEsq = altura_de_ABP(a->esq); // Calcula altura das subarvores
        altDir = altura_de_ABP(a->dir);
        if (altEsq > altDir) // Encontra qual subarvore tem maior altura e acrescenta 1
            return (1 + altEsq);
        else
            return (1 + altDir);
    }
}

TnodoABP *consulta_em_ABP(TnodoABP *a, char *palavra)
{
    while (a != NULL)
    {
        if (strcmp(a->palavra, palavra) == 0)
        {

            return a; //achou então retorna o ponteiro para o nodo
        }
        if (strcmp(palavra, a->palavra) < 0)
            a = a->dir;
        else
            a = a->esq;
    }
    return NULL; //Retorna NULL caso não encontrar
}

void contador_de_ABP(int x, int y, TnodoABP *a, FILE *arq)
{

    if (a == NULL)
        return;

    if (a->frequencia <= y && a->frequencia >= x) //Se frequencia maior igual a y e menor igual a y
    {

        fprintf(arq, "%s - ", a->palavra); // Escreve a palavra e a frequencia do arquivo de saida
        fprintf(arq, "%d\n", a->frequencia);
    }
    contador_de_ABP(x, y, a->dir, arq);
    contador_de_ABP(x, y, a->esq, arq);
}

int *FB_de_ABP(TnodoABP *a, int *maior) // Fator balancemanto da árvore
{

    if (a == NULL) // Se nodd vazio retorna 0
        return 0;

    if (abs(a->FB) > abs(*maior))
        *maior = a->FB;

    FB_de_ABP(a->dir, maior);
    FB_de_ABP(a->esq, maior);

    return maior;
}
