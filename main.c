#include <stdio.h>
#include "avl.c"
#include "contador_palavras.h"
#define COMPARACOES 0
#define ROTACOES 0


FILE *arq_entrada;
FILE *arq_saida;
char nome_arqE[30];
char nome_arqS[30];
char aux_c;
char aux_pal[30];
nodoAVL *arv;
int x;

inicializa_AVL();


printf("Nome do arquivo com o texto: ");
scanf("%s",nome_arqE);
printf("Nome do arquivo de saida: ");
scanf("%s",nome_arqS)

arq_entrada = fopen(nome_arqE, "r");
arq_saida = fopen(nome_arqS, "w");



while(!EOF)
{

    x = 0;

    while(getc(arq_entrada) != " ")
    {
        aux_c = getc(arq_entrada);
        aux_pal[x] = aux_c;
        x++;
    }

    insere_AVL(arv,aux_pal,1);


}
