#include "../include/avl.h"

int conta_nodos_AVL(TnodoAVL *a)
{
    if (a == NULL)
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

int* fator_balanceamento(TnodoAVL *a, int *maior) // Fator balncemanto da árvore
{

    if (a == NULL)
        return 0;

    if (abs(a->FB) > abs(maior))
        maior = a->FB;

    fator_balanceamento(a->dir, maior);
    fator_balanceamento(a->esq, maior);

    return maior;
}


TnodoAVL* consulta_AVL(TnodoAVL *a, char *palavra)
{

    while (a != NULL)
    {
        if (strcmp(a->palavra,palavra) == 0)
        {
            return a; //achou então retorna o nodo
        }
        if (strcmp(palavra, a->palavra) < 0) // Se a palavra for menor
            a = a->esq;
        else                                //Se palavra maior
            a = a->dir;
    }
    return NULL; //Retorna NULL se não encontrou
}


void contador_AVL(int x, int y, TnodoAVL *a,FILE *arq)
{

    if(a == NULL)
        return;

    if(a->frequencia <= y && a->frequencia >= x ) //Se frequencia estiver no intervalo de x a y
    {

        fprintf(arq, "%s - ",a->palavra); // Escreve a palavra e sua frequencia no arquivo de saida
        fprintf(arq, "%d\n",a->frequencia);

    }
    contador_AVL(x,y,a->dir,arq);
    contador_AVL(x,y,a->esq,arq);


}


// A utility function to get the height of the tree
int height(TnodoAVL *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// Retorna o mair de dois inteiros
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new nodoAVL with the given key and
    NULL left and right pointers. */
TnodoAVL* newnodoAVL(char *palavra)
{
    TnodoAVL* nodoAVL = (TnodoAVL*)malloc(sizeof(TnodoAVL));
    strcpy(nodoAVL->palavra, palavra);
    nodoAVL->esq   = NULL;
    nodoAVL->dir  = NULL;
    nodoAVL->height = 1;  // new nodoAVL is initially added at leaf
    nodoAVL->frequencia = 1;
    return(nodoAVL);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
TnodoAVL *rightRotate(struct nodoAVL *y)
{
    TnodoAVL *x = y->esq;
    TnodoAVL *T2 = x->dir;

    // Perform rotation
    x->dir = y;
    y->esq = T2;

    // Update heights
    y->height = max(height(y->esq), height(y->dir))+1;
    x->height = max(height(x->esq), height(x->dir))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
TnodoAVL *leftRotate(struct nodoAVL *x)
{
    TnodoAVL *y = x->dir;
    TnodoAVL *T2 = y->esq;

    // Perform rotation
    y->esq = x;
    x->dir = T2;

    //  Update heights
    x->height = max(height(x->esq), height(x->dir))+1;
    y->height = max(height(y->esq), height(y->dir))+1;

    // Return new root
    return y;
}

// Retorna o valor de balaceamnto de uma arvore
int getBalance(struct nodoAVL *N)
{
    if (N == NULL)
        return 0;
    return height(N->esq) - height(N->dir);
}

TnodoAVL* insert(TnodoAVL* nodoAVL, char *palavra)
{

    if (nodoAVL == NULL)// Se vazio cria um nodo
        return(newnodoAVL(palavra));

    else if (strcmp(palavra, nodoAVL->palavra) < 0) //  Se palavra menor insere a esquerda
        nodoAVL->esq  = insert(nodoAVL->esq, palavra);

    else if (strcmp(palavra, nodoAVL->palavra) > 0) // Se palavra maior insere a direita
        nodoAVL->dir = insert(nodoAVL->dir, palavra);

    else // se já tiver a palavra, nao precisa balancear
    {
        (nodoAVL->frequencia)++;
        return nodoAVL;
    }

    // 2. Atualiza a  altura de seu antecessor nodoAVL
    nodoAVL->height = 1 + max(height(nodoAVL->esq),
                              height(nodoAVL->dir));

    //3. Calcula o fator de balanceamento de seu antecessor
    int balance = getBalance(nodoAVL);

    // Se o nodo ficou desbalanceado

    // Left Left Case
    if (balance > 1 && (strcmp(palavra, nodoAVL->esq->palavra)<0))
        return rightRotate(nodoAVL);

    // Right Right Case
    if (balance < -1 && (strcmp(palavra, nodoAVL->dir->palavra)>0))
        return leftRotate(nodoAVL);

    // Left Right Case
    if (balance > 1 && (strcmp(palavra, nodoAVL->esq->palavra)>0))
    {
        nodoAVL->esq =  leftRotate(nodoAVL->esq);
        return rightRotate(nodoAVL);
    }

    // Right Left Case
    if (balance < -1 && (strcmp(palavra, nodoAVL->dir->palavra)>0))
    {
        nodoAVL->dir = rightRotate(nodoAVL->dir);
        return leftRotate(nodoAVL);
    }
    return nodoAVL;
}



















