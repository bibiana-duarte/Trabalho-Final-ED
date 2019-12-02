
struct nodoABP{
        char palavra;
        int frequencia;
        struct TnodoABP *esq;
        struct TnodoABP *dir;
};

typedef struct nodoABP TnodoABP;

TnodoABP* insereArvore(TnodoABP *a, char palavra);
int alturaABP (TnodoABP *a);
int conta_nodosABP(TnodoABP *a);
TnodoABP* consultaABP(TnodoABP *a, char palavra[]);
