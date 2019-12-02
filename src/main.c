#include <stdio.h>
#include "../include/avl.h"
#define COMPARACOES 0
#define ROTACOES 0
#define FILENAME_LENGTH 20
#define SUCCESS 0
#define ERROR -1

int main(int argc, char* argv[])
{
     //char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    // char linha[1000];
    TnodoAVL *arv;
    arv = inicializa_AVL();

    FILE *arq_entrada;
    FILE *arq_operacoes;
    FILE *arq_saida;
    char nome_arq_entrada[FILENAME_LENGTH];
    char nome_arq_operacoes[FILENAME_LENGTH];
    char nome_arq_saida[FILENAME_LENGTH];
    if (argc < 3)
    {
        printf("Nome do arquivo com o texto: ");
        gets(nome_arq_entrada);
        printf("Nome do arquivo de saida: ");
        gets(nome_arq_operacoes);
        printf("Nome do arquivo de saida: ");
        gets(nome_arq_saida);
    }
    else
    {
        strncpy(nome_arq_entrada, argv[0], FILENAME_LENGTH);
        strncpy(nome_arq_operacoes, argv[1], FILENAME_LENGTH);
        strncpy(nome_arq_saida, argv[2], FILENAME_LENGTH);
    }
    if ((arq_entrada = fopen(nome_arq_entrada, "r")) == NULL)
        return ERROR;
    if ((arq_operacoes = fopen(nome_arq_operacoes, "r")) == NULL)
        return ERROR;
    if ((arq_saida = fopen(nome_arq_saida, "w")) == NULL)
        return ERROR;




    /*

         while (fgets(linha,1000,arq_entrada))
                {
                    palavra = strtok (linha, separador); //considera qquer caractere n�o alfab�tico como separador
                    while (palavra != NULL)
                    {
                        fprintf(saida,"%s ", strlwr(palavra)); //strlwr � a fun��o que converte palavras para min�sculo
                        palavra = strtok (NULL, separador);
                    }
                }

    */

    int x;
    x = 0;
    char aux_pal[30];
    aux_pal[0] = getc(arq_entrada);
    char aux_c;
    while (aux_pal[x] == !EOF)
    {
        while (getc(arq_entrada) != ' ')
        {
            aux_c = getc(arq_entrada);
            aux_pal[x] = aux_c;
            x++;
        }

        int balanceada = 1;
        insere_AVL(arv, aux_pal, &balanceada);
    }

    fclose(arq_entrada);
    fclose(nome_arq_operacoes);
    fclose(nome_arq_saida);
    return SUCCESS;
}
