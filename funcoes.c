// Biblioteca

#include "funcoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>


// ===========================================
//Cabeçalho das funcoes

double Logistica(double net);
double TangHiperbolica(double net);
double DerLogistica(double net);
double DerTgHiperbolica(double net);
void ExibeMatrizInt(int **matriz, int lin, int col);
void ExibeMatrizDouble(double **matriz, int lin, int col);
void EmbaralharLinhas(int **matriz, int linha);
double Treinar(int *valores_entrada, int tam_entrada, double **pesos_o, double **pesos_s, int neur_cam_entrada, int neur_cam_oculta, int neur_cam_saida);
void NetInt(double *nets, int quant_neur, int quant_neur_ant, int *valores, double **pesos);
void NetDouble(double *nets, int quant_neur, int quant_neur_ant, double *valores, double **pesos);
void FuncaoPropagacao(double *nets, double *propag, int quant_neur);
void CalcularErrosSaida(double *erros_s, int desejado, double *saida, int neur_cam_saida, double *net_s);
void CalcularErrosOculta(double *erros_o, double *nets_o, int neur_cam_oculta, double *erros_s, int neur_cam_saida, double **pesos_s);
void AjustaPesosSaida(double **pesos_s, double *erros_s, double *propag_o, int neur_cam_saida, int neur_cam_oculta);
void AjustaPesosOculta(double **pesos_o, double *erros_o, int *valor_e, int neur_cam_entrada, int neur_cam_oculta);
double ErroRede(double *erros_saida, int neur_cam_saida);
bool VerificaResultado(int **matriz_confusao, int classe, int quant_neur_e, double *saida, int quant_neur_s);
void Testar(int **matriz_confusao, int *valores_entrada, double **pesos_o, double **pesos_s, int neur_cam_entrada, int neur_cam_oculta, int neur_cam_saida);

// ===========================================
// Funcoes

double Logistica(double net) {
    return (1.0/(1.0+exp(-net)));
}


double TangHiperbolica(double net) {
    return (1.0-exp(-2.0*net))/(1.0+exp(-2.0*net));
}


double DerLogistica(double net) {
    return (exp(-net)/( (1.0+exp(-net))*(1.0+exp(-net)) ));
}


double DerTgHiperbolica(double net) {
    return 1.0-pow(TangHiperbolica(net), 2.0);
}


void ExibeMatrizInt(int **matriz, int lin, int col) {
    for (int i=0; i<lin; i++) {
        for (int j=0; j<col; j++) {
            printf(" %3d |", matriz[i][j]);
        }
        printf("\n");
    }
}


void ExibeMatrizDouble(double **matriz, int lin, int col) {
    printf("Neuronio 1 |     2     |     3     |     4     |     5     |     6     |     7     | ... \n");
    for (int i=0; i<lin; i++) {
        for (int j=0; j<col; j++)
            printf(" %9f |", matriz[i][j]);
        printf("\n");
    }
}

void EmbaralharLinhas(int **matriz, int linha) {
    int *linha_aux;
    int posicao;

    srand(time(NULL));
    for (int l=0; l<linha; l++) {
        posicao = (int) rand()%linha;
        linha_aux = matriz[l];
        matriz[l] = matriz[posicao];
        matriz[posicao] = linha_aux;
    }
}


double Treinar(int *valores_entrada, int tam_entrada, double **pesos_o, double **pesos_s, int neur_cam_entrada, int neur_cam_oculta, int neur_cam_saida) {
    double nets_o[neur_cam_oculta];
    double erros_o[neur_cam_oculta];
    double propag_o[neur_cam_oculta];

    double nets_s[neur_cam_saida];
    double erros_s[neur_cam_saida];
    double saida[neur_cam_saida];

    NetInt(nets_o, neur_cam_oculta, neur_cam_entrada, valores_entrada, pesos_o);
    FuncaoPropagacao(nets_o, propag_o, neur_cam_oculta);

    NetDouble(nets_s, neur_cam_saida, neur_cam_oculta, propag_o, pesos_s);
    FuncaoPropagacao(nets_s, saida, neur_cam_saida);

    CalcularErrosSaida(erros_s, valores_entrada[tam_entrada], saida, neur_cam_saida, nets_s);
    CalcularErrosOculta(erros_o, nets_o, neur_cam_oculta, erros_s, neur_cam_saida, pesos_s);

    AjustaPesosSaida(pesos_s, erros_s, propag_o, neur_cam_saida, neur_cam_oculta);
    AjustaPesosOculta(pesos_o, erros_o, valores_entrada, neur_cam_entrada, neur_cam_oculta);

    return ErroRede(erros_s, neur_cam_saida);
}

void NetInt(double *nets, int quant_neur, int quant_neur_ant, int *valores, double **pesos) {
    double net;

    for (int i=0; i<quant_neur; i++) {
        net = 0;
        for (int j=0; j<quant_neur_ant; j++)
            net = net + (valores[j] * pesos[i][j]);
        nets[i] = net;
    }
}

