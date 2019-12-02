#include <string.h>
#include <stdlib.h>

struct nodoABP
{
        char palavra;
        int frequencia;
        struct TnodoABP *esq;
        struct TnodoABP *dir;
};

typedef struct nodoABP TnodoABP;

TnodoABP *insere_ABP(TnodoABP *a, char palavra);
int altura_ABP(TnodoABP *a);
int conta_nodos_ABP(TnodoABP *a);
TnodoABP *consulta_ABP(TnodoABP *a, char palavra[]);
