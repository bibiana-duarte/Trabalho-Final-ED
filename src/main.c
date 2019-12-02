#include <stdio.h>
#include "../include/avl.h"
#define COMPARACOES 0
#define ROTACOES 0

void main()
{
    FILE *arq_entrada;
    FILE *arq_saida;
    char nome_arqE[30];
    char nome_arqS[30];
    char aux_c;
    char aux_pal[30];
    TnodoAVL *arv;
    int x;
    int balanceada = 1;

    arv = inicializa_AVL();

    printf("Nome do arquivo com o texto: ");
    gets(nome_arqE);
    printf("Nome do arquivo de saida: ");
    gets(nome_arqS);

    arq_entrada = fopen(nome_arqE, "r");
    arq_saida = fopen(nome_arqS, "w");

    x = 0;

    aux_pal[0] = getc(arq_entrada);

    while (aux_pal[x] = !EOF)
    {

        while (getc(arq_entrada) != " ")
        {
            aux_c = getc(arq_entrada);
            aux_pal[x] = aux_c;
            x++;
        }

        insere_AVL(arv, aux_pal, &balanceada);
    }

    fclose(arq_entrada);
}
