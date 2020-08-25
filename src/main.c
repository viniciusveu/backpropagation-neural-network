// Trabalho de Inteligencia Artificial - Prof. Almir O. Artero

#include "lib.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    printf(" =================================================== \n");
    printf("||  - Trabalho Prático - Inteligência Artificial   || \n");
    printf("||  - Professor Almir O. Artero                    || \n");
    printf("||  - Rede Neural Backpropagation                  || \n");
    printf(" =================================================== \n");

    char nome_arquivo[30];
    FILE* arquivo_treino;
    int neur_cam_entrada;
    int neur_cam_saida;
    int neur_cam_oculta;
    int i = 0;
    char val[3];
    char line[150];
    char *valor;
    char *val_ant;
    char final;
    char resp;
    int op;

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

    while (fgets(val, 4, arquivo_treino) != NULL) {    
        i++;
        if (val[2] != ',') {
            neur_cam_entrada = i-1;
            printf("Número de Neurônios na Camada de Entrada: %i \n", neur_cam_entrada);
            fgets(val, 4, arquivo_treino);
            break;
        }
    }

    while (fgets(line, sizeof(line), arquivo_treino)) {
        valor = strtok(line, ",");

        while (valor != NULL) {
            //printf("%s\n",valor);
            val_ant = valor;
            valor = strtok(NULL, ",");
            
        }
        
    }
    neur_cam_saida = val_ant[0] - '0';
    printf("Número de Neurônios na Camada de Saída: %i \n", neur_cam_saida);
    
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

    printf("\nQual função de tranferência deseja utilizar? \n");
    printf("\t 1 - Logística \n");
    printf("\t 2 - Tangente Hiperbólica \n");
    printf("Opção: ");
    scanf("%i", &op);
    printf("Q\n");
    if (op == 1) {
        printf("Função de Transferência escolhida: 1 - Logística \n");
    } else if (op != 2) return printf("Opção inválida :( \n");
    else {
        printf("Função de Transferência escolhida: 2 - Tangente Hiperbólica \n");
    }


    printf("\nFinalizando o programa..... \n");
    fclose(arquivo_treino);
    //system("PAUSE");
    return 0;
};