#include "../include/avl.h"
#define ROTACOES 0

//#include "../include/main.h"





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

int fator_balanceamento(TnodoAVL *a) // Fator balncemanto da árvore
{
    int fb_dir, fb_esq;
    int maior;

    if (a == NULL)
        return 0;

    fb_dir = fator_balanceamento(a->dir);
    fb_esq = fator_balanceamento(a->esq);
    maior = a->FB;

    if (maior < fb_dir)
        maior = fb_dir;

    if (maior < fb_esq)
    {
        //COMP_AVL++;
        maior = fb_esq;
    }
    return maior;
}


void desenha(TnodoAVL *a, int nivel)
{
    int x;

    if (a !=NULL)
    {
        // COMP_AVL++;

        for (x=1; x<=nivel; x++)
            printf("=");
        puts(a->palavra);
        printf("FB= %d\n", calcula_fator(a));
        printf("frequencia: %d \n", a->frequencia);
        if (a->esq != NULL)
            desenha(a->esq, (nivel+1));
        if (a->dir != NULL)
            desenha(a->dir, (nivel+1));
    }
}



TnodoAVL *rotacao_direita(TnodoAVL *n)
{
    TnodoAVL *aux;

    aux = n->esq;
    n->esq = aux->dir;
    aux->dir = n;
    n->FB = 0;
    n = aux;
    ROTACOES++;
    return n;
}

TnodoAVL *rotacao_esquerda(TnodoAVL *n)
{
    TnodoAVL *aux;

    aux = n->dir;
    n->dir = aux->esq;
    aux->esq = n;
    n->FB = 0;
    n = aux;
    ROTACOES++;
    return aux;
}

TnodoAVL *rotacao_dupla_direita(TnodoAVL *n)
{
    TnodoAVL *aux1, *aux2;

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
    ROTACOES++;
    ROTACOES++;
    return n;
}

TnodoAVL *rotacao_dupla_esquerda(TnodoAVL *n)
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
    ROTACOES++;
    ROTACOES++;
    return n;
}

TnodoAVL *caso1(TnodoAVL *arv, int *ok)
{
    TnodoAVL *aux;

    aux = arv->esq;
    if (aux->FB == 1)
    {
        arv = rotacao_direita(arv);
        //  ROT_AVL++;

    }
    else
    {
        arv = rotacao_dupla_direita(arv);
        // ROT_AVL++;
        //  ROT_AVL++;



    }

    arv->FB = 0;
    *ok = 0;

    return arv;
}

TnodoAVL *caso2(TnodoAVL *arv, int *ok)
{
    TnodoAVL *aux;

    aux = arv->dir;
    if (aux->FB == -1)
    {
        arv = rotacao_esquerda(arv);
        // ROT_AVL++;
    }
    else
    {
        arv = rotacao_dupla_esquerda(arv);
        //ROT_AVL++;
        //ROT_AVL++;

    }
    arv->FB = 0;
    *ok = 0;

    return arv;
}

TnodoAVL* consulta_AVL(TnodoAVL *a, char *palavra)
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



TnodoAVL *insere_AVL(TnodoAVL *a, char palavra[], int *ok)
{

    if (consulta_AVL(a,palavra) == NULL) //Chegou no fim da árvore, insere o nodo
    {

        a = (TnodoAVL *)malloc(sizeof(TnodoAVL));
        strcpy(a->palavra, palavra);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        a->frequencia = 1;
        *ok = 1;
    }
    else if ((strcmp(palavra, a->palavra)) < 0)
    {
        a->dir = insere_AVL(a->dir, palavra, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a = caso1(a, ok);
                break;
            }
        }
    }
    else if (strcmp(palavra, a->palavra) > 0)
    {

        a->esq = insere_AVL(a->esq, palavra, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = caso2(a, ok);
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

void contador_AVL(int x, int y, TnodoAVL *a,FILE *arq)
{

    if(a == NULL)
        return;

    if(a->frequencia <= y && a->frequencia >= x )
    {

        fprintf(arq, "%s - ",a->palavra);
        fprintf(arq, "%d\n",a->frequencia);

    }
    contador_AVL(x,y,a->dir,arq);
    contador_AVL(x,y,a->esq,arq);


}














// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(TnodoAVL *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
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

// Get Balance factor of nodoAVL N
int getBalance(struct nodoAVL *N)
{
    if (N == NULL)
        return 0;
    return height(N->esq) - height(N->dir);
}

// Recursive function to insert a key in the subtree rooted
// with nodoAVL and returns the new root of the subtree.
TnodoAVL* insert(TnodoAVL* nodoAVL, char *palavra)
{
    /* 1.  Perform the normal BST insertion */
    if (nodoAVL == NULL)
        return(newnodoAVL(palavra));

    else if (strcmp(palavra, nodoAVL->palavra) < 0)
        nodoAVL->esq  = insert(nodoAVL->esq, palavra);
    else if (strcmp(palavra, nodoAVL->palavra) > 0)
        nodoAVL->dir = insert(nodoAVL->dir, palavra);
    else // se já tiver a palavra, nao precisa balancear
       {
       (nodoAVL->frequencia)++;
    return nodoAVL;}

    /* 2. Update height of this ancestor nodoAVL */
    nodoAVL->height = 1 + max(height(nodoAVL->esq),
                              height(nodoAVL->dir));

    /* 3. Get the balance factor of this ancestor
          nodoAVL to check whether this nodoAVL became
          unbalanced */
    int balance = getBalance(nodoAVL);

    // If this nodoAVL becomes unbalanced, then
    // there are 4 cases

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

    /* return the (unchanged) nodoAVL pointer */
    return nodoAVL;
}



















