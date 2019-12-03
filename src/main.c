#include "../include/main.h"

int main(int argc, char *argv[])
{
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
            int letra;
            for (letra = 0; letra < strlen(palavra); letra++) // Torna minúscula a palavra
                palavra[letra] = tolower(palavra[letra]);

            int balanceada = 1;
            // puts(palavra);
            arv_AVL = insere_AVL(arv_AVL, palavra, &balanceada); // Insere a palavra na árvore AVL

            arv_ABP = insere_ABP(arv_ABP, palavra); // Insere a palavra na árvore ABP
            // puts(palavra);
            palavra = strtok(NULL, " "); // Pega a próxima palavra da linha


        }
    }

    fclose(arq_entrada);

    if(arv_ABP == NULL)
        printf("Vazia");


    TnodoABP *c;
    char p[20];
    printf("Palavra: ");
    gets(p);
    c = consulta_ABP(arv_ABP,p);
    printf("%d\n",c->frequencia);



    FILE *arq_operacoes;
    if ((arq_operacoes = fopen(nome_arq_operacoes, "r")) == NULL)
        return ERROR;

    FILE *arq_saida;
    if ((arq_saida = fopen(nome_arq_saida, "w")) == NULL)
        return ERROR;


    char *operacao,*inic,*fim;
    char linha_op[50];
    char *palav;
    TnodoABP *nodo1;

    fgets(linha_op, 50, arq_operacoes);
    operacao = strtok(linha_op," ");

    //Funciona até aqui

    if(operacao[0] == 'C')
    {

        inic = strtok(NULL," ");
        fim = strtok(NULL," ");
    }
    else
    {

      //  palav = strtok(linha_op," ");
      //  puts(palav);
        palav = strtok(NULL," ");
         puts(palav);
        palav = strtok(linha_op, " ");
        puts(palav);


        nodo1 = consulta_ABP(arv_ABP,palav);
        fprintf(arq_saida, "%s",palav);
        fprintf(arq_saida, "%d",nodo1->frequencia);
    }



    fclose(arq_operacoes);
    fclose(arq_saida);
    return SUCCESS;
}
