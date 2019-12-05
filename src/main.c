#include "../include/main.h"

//void contador_ABP(int x, int y, TnodoABP *a);
int main(int argc, char **argv)
{
    setlocale(LC_ALL, "portuguese");
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    char nome_arq_entrada[MAX_FILENAME_LENGTH];
    char nome_arq_operacoes[MAX_FILENAME_LENGTH];
    char nome_arq_saida[MAX_FILENAME_LENGTH];
    char separador[] = {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    if (argc < 4)
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
        strncpy(nome_arq_entrada, argv[1], MAX_FILENAME_LENGTH);
        strncpy(nome_arq_operacoes, argv[2], MAX_FILENAME_LENGTH);
        strncpy(nome_arq_saida, argv[3], MAX_FILENAME_LENGTH);
    }

    FILE *arq_entrada;
    if ((arq_entrada = fopen(nome_arq_entrada, "r")) == NULL){
        printf("Erro de abertura do arquivo de entrada"); return ERROR_RETURN;}

    TnodoABP *arv_ABP = NULL;
    TnodoAVL *arv_AVL = NULL;

    while (!feof(arq_entrada)) // Enquanto não ler todo o arquivo
    {
        //start = clock(); //inicia a contagem do tempo
        char linha[MAX_STRING_LENGTH];
        fgets(linha, MAX_STRING_LENGTH, arq_entrada); // Lê uma linha do arquivo
        char *palavra = strtok(linha, separador);     // Pega a primeira palavra da linha
        while (palavra != NULL)                       // Enquanto for possível pegar novas palavras válidas da linha
        {
            int letra;
            for (letra = 0; letra < strlen(palavra); letra++) // Torna minúscula a palavra
                palavra[letra] = tolower(palavra[letra]);

            arv_AVL = insere_em_AVL(arv_AVL, palavra);
            arv_ABP = insere_em_ABP(arv_ABP, palavra); // Insere a palavra na árvore ABP
            palavra = strtok(NULL, separador);      // Pega a próxima palavra da linha
        }
    }

    fclose(arq_entrada);
    //Abre os arquivos de operações e de saída
    FILE *arq_operacoes;
    if ((arq_operacoes = fopen(nome_arq_operacoes, "r")) == NULL){
        printf("Erro de abertura do arquivo de operações"); return ERROR_RETURN;}

    FILE *arq_saida;
    if ((arq_saida = fopen(nome_arq_saida, "w")) == NULL){
        printf("Erro de abertura do arquivo de saída"); return ERROR_RETURN;}

    int quantidade_de_nodos;
    int FB;
    int altura;
    int opcao;
    printf("1-ABP\n2-AVL\n");
    scanf("%d", &opcao);
    if (opcao == ABP)
    {
        quantidade_de_nodos = quantidade_de_nodos_de_ABP(arv_ABP);
        int temp = arv_ABP->FB;
        FB = *FB_de_ABP(arv_ABP, &temp);
        altura = altura_de_ABP(arv_ABP);
        fprintf(arq_saida, "**********ESTATISTICAS DA ABP *************\n");
    }
    else if (opcao == AVL)
    {
        quantidade_de_nodos = quantidade_de_nodos_de_AVL(arv_AVL);
        int temp = arv_AVL->FB;
        FB = *FB_de_AVL(arv_AVL, &temp);
        altura = altura_de_AVL(arv_AVL);
        fprintf(arq_saida, "**********ESTATISTICAS DA AVL *************\n");
    }
    else{
        printf("Opção inválida"); return ERROR_RETURN;}
    
        fprintf(arq_saida, "Numero de nodos %d\n", quantidade_de_nodos);
        fprintf(arq_saida, "Balanceamento: %d \n\n",FB);
        fprintf(arq_saida, "Altura: %d\n", altura);
        fprintf(arq_saida, "*************************************************************\n");

    char *operacao, *inic, *fim;
    int ninic, nfim;
    char linha_op[50];
    char *pal;
    while (!feof(arq_operacoes)) //Enquanto não chegar no fim do arquivo
    {
        fgets(linha_op, 50, arq_operacoes); //Pega uma linha e guarda em linha_op
        operacao = strtok(linha_op, " ");   // Pega o conteudo da linh até o espaço

        if (operacao[0] == 'C')
        {
            fprintf(arq_saida, "***************************************************************************\n%c ", operacao[0]);
            inic = strtok(NULL, " "); //Pega o conteudo da linha até o espaço
            fim = strtok(NULL, " ");
            inic = limpa(inic); //Retira caracteres especiais(espaço,ponto, virgulas e etc)
            fim = limpa(fim);
            ninic = atoi(inic); //Converte char em int
            fprintf(arq_saida, "%d  ", ninic);
            nfim = atoi(fim);
            fprintf(arq_saida, "%d \n\n", nfim);
            opcao == ABP ? contador_de_ABP(ninic, nfim, arv_ABP, arq_saida) : contador_de_AVL(ninic, nfim, arv_AVL, arq_saida);
            strtok(NULL, "\n");
            operacao = strtok(NULL, " ");
        }
        else
        {
            fprintf(arq_saida, "\n%c ", operacao[0]);
            pal = strtok(NULL, " ");
            pal = limpa(pal); //Retira caracteres especiais
            fprintf(arq_saida, " %d\n", opcao == ABP ? consulta_em_ABP(arv_ABP, pal)->frequencia : consulta_em_AVL(arv_AVL, pal)->frequencia);
            strtok(NULL, "\n");
            operacao = strtok(NULL, " ");
        }
    }
    fclose(arq_operacoes); //Fecha arquivo de operações
    printf("Operações realizadas com sucesso.\n");

    QueryPerformanceCounter(&end);
    interval = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    fprintf(arq_saida, "\nTempo: %f s", interval);
    
    fclose(arq_saida);     // Fecha arquivo de saída
    printf("Programa encerrado.\n");
    return SUCCESSFUL_RETURN;
}

// Função que retira todos os caracteres especiais da string
char *limpa(char *p)
{
    int i;

    for (i = 0; i < strlen(p); i++)
    {
        if ((p[i] < 48) || (p[i] > 172))
            p[i] = p[i + 1];
    }
    return p;
}

// Retorna o maior de dois inteiros
int maximo(int a, int b)
{
    return (a > b) ? a : b;
}
