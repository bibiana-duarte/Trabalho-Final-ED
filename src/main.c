#include "../include/main.h"
#include <windows.h>
//void contador_ABP(int x, int y, TnodoABP *a);
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"portuguese");
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

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
        //start = clock(); //inicia a contagem do tempo
        char linha[MAX_STRING_LENGTH];
        fgets(linha, MAX_STRING_LENGTH, arq_entrada); // Lê uma linha do arquivo
        char *palavra = strtok(linha,separador); // Pega a primeira palavra da linha
        while (palavra != NULL) // Enquanto for possível pegar novas palavras válidas da linha
        {
            int letra;
            for (letra = 0; letra < strlen(palavra); letra++) // Torna minúscula a palavra
                palavra[letra] = tolower(palavra[letra]);

            arv_AVL = insert(arv_AVL, palavra);
            arv_ABP = insere_ABP(arv_ABP, palavra); // Insere a palavra na árvore ABP
            palavra = strtok(NULL, separador); // Pega a próxima palavra da linha


        }
    }

    fclose(arq_entrada);
    //Abre os arquivos de operações e de saída
    FILE *arq_operacoes;
    if ((arq_operacoes = fopen(nome_arq_operacoes, "r")) == NULL)
        return ERROR;

    FILE *arq_saida;
    if ((arq_saida = fopen(nome_arq_saida, "w")) == NULL)
        return ERROR;


    char *operacao,*inic,*fim;
    int ninic, nfim,opcao;
    char linha_op[50];
    char *pal;
    printf("1-ABP\n2-AVL\n");
    scanf("%d",&opcao);

    if(opcao == 1)
    {
        int n_nodos = conta_nodos_ABP(arv_ABP);
        fprintf(arq_saida, "**********ESTATISTICAS DA ABP *************\nNumero de nodos %d\n",n_nodos);
        int altura = altura_ABP(arv_ABP);
        int *maior=arv_ABP->FB;
        fprintf(arq_saida, "Balanceamento: %d \n\n",fator_balanceamento2(arv_ABP,maior));
        fprintf(arq_saida,"Altura: %d\n*************************************************************\n",altura);


        while(!feof(arq_operacoes))//Enquanto não chegar no fim do arquivo
        {
            fgets(linha_op, 50, arq_operacoes);//Pega uma linha e guarda em linha_op
            operacao = strtok(linha_op," ");// Pega o conteudo da linh até o espaço

            if(operacao[0] == 'C')
            {
                fprintf(arq_saida,"***************************************************************************\n%c ",operacao[0]);
                inic = strtok(NULL," "); //Pega o conteudo da linha até o espaço
                fim = strtok(NULL," ");
                inic=limpa(inic);//Retira caracteres especiais(espaço,ponto, virgulas e etc)
                fim=limpa(fim);
                ninic=atoi(inic);//Converte char em int
                fprintf(arq_saida, "%d  ",ninic);
                nfim=atoi(fim);
                fprintf(arq_saida, "%d \n\n",nfim);
                contador_ABP(ninic, nfim , arv_ABP,arq_saida);
                strtok(NULL,"\n");
                operacao = strtok(NULL," ");

            }
            else
            {
                fprintf(arq_saida, "\n%c ",operacao[0]);
                pal = strtok(NULL, " ");
                pal = limpa(pal); //Retira caracteres especiais
                TnodoABP *nodo1;
                nodo1 = consulta_ABP(arv_ABP,pal); // Retorna o nodo da palavra procurada
                fprintf(arq_saida, "%s -",pal);
                fprintf(arq_saida, " %d\n",nodo1->frequencia);
                strtok(NULL,"\n");
                operacao = strtok(NULL," ");

            }

        }

    }

    if(opcao == 2)
    {

        int n_nodos = conta_nodos_AVL(arv_AVL);
        fprintf(arq_saida, "**********ESTATISTICAS DA AVL *************\nNumero de nodos %d\n",n_nodos);
        int alt = height(arv_AVL);
        int *maior=arv_AVL->FB;
        fprintf(arq_saida, "Balanceamento: %d \n\n",fator_balanceamento(arv_AVL,maior));
        fprintf(arq_saida,"Altura: %d\n*************************************************************\n",alt);



        while(!feof(arq_operacoes))
        {

            fgets(linha_op, 50, arq_operacoes);
            operacao = strtok(linha_op," ");
            if(operacao[0] == 'C')
            {
                fprintf(arq_saida,"***************************************************************************\n%c ",operacao[0]);
                inic = strtok(NULL," ");
                fim = strtok(NULL," ");
                inic=limpa(inic); //Retira caracteres especiais
                fim=limpa(fim);
                ninic=atoi(inic); // Conversão de char para int
                fprintf(arq_saida, "%d ",ninic);
                nfim=atoi(fim);
                fprintf(arq_saida, "%d  \n\n",nfim);
                contador_AVL(ninic, nfim , arv_AVL,arq_saida);
                strtok(NULL,"\n");
                operacao = strtok(NULL," ");

            }
            else
            {
                fprintf(arq_saida, "\n%c  ",operacao[0]);
                pal = strtok(NULL, " ");
                pal = limpa(pal);
                TnodoAVL *nodo2;
                nodo2 = consulta_AVL(arv_AVL,pal); // Retorna o nodo com palavra desejada
                fprintf(arq_saida, "%s -",pal);
                fprintf(arq_saida, " %d\n",nodo2->frequencia);
                strtok(NULL,"\n");
                operacao = strtok(NULL," ");

            }

        }
    }

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    fprintf(arq_saida, "\nTempo: %f s", interval);
    fclose(arq_operacoes); //Fecha arquivo de operações
    fclose(arq_saida); // Fecha arquivo de saída
    return SUCCESS;
}
