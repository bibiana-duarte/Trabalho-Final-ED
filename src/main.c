#include "../include/main.h"

int main(int argc, char *argv[])
{
    //char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};
    // char linha[1000];

    char nome_arq_entrada[MAX_FILENAME_LENGTH];
    char nome_arq_operacoes[MAX_FILENAME_LENGTH];
    char nome_arq_saida[MAX_FILENAME_LENGTH];

    if (argc < 3)
    {
        printf("Nome do arquivo com o texto: ");
        gets(nome_arq_entrada);
        printf("Nome do arquivo de operacoes: ");
        gets(nome_arq_operacoes);
        printf("Nome do arquivo de saida: ");
        gets(nome_arq_saida);
    }
    else
    {
        strncpy(nome_arq_entrada, argv[0], MAX_FILENAME_LENGTH);
        strncpy(nome_arq_operacoes, argv[1], MAX_FILENAME_LENGTH);
        strncpy(nome_arq_saida, argv[2], MAX_FILENAME_LENGTH);
    }

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

    FILE *arq_entrada;
    if ((arq_entrada = fopen(nome_arq_entrada, "r")) == NULL)
        return ERROR;

    TnodoABP *arv_ABP = (TnodoABP *)NULL;
    TnodoAVL *arv_AVL = (TnodoAVL *)NULL;

    while (!feof(arq_entrada)) // Enquanto não ler todo o arquivo
    {
        char linha[MAX_STRING_LENGTH];
        fgets(linha, MAX_STRING_LENGTH, arq_entrada); // Lê uma linha do arquivo

        char *palavra = strtok(linha, " "); // Pega a primeira palavra da linha
        while (palavra != NULL) // Enquanto for possível pegar novas palavras válidas da linha
        {
            for (int letra = 0; letra < strlen(palavra); letra++) // Torna minúscula a palavra
                palavra[letra] = tolower(palavra[letra]);

            int balanceada = 1;
            insere_AVL(arv_AVL, palavra, &balanceada); // Insere a palavra na árvore AVL
            insere_ABP(arv_ABP, palavra); // Insere a palavra na árvore ABP

            palavra = strtok(NULL, " "); // Pega a próxima palavra da linha
        }
    }

    fclose(arq_entrada);

    FILE *arq_operacoes;
    if ((arq_operacoes = fopen(nome_arq_operacoes, "r")) == NULL)
        return ERROR;

    FILE *arq_saida;
    if ((arq_saida = fopen(nome_arq_saida, "w")) == NULL)
        return ERROR;

    fclose(arq_operacoes);
    fclose(arq_saida);

/*
    char palavra[20];
    printf("Palavra:");
    gets(palavra);

    c = consulta_ABP(arv,palavra);
    printf("FC: %d",c->frequencia);
*/

/*
    fgets(linha , 100 ,arq_operacoes)
    operacao = strtok(linha,' ');

    if(operacao == 'C')
        inic = strtok (NULL,linha);
    fim = strtok(NULL, ,linha);

    if(operacao == 'F')
        palavra = strtok(NULL, linhas);
    nodo = consulta(xxx, palavra);
    //nodo->frequencia

*/
    return SUCCESS;
}
