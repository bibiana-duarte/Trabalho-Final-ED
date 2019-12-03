#include "../include/main.h"
void contador_ABP(int x, int y, TnodoABP *a);
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"portuguese");

    char nome_arq_entrada[MAX_FILENAME_LENGTH];
    char nome_arq_operacoes[MAX_FILENAME_LENGTH];
    char nome_arq_saida[MAX_FILENAME_LENGTH];
    char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

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

    TnodoABP *arv_ABP = NULL;
    TnodoAVL *arv_AVL = NULL;

    while (!feof(arq_entrada)) // Enquanto não ler todo o arquivo
    {
        char linha[MAX_STRING_LENGTH];
        fgets(linha, MAX_STRING_LENGTH, arq_entrada); // Lê uma linha do arquivo

        char *palavra = strtok(linha,separador); // Pega a primeira palavra da linha
        // char *palavra = strtok(linha, " ");
        int balanceada = 1;
        while (palavra != NULL) // Enquanto for possível pegar novas palavras válidas da linha
        {
            int letra;
            for (letra = 0; letra < strlen(palavra); letra++) // Torna minúscula a palavra
                palavra[letra] = tolower(palavra[letra]);


            // puts(palavra);
            arv_AVL = insere_AVL(arv_AVL, palavra, &balanceada); // Insere a palavra na árvore AVL

            arv_ABP = insere_ABP(arv_ABP, palavra); // Insere a palavra na árvore ABP

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
    int ninic, nfim;
    char linha_op[50];
    char *pal;
    TnodoABP *nodo1;

    //fgets(linha_op, 50, arq_operacoes);
    //operacao = strtok(linha_op," ");

    //Funciona até aqui


    while(!feof(arq_operacoes))
    {
        fgets(linha_op, 50, arq_operacoes);
        operacao = strtok(linha_op," ");

        if(operacao[0] == 'C')
        {
            printf("C\n");


            // scanf("%[0123456789] %[0123456789]", &inic, &fim);
            inic = strtok(NULL," ");
            fim = strtok(NULL," ");
            puts(inic);
            puts(fim);
            inic=limpa(inic);
            fim=limpa(fim);



            ninic=atoi(inic);
            nfim=atoi(fim);


           ////////////////////////////////////////////////////

            void contador_ABP(int x, int y, TnodoABP *a)
            {

                if(a == NULL)
                    return;

                if(a->frequencia <= y && a->frequencia >= x )
                {

                    fprintf(arq_saida, "%s",a->palavra);
                    fprintf(arq_saida, "%d",a->frequencia);

                    //puts(a->palavra);
                    //printf("%d",a->frequencia);

                }
                contador_ABP(x,y,a->dir);
                contador_ABP(x,y,a->esq);


            }
            contador_ABP(ninic, nfim , arv_ABP);
            /////////////////////////////////////////////////////



            strtok(NULL,"\n");
            operacao = strtok(NULL," ");


        }
        else
        {

            //pal = strtok(linha_op," ");

            pal = strtok(NULL, " ");
            pal = limpa(pal);
            puts(operacao);
            puts(pal);

            // char *testebug;
            //printf("colocoque aqui");
            //gets(testebug);

            nodo1 = consulta_ABP(arv_ABP,pal);

            fprintf(arq_saida, "%s",pal);

            fprintf(arq_saida, "%d",nodo1->frequencia);


            strtok(NULL,"\n");
            operacao = strtok(NULL," ");

        }

    }


    fclose(arq_operacoes);
    fclose(arq_saida);
    return SUCCESS;
}
