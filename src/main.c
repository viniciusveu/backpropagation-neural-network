// Trabalho de Inteligencia Artificial - Prof. Almir O. Artero

#include "lib.h"

int main(int argc, char *argv[]) {
    printf(" =================================================== \n");
    printf("||  - Trabalho Prático - Inteligência Artificial   || \n");
    printf("||  - Professor Almir O. Artero                    || \n");
    printf("||  - Rede Neural Backpropagation                  || \n");
    printf(" =================================================== \n");

    char nome_arquivo[30];
    FILE* arquivo_treino;

    if(argc == 1) { // Abre arquivo por parâmetro
    
        printf("Você também pode entrar com o nome do arquivo direto nos argumentos. \nEx: ./RedeNeuralBP treinamento.csv \n\n");
        printf("Entre com o nome do arquivo: \n");
        scanf("%s", nome_arquivo);
        printf("Abrindo arquivo: %s \n", nome_arquivo);

    } else if(argc == 2) {// Necessita do nome do arquivo

        strcpy(nome_arquivo, argv[1]);
        printf("Abrindo arquivo: %s \n", nome_arquivo);
        
    } else return printf("Argumentos inválidos :( \n");

    if(arquivo_treino = fopen(nome_arquivo, "r+b")) printf("Foi :D \n");
    else printf("Deu ruim :( \n");

    return 0;
};