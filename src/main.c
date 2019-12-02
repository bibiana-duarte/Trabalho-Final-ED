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

    int letra;

    while (!feof(arq_entrada)) // Enquanto não ler todo o arquivo
    {
        char linha[MAX_STRING_LENGTH];
        fgets(linha, MAX_STRING_LENGTH, arq_entrada); // Lê uma linha do arquivo

        char *palavra = strtok(linha, " "); // Pega a primeira palavra da linha
        while (palavra != NULL) // Enquanto for possível pegar novas palavras válidas da linha
        {
            for (letra = 0; letra < strlen(palavra); letra++) // Torna minúscula a palavra
                palavra[letra] = tolower(palavra[letra]);

            int balanceada = 1;

            arv_AVL = insere_AVL(arv_AVL, palavra, &balanceada); // Insere a palavra na árvore AVL
            arv_ABP = insere_ABP(arv_ABP, palavra); // Insere a palavra na árvore ABP

            palavra = strtok(NULL, " "); // Pega a próxima palavra da linha
        }
    }

    fclose(arq_entrada);

    int n = 1;

    if(arv_ABP == NULL)
        printf("Vazia");


    TnodoABP *c;
    char p[20];
    puts("Palavra: ");
    gets(p);

    c = consulta_ABP(arv_ABP,p);
    printf("F: %d",c->frequencia);


    FILE *arq_operacoes;
    if ((arq_operacoes = fopen(nome_arq_operacoes, "r")) == NULL)
        return ERROR;

    FILE *arq_saida;
    if ((arq_saida = fopen(nome_arq_saida, "w")) == NULL)
        return ERROR;


    fgets(linha , 1000 ,arq_operacoes)
    operacao = strtok(linha,' ');
    strtok (NULL,linha);

    if(operacao == 'C'){
        inic = strtok (linha,' ');
        strtok(NULL, ,linha);
        fim = inic = strtok (linha,' ');
    }


    else{
        strtok(NULL, linhas);
        palavra = strtok(linha, ' ');
        nodo = consulta(arv_AVL, palavra);
        //nodo->frequencia

    fclose(arq_operacoes);
    fclose(arq_saida);

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
