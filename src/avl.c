#include "../include/avl.h"

TnodoAVL *insere_em_AVL(TnodoAVL *nodoAVL, char *palavra)
{
    if (nodoAVL == NULL) // Se vazio cria um nodo
    {
        nodoAVL = (TnodoAVL *)malloc(sizeof(TnodoAVL));
        strcpy(nodoAVL->palavra, palavra);
        nodoAVL->esq = NULL;
        nodoAVL->dir = NULL;
        nodoAVL->frequencia = 1;
    }
    else if (strcmp(palavra, nodoAVL->palavra) < 0) //  Se palavra menor insere a esquerda
    {
        nodoAVL->esq = insere_em_AVL(nodoAVL->esq, palavra);
    }
    else if (strcmp(palavra, nodoAVL->palavra) > 0) // Se palavra maior insere a direita
    {
        nodoAVL->dir = insere_em_AVL(nodoAVL->dir, palavra);
    }
    else
    {
        nodoAVL->frequencia++;
        return nodoAVL; // se já tiver a palavra, nao precisa balancear
    }

    //3. Calcula o fator de balanceamento de seu antecessor
    int balance = FB_da_raiz_de_AVL(nodoAVL);

    // Se o nodo ficou desbalanceado

    // Left Left Case
    if (balance > 1 && (strcmp(palavra, nodoAVL->esq->palavra) < 0))
        return rotacao_a_direita(nodoAVL);

    // Right Right Case
    if (balance < -1 && (strcmp(palavra, nodoAVL->dir->palavra) > 0))
        return rotacao_a_esquerda(nodoAVL);

    // Left Right Case
    if (balance > 1 && (strcmp(palavra, nodoAVL->esq->palavra) > 0))
    {
        nodoAVL->esq = rotacao_a_esquerda(nodoAVL->esq);
        return rotacao_a_direita(nodoAVL);
    }

    // Right Left Case
    if (balance < -1 && (strcmp(palavra, nodoAVL->dir->palavra) > 0))
    {
        nodoAVL->dir = rotacao_a_direita(nodoAVL->dir);
        return rotacao_a_esquerda(nodoAVL);
    }
    return nodoAVL;
}

int quantidade_de_nodos_de_AVL(TnodoAVL *a)
{
    if (a == NULL)
        return 0;
    else
        return (1 + quantidade_de_nodos_de_AVL(a->dir) + quantidade_de_nodos_de_AVL(a->esq));
}

int altura_de_AVL(TnodoAVL *a)
{
    int alt_esq, alt_dir;
    if (a == NULL)
        return 0;
    else
    {
        alt_esq = altura_de_AVL(a->esq);
        alt_dir = altura_de_AVL(a->dir);
        if (alt_esq > alt_dir)
            return (1 + alt_esq);
        else
            return (1 + alt_dir);
    }
}

TnodoAVL *consulta_em_AVL(TnodoAVL *a, char *palavra)
{
    while (a != NULL)
    {
        if (strcmp(a->palavra, palavra) == 0)
        {
            return a; //achou então retorna o nodo
        }
        if (strcmp(palavra, a->palavra) < 0) // Se a palavra for menor
            a = a->esq;
        else //Se palavra maior
            a = a->dir;
    }
    return NULL; //Retorna NULL se não encontrou
}

void contador_de_AVL(int x, int y, TnodoAVL *a, FILE *arq)
{
    if (a == NULL)
        return;

    if (a->frequencia <= y && a->frequencia >= x) //Se frequencia estiver no intervalo de x a y
    {

        fprintf(arq, "%s - ", a->palavra); // Escreve a palavra e sua frequencia no arquivo de saida
        fprintf(arq, "%d\n", a->frequencia);
    }
    contador_de_AVL(x, y, a->dir, arq);
    contador_de_AVL(x, y, a->esq, arq);
}

int *FB_de_AVL(TnodoAVL *a, int *maior) // Fator balncemanto da árvore
{
    if (a == NULL)
        return 0;

    if (abs(a->FB) > abs(*maior))
        *maior = a->FB;

    FB_de_AVL(a->dir, maior);
    FB_de_AVL(a->esq, maior);

    return maior;
}

// Retorna o valor de balaceamnto de uma arvore
int FB_da_raiz_de_AVL(TnodoAVL *N)
{
    if (N == NULL)
        return 0;
    return altura_de_AVL(N->esq) - altura_de_AVL(N->dir);
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
TnodoAVL *rotacao_a_esquerda(TnodoAVL *x)
{
    TnodoAVL *y = x->dir;
    TnodoAVL *T2 = y->esq;

    // Perform rotation
    y->esq = x;
    x->dir = T2;

    // Return new root
    return y;
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
TnodoAVL *rotacao_a_direita(TnodoAVL *y)
{
    TnodoAVL *x = y->esq;
    TnodoAVL *T2 = x->dir;

    // Perform rotation
    x->dir = y;
    y->esq = T2;

    // Return new root
    return x;
}

