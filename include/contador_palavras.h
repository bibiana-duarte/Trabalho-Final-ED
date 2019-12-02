typedef struct nodoAVL
{
    char palavra[30];
    int FB;
    int frequencia;
    struct TnodoAVL *esq;
    struct TnodoAVL *dir;
} TnodoAVL;