void NetDouble(double *nets, int quant_neur, int quant_neur_ant, double *valores, double **pesos) {
    double net;

    for (int i=0; i<quant_neur; i++) {
        net = 0;
        for (int j=0; j<quant_neur_ant; j++)
            net = net + (valores[j] * pesos[i][j]);
        nets[i] = net;
    }
}


void FuncaoPropagacao(double *nets, double *propag, int quant_neur) {
    if(opcoes[0] == 1) { // Logistica
        for (int i=0; i<quant_neur; i++)
            propag[i] = Logistica(nets[i]);
    } else { //Tg Hiperbolica
        for (int i=0; i<quant_neur; i++)
            propag[i] = TangHiperbolica(nets[i]);
    }
}

void CalcularErrosSaida(double *erros_s, int desejado, double *saida, int neur_cam_saida, double *nets_s) {
    int desejados[neur_cam_saida];

    if (opcoes[0] == 1) {  // Logistica
        for (int i=0; i<neur_cam_saida; i++)  desejados[i] = 0;
        desejados[desejado-1] = 1;
        for (int i=0; i<neur_cam_saida; i++)
            erros_s[i] = (desejados[i]-saida[i]) * DerLogistica(nets_s[i]);;
    }
    else {// Tg. Hiperbolica
        for (int i=0; i<neur_cam_saida; i++)  desejados[i] = -1;
        desejados[desejado-1] = 1;
        for (int i=0; i<neur_cam_saida; i++)
            erros_s[i] = (desejados[i]-saida[i]) * DerTgHiperbolica(nets_s[i]);
    }

}

void CalcularErrosOculta(double *erros_o, double *nets_o, int neur_cam_oculta, double *erros_s, int neur_cam_saida, double **pesos_s) {
    double soma;

    for (int neur_o=0; neur_o<neur_cam_oculta; neur_o++) {
        soma=0.0;
        for (int neur_s=0; neur_s<neur_cam_saida; neur_s++)
            soma = soma + (erros_s[neur_s] * pesos_s[neur_s][neur_o]);

        if (opcoes[0] == 1)
            erros_o[neur_o] = soma * DerLogistica(nets_o[neur_o]);
        else erros_o[neur_o] = soma * DerTgHiperbolica(nets_o[neur_o]);
    }
}

void AjustaPesosSaida(double **pesos_s, double *erros_s, double *propag_o, int neur_cam_saida, int neur_cam_oculta){
    for (int neur_s=0; neur_s<neur_cam_saida ; neur_s++)
        for (int neur_o=0; neur_o<neur_cam_oculta ; neur_o++)
            pesos_s[neur_s][neur_o] = pesos_s[neur_s][neur_o] + (tx_aprendizado * erros_s[neur_s] * propag_o[neur_o]);
}

void AjustaPesosOculta(double **pesos_o, double *erros_o, int *entrada, int neur_cam_entrada, int neur_cam_oculta) {
    for (int neur_o=0; neur_o<neur_cam_oculta; neur_o++)
        for (int neur_e=0; neur_e<neur_cam_entrada; neur_e++)
            pesos_o[neur_o][neur_e] = pesos_o[neur_o][neur_e] + (tx_aprendizado * erros_o[neur_o] * entrada[neur_e]);
}

double ErroRede(double *erros_saida, int neur_cam_saida) {
    double soma = 0;

    for (int er=0; er<neur_cam_saida; er++)
        soma = soma + (erros_saida[er] * erros_saida[er]);

    return soma/2.0;
}

void Testar(int **matriz_confusao, int *valores_entrada, double **pesos_o, double **pesos_s, int neur_cam_entrada, int neur_cam_oculta, int neur_cam_saida) {
    double nets_o[neur_cam_oculta];
    double propag_o[neur_cam_oculta];

    double nets_s[neur_cam_saida];
    double saida[neur_cam_saida];

    NetInt(nets_o, neur_cam_oculta, neur_cam_entrada, valores_entrada, pesos_o);
    FuncaoPropagacao(nets_o, propag_o, neur_cam_oculta);

    NetDouble(nets_s, neur_cam_saida, neur_cam_oculta, propag_o, pesos_s);
    FuncaoPropagacao(nets_s, saida, neur_cam_saida);

    VerificaResultado(matriz_confusao, valores_entrada[neur_cam_entrada], neur_cam_entrada, saida, neur_cam_saida);
}

bool VerificaResultado(int **matriz_confusao, int classe, int quant_neur_e, double *saida, int quant_neur_s) {
    int desejado[quant_neur_s];
    desejado[classe-1] = 1;
    int maior = 0;

    if (opcoes[0] == 1) {
        for (int i=0; i<quant_neur_s; i++)
            if(desejado[i] != 1) desejado[i] = 0;
    } else {
        for (int i=0; i<quant_neur_s; i++)
            if(desejado[i] != 1) desejado[i] = -1;
    }

    for (int i=1; i<quant_neur_s; i++)
        if (saida[i] > saida[maior]) maior = i;

    matriz_confusao[classe-1][maior]++;

    if (classe-1 == maior) return true;
    else return false;
}
