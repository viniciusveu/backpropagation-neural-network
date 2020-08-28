// Trabalho de Inteligencia Artificial - Prof. Almir O. Artero

#include "funcoes.c"

int main(int argc, char *argv[]) {

    // Configurando ambiente
    setlocale(LC_ALL, "Portuguese");

    // Apresentação do programa
    printf(" =================================================== \n");
    printf("||  - Trabalho Prático - Inteligência Artificial   || \n");
    printf("||  - Professor Almir O. Artero                    || \n");
    printf("||  - Rede Neural Backpropagation                  || \n");
    printf(" =================================================== \n");

    // Declaração das variáveis
    char nome_arquivo[30];
    FILE* arquivo_treino;
    int neur_cam_entrada;
    int neur_cam_saida;
    int neur_cam_oculta;
    int i = 0;
    char val[3];
    char line[150];
    char line2[15];
    char *valor;
    char *val_ant;
    char final;
    char resp;  
    int quant_amostras = 0;
    int coluna = 0;
    int linha = 0;
    int **matriz_amostras;
    double erro_max;
    int num_iteracoes;

    // Abrindo o Arquivo
    if(argc == 1) { // Abre arquivo por parâmetro
        printf("Você também pode entrar com o nome do arquivo direto nos argumentos. \nEx: ./RedeNeuralBP treinamento.csv \n\n");
        printf("Entre com o nome do arquivo: \n");
        scanf("%s", nome_arquivo);
        printf("Abrindo arquivo: %s \n", nome_arquivo);

    } else if(argc == 2) {// Necessita do nome do arquivo

        strcpy(nome_arquivo, argv[1]);
        printf("Abrindo arquivo: %s \n", nome_arquivo);
        
    } else return printf("Argumentos inválidos :( \n");

    if(!(arquivo_treino = fopen(nome_arquivo, "r"))) 
        return printf("Arquivo não encontrado! :( \n");
    
    printf("Arquivo aberto. \n");


    // Verificando a quantidade de deuronios na camada de entrada
    while (fgets(val, 4, arquivo_treino) != NULL) {    
        i++;
        if (val[2] != ',') {
            neur_cam_entrada = i-1;
            printf("Número de Neurônios na Camada de Entrada: %i \n", neur_cam_entrada);
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
    quant_amostras--;
    printf("Quantidade de amostras no arquivo : %d \n", quant_amostras);
    neur_cam_saida = val_ant[0] - '0';
    printf("Número de Neurônios na Camada de Saída: %i \n", neur_cam_saida);
    
    // Verificando a quantidade de neuronios na camada oculta
    neur_cam_oculta = abs(sqrt(neur_cam_entrada * neur_cam_saida));
    printf("Número de Neurônios na Camada Oculta: %i \n", neur_cam_oculta);
    printf("Deseja alterar o número de neurônios na camada oculta? [S,n]: ");
    scanf("%c", &resp);
    resp = toupper(resp);
    if (resp == 'S') {
        printf("Entre com o novo número de neurônios na camada oculta: ");
        scanf("%i", &neur_cam_oculta);
    } else if (resp != 'N') return printf("Opção inválida :( \n");
    printf("Número de Neurônios na Camada Oculta: %i \n", neur_cam_oculta);


    // Verificando a função de transferência desejada
    do {
        printf("\nQual função de transferência deseja utilizar? \n");
        printf("\t 1 - Logística \n");
        printf("\t 2 - Tangente Hiperbólica \n");
        printf("Opção: ");
        scanf("%i", &opcoes[0]);
    } while (opcoes[0] != 1 && opcoes[0] != 2);
    
    // Verificando a condição de parada do treinamento
    printf("\nQual condição de parada deseja utilizar? \n");
    printf("\t 1 - Erro Máximo \n");
    printf("\t 2 - Número de Iterações \n");
    printf("Opção: ");
    scanf("%i", &opcoes[1]);

    if (opcoes[1] == 1) {
        printf("Entre com o valor do erro máximo: \n");
        scanf("%lf", &erro_max);
    } else if (opcoes[1] != 2) return printf("Opção inválida :( \n");
    else {
        printf("Entre com o valor máximo de iterações: \n");
        scanf("%d", &num_iteracoes);
    }


    // Criando a matriz com as amostras
    matriz_amostras = (int **) malloc(quant_amostras * sizeof(sizeof(int *)));
    rewind(arquivo_treino);
    fgets(line, sizeof(line), arquivo_treino);
    printf("Linha descartada: %s \n", line);
    //fgets(line, sizeof(line), arquivo_treino);
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
    ExibeMatrizInt(matriz_amostras, quant_amostras, neur_cam_entrada+1);

    // Criando as matrizes com os pesos (linhas: cada nó, coluna: valor respectivo da camada anterior)
    double **pesos_o;
    pesos_o = (double **) malloc(neur_cam_oculta * sizeof(sizeof(double *)));
    double **pesos_s;
    pesos_s = (double **) malloc(neur_cam_saida * sizeof(sizeof(double *)));
    // Gerando pesos aleatórios 
    srand(time(NULL));
    for (int i=0; i<neur_cam_oculta; i++) {
        pesos_o[i] = (double *) malloc(neur_cam_entrada * sizeof(double));
        for (int j=0; j<neur_cam_entrada; j++)
            pesos_o[i][j] = (double)(rand())/(double)(RAND_MAX)*0.1;
    }
    for (int i=0; i<neur_cam_saida; i++) {
        pesos_s[i] = (double *) malloc(neur_cam_oculta * sizeof(double));
        for (int j=0; j<neur_cam_oculta; j++)
            pesos_s[i][j] = (double)(rand())/(double)(RAND_MAX)*0.1;
    }

    // Exibindo as matrizes com seus pesos
    puts("\n");
    printf("Pesos iniciais gerados: \n");
    printf("Camada Oculta: \n");
    ExibeMatrizDouble(pesos_o, neur_cam_oculta, neur_cam_entrada);
    puts("\n");
    printf("Camada de Saída: \n");
    ExibeMatrizDouble(pesos_s, neur_cam_saida, neur_cam_oculta);

    // Loop com o treinamento
    int contador = 0;
    double erro;
    int classe_posicao = neur_cam_entrada;
    for (linha=0; linha<quant_amostras; linha++) {
        erro = Treinar(matriz_amostras[linha], classe_posicao, pesos_o, pesos_s, neur_cam_entrada, neur_cam_oculta, neur_cam_saida);
        contador++;
        if (opcoes[1] == 1) { // erro max
            if( erro <= erro_max) {
                printf("Erro max. atingido! Erro da rede: %e \n", erro);
                break;
            }
        } else { // num iter
            if (contador == num_iteracoes) {
                printf("Número max. de iterações alcançado! Erro da rede: %e\n", erro);
                break;
            }
        }
        //break;
    }
    printf("Num. de iterações realizadas: %d", contador);

    

    // Finalizando o programa
    printf("\nFinalizando o programa..... \n");
    fclose(arquivo_treino);
    return 0;
};