// Trabalho de Inteligencia Artificial - Prof. Almir O. Artero
// Arquivo Principal

// Biblioteca com as função para treino e teste da RNA
#include "funcoes.c"


int main(int argc, char *argv[]) {

    // Configurando ambiente
    setlocale(LC_ALL, "");

    // Apresentação do programa
    printf(" =================================================== \n");
    printf("||        << Rede Neural Backpropagation >>        || \n");
    printf("||                     2020                        || \n");
    printf("||  - Trabalho Pratico - Inteligencia Artificial   || \n");
    printf("||  - Aluno: Vinicius Vedovotto, RA 171257499      || \n");
    printf("||  - Professor: Almir O. Artero                   || \n");
    printf(" =================================================== \n");

    // Declaração das variáveis
    char nome_arquivo_treino[30];
    char nome_arquivo_teste[30];
    FILE* arquivo_treino;
    FILE* arquivo_teste;
    int neur_cam_entrada;
    int neur_cam_saida;
    int neur_cam_oculta;
    int i = 0;
    char n[4];
    char val[3];
    char line[150];
    char *valor;
    char *val_ant;
    char final;
    char resp;
    int quant_amostras = -1;
    int coluna = 0;
    int linha = 0;
    int **matriz_amostras;
    int **matriz_amostras_teste;
    double er_limiar;
    int num_iteracoes;


    // Abrindo o arquivos de teste e de treino
    if(argc == 1) { // Necessita do nome do arquivo
        printf("Voce tambem pode entrar com o nome do arquivo direto nos argumentos. \nEx: ./RedeNeuralBP treinamento.csv teste.csv\n\n");
        printf("Entre com o nome do arquivo de treino: ");
        setbuf(stdin, NULL); scanf("%s", nome_arquivo_treino);
        printf("Abrindo arquivo: %s \n", nome_arquivo_treino);

        printf("Agora entre com o nome do arquivo de teste: ");
        setbuf(stdin, NULL); scanf("%s", nome_arquivo_teste);
        printf("Abrindo arquivo: %s \n", nome_arquivo_teste);

    } else if(argc > 1) { // Abre arquivo por parâmetro

        strcpy(nome_arquivo_treino, argv[1]);
        printf("Abrindo arquivo treino: %s \n", nome_arquivo_treino);

        strcpy(nome_arquivo_teste, argv[2]);
        printf("Abrindo arquivo teste: %s \n", nome_arquivo_teste);

    } else return printf("Argumentos inválidos :( \n");

    if(!(arquivo_treino = fopen(nome_arquivo_treino, "r")))
        return printf("Arquivo treino não encontrado! :( \n");
    if(!(arquivo_teste = fopen(nome_arquivo_teste, "r")))
        return printf("Arquivo teste não encontrado! :( \n");
    printf("Arquivo aberto. \n");


    // Verificando a quantidade de neuronios na camada de entrada
    while (fgets(val, 4, arquivo_treino) != NULL) {
        i++;
        if (val[2] != ',') {
            neur_cam_entrada = i-1;
            fgets(val, 4, arquivo_treino);
            break;
        }
    }

    //Verificando a quantidade de neuronios na camada de saida
    while (fgets(line, sizeof(line), arquivo_treino)) {
        valor = strtok(line, ",");
        while (valor != NULL) {
            val_ant = valor;
            valor = strtok(NULL, ",");
        }
        quant_amostras++;
    }
    neur_cam_saida = val_ant[0] - '0';

    // Verificando a quantidade de neuronios na camada oculta de maneira automatica
    neur_cam_oculta = abs(sqrt(neur_cam_entrada * neur_cam_saida));

    // Exibindo algumas informacoes
    printf("\nInformacoes encontradas no conjunto de amostras: \n");
    printf("Quantidade de amostras no arquivo : %d \n", quant_amostras);
    printf("Numero de Neuronios na Camada de Entrada: %i \n", neur_cam_entrada);
    printf("Numero de Neuronios na Camada de Saida: %i \n", neur_cam_saida);
    printf("Numero de Neurunios na Camada Oculta: %i \n\n", neur_cam_oculta);

    // Configuração manual do numero de neuronios na camada oculta
    printf("Deseja alterar o numero de neuronios na camada oculta? [S,n]: ");
    setbuf(stdin, NULL); scanf("%c", &resp);
    resp = toupper(resp);
    if (resp == 'S') {
        printf("Entre com o novo numero de neuronios na camada oculta: ");
        setbuf(stdin, NULL); scanf("%i", &neur_cam_oculta);
    } else if (resp != 'N') return printf("Opcao invalida :( \n");
    printf("Numero de Neuronios na Camada Oculta: %i \n", neur_cam_oculta);


    // Verificando a função de transferência desejada
    do {
        printf("\nQual funcao de transferencia deseja utilizar? \n");
        printf("\t 1 - Logistica \n");
        printf("\t 2 - Tangente Hiperbolica \n");
        printf("Opcao: ");
        setbuf(stdin, NULL); scanf("%i", &opcoes[0]);
    } while (opcoes[0] != 1 && opcoes[0] != 2);

    // Verificando a condição de parada do treinamento
    printf("\nQual condicao de parada deseja utilizar? \n");
    printf("\t 1 - Erro Maximo \n");
    printf("\t 2 - Numero de Iteracoes \n");
    printf("Opcao: ");
    setbuf(stdin, NULL); scanf("%i", &opcoes[1]);

    if (opcoes[1] == 1) { // Erro max.
        printf("Entre com o valor do erro maximo: ");
        setbuf(stdin, NULL); scanf("%lf", &er_limiar);
    } else if (opcoes[1] != 2) return printf("Opcao invalida :( \n");
    else {  // Quant iteracoes
        printf("Entre com o valor maximo de iteracoes: ");
        setbuf(stdin, NULL); scanf("%d", &num_iteracoes);
    }

    // Setando tx de aprendizado (n)                ;
    printf("Entre com uma taxa de aprendizado [ex.: 0,01]: ");
    setbuf(stdin, NULL); scanf("%f", &tx_aprendizado);

    // Criando a matriz com as amostras
    matriz_amostras = (int **) malloc(quant_amostras * sizeof(sizeof(int *)));
    rewind(arquivo_treino);
    fgets(line, sizeof(line), arquivo_treino);
    while (fgets(line, sizeof(line), arquivo_treino)) {
        valor = strtok(line, ",");
        matriz_amostras[linha] = (int *) malloc((neur_cam_entrada+1) * sizeof(int));
        while (valor != NULL && coluna <= neur_cam_entrada) {
            matriz_amostras[linha][coluna] = atoi(valor);
            valor = strtok(NULL, ",");
            coluna++;
        }
        coluna = 0;
        linha++;
        if(linha == quant_amostras) break;
    }

    EmbaralharLinhas(matriz_amostras, quant_amostras); // Embaralhar linhas para desagrupar as classes
    // ExibeMatrizInt(matriz_amostras, quant_amostras, neur_cam_entrada+1);

    // Criando as matrizes com os pesos (linhas: cada nó, coluna: valor respectivo da camada anterior)
    double **pesos_o;
    pesos_o = (double **) malloc(neur_cam_oculta * sizeof(sizeof(double *)));
    double **pesos_s;
    pesos_s = (double **) malloc(neur_cam_saida * sizeof(sizeof(double *)));
    // Gerando pesos aleatórios [-0.5, +0.5]
    srand(time(NULL));
    for (int i=0; i<neur_cam_oculta; i++) {
        pesos_o[i] = (double *) malloc(neur_cam_entrada * sizeof(double));
        for (int j=0; j<neur_cam_entrada; j++)
            pesos_o[i][j] = (double)(rand())/(double)(RAND_MAX)*0.5 - (double)(rand())/(double)(RAND_MAX)*0.5;
    }
    for (int i=0; i<neur_cam_saida; i++) {
        pesos_s[i] = (double *) malloc(neur_cam_oculta * sizeof(double));
        for (int j=0; j<neur_cam_oculta; j++)
            pesos_s[i][j] = (double)(rand())/(double)(RAND_MAX)*0.5 - (double)(rand())/(double)(RAND_MAX)*0.5;
    }


    // Exibindo as matrizes com seus pesos
    puts("\n");
    printf("Pesos iniciais gerados: \n");
    printf("Camada Oculta: \n");
    ExibeMatrizDouble(pesos_o, neur_cam_oculta, neur_cam_entrada);
    puts("\n");
    printf("Camada de Saida: \n");
    ExibeMatrizDouble(pesos_s, neur_cam_saida, neur_cam_oculta);

    // Loop com o treinamento  =====================================================================================
    int contador = 0;
    double erro; // Erro da rede
    int classe_posicao = neur_cam_entrada;
    printf("\nTreinando . . .");
    do {    // Treina o conjunto de amostras até o limite estabelecido
        for (linha=0; linha<quant_amostras; linha++) // Passa toda a amostra no Backpropagation
            erro = Treinar(matriz_amostras[linha], classe_posicao, pesos_o, pesos_s, neur_cam_entrada, neur_cam_oculta, neur_cam_saida);
        contador++;
        printf(" . ");
        if (opcoes[1] == 1) { // erro max
            if( erro <= er_limiar) {
                printf("\nErro max. atingido! Erro da rede: %e \n", erro);
                break;
            }
        } else { // num iter
            if (contador == num_iteracoes) {
                printf("\nNumero max. de iteracoes alcancado! Erro da rede: %f\n", erro);
                break;
            }
        }
    } while (1);

    // Exibe os pesos encontrados no treinamento
    printf("O treinamento terminou! :D \n\n");
    printf("Num. de iteracoes realizadas: %d \n\n", contador);
    printf("Pesos finais obtidos: \n");
    printf("Camada Oculta: \n");
    ExibeMatrizDouble(pesos_o, neur_cam_oculta, neur_cam_entrada);
    puts("\n");
    printf("Camada de Saida: \n");
    ExibeMatrizDouble(pesos_s, neur_cam_saida, neur_cam_oculta);
    puts("\n");

    // Teste da rede
    printf("\nSeguindo para os testes da RNA Backpropagation... \n");

    quant_amostras = -1;
    while (fgets(line, sizeof(line), arquivo_teste)) quant_amostras++;
    printf("Quantidade de amostras para o teste: %d \n", quant_amostras);

    // Criando a matriz com as amostras
    matriz_amostras_teste = (int **) malloc(quant_amostras * sizeof(sizeof(int *)));
    rewind(arquivo_teste); linha = coluna = 0;
    fgets(line, sizeof(line), arquivo_teste);
    while (fgets(line, sizeof(line), arquivo_teste)) {
        valor = strtok(line, ",");
        matriz_amostras_teste[linha] = (int *) malloc((neur_cam_entrada+1) * sizeof(int));
        while (valor != NULL && coluna < neur_cam_entrada+1) {
            matriz_amostras_teste[linha][coluna] = atoi(valor);
            valor = strtok(NULL, ",");
            coluna++;
        }
        coluna = 0;
        linha++;
        if(linha == quant_amostras) break;
    }
    //ExibeMatrizInt(matriz_amostras_teste, quant_amostras, neur_cam_entrada+1);

    //Criando a matriz de confusão
    int **matriz_confusao = (int **) malloc(neur_cam_saida * sizeof(sizeof(int *)));
    for (i=0; i<neur_cam_saida; i++) {
        matriz_confusao[i] = (int *) malloc(neur_cam_saida * sizeof(int));
        for (int j=0; j<neur_cam_saida; j++) matriz_confusao[i][j] = 0;
    }

    for (linha=0; linha<quant_amostras; linha++) // Testando a rede para cada amostra do conjunto de teste
        Testar(matriz_confusao, matriz_amostras_teste[linha], pesos_o, pesos_s, neur_cam_entrada, neur_cam_oculta, neur_cam_saida);

    // Exibindo matriz de confusão
    printf("\nMatriz de confusao obtida: \n");
    ExibeMatrizInt(matriz_confusao, neur_cam_saida, neur_cam_saida);

    // Finalizando o programa
    printf("\nFinalizando o programa..... \n");
    fclose(arquivo_treino);
    fclose(arquivo_teste);

    system("PAUSE");
    return 0;
};
