// Biblioteca

#include "funcoes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <ctype.h>
#include <time.h>


// =========================================== 
//Prototipos

double Logistica(double net);
double TangHiperbolica(double net);
double DerLogistica(double net);
double DerTgHiperbolica(double net);
void ExibeMatrizInt(int **matriz, int lin, int col);
void ExibeMatrizDouble(double **matriz, int lin, int col);
double Treinar(int *valores_entrada, int tam_entrada, double **pesos_o, double **pesos_s, int neur_cam_entrada, int neur_cam_oculta, int neur_cam_saida);
void FuncaoPropagacao(double *nets, double *propag, int quant_neur);
void CalcularErrosSaida(double *erros_s, int desejado, double *saida, int neur_cam_saida, double *net_s);
void CalcularErrosOculta(double *erros_o, double *nets_o, int neur_cam_oculta, double *erros_s, int neur_cam_saida, double **pesos_s);
void AjustaPesosSaida(double **pesos_s, double *erros_s, double *propag_o, int neur_cam_saida, int neur_cam_oculta);
void AjustaPesosOculta(double **pesos_o, double *erros_o, int *valor_e, int neur_cam_entrada, int neur_cam_oculta);
double ErroRede(double *erros_saida, int neur_cam_saida);

// =========================================== 
// Funcoes

double Logistica(double net) {
    return (1.0/(1.0+exp(-net)));
}


double TangHiperbolica(double net) {
    return (1.0-exp(-2.0*net))/(1.0+exp(-2.0*net));
}


double DerLogistica(double net) {
    return exp(-net)/( (1.0+exp(-net))*(1.0+exp(-net)) );
}


double DerTgHiperbolica(double net) {
    return 1.0-pow(DerTgHiperbolica(net), 2.0);
}


void ExibeMatrizInt(int **matriz, int lin, int col) {
    for (int i=0; i<lin; i++) {
        for (int j=0; j<col; j++) {
            printf(" %d |", matriz[i][j]);
        }
        printf("\n");
    }
}


void ExibeMatrizDouble(double **matriz, int lin, int col) {
    printf("Neuronio 1|    2     |    3     |     4    |    5     |     6    |\n");
    for (int i=0; i<lin; i++) {
        for (int j=0; j<col; j++) {
            printf(" %f |", matriz[i][j]);
        }
        printf("\n");
    }
}

// matriz_amostras[linha], neur_cam_entrada+1, pesos_o, pesos_s, neur_cam_entrada, neur_cam_oculta, neur_cam_saida
double Treinar(int *valores_entrada, int tam_entrada, double **pesos_o, double **pesos_s, int neur_cam_entrada, int neur_cam_oculta, int neur_cam_saida) {
    double net;
    double nets_o[neur_cam_oculta];
    double erros_o[neur_cam_oculta];
    double propag_o[neur_cam_oculta];
    double nets_s[neur_cam_saida];
    double erros_s[neur_cam_saida];
    double saida[neur_cam_saida];

    for (int o=0; o<neur_cam_oculta; o++) {
        net = 0;
        for (int neur=0; neur<neur_cam_entrada; neur++) {
            net = net + (valores_entrada[neur] * pesos_o[o][neur]);
            //printf("%lf * %d + \n", pesos_o[o][neur], valores_entrada[neur]);
        }
        nets_o[o] = net;
        //printf("net o = %lf\n\n", nets_o[o]);
    }
    FuncaoPropagacao(nets_o, propag_o, neur_cam_oculta);
    

    for (int s=0; s<neur_cam_saida; s++) {
        net=0;
        for (int neur=0; neur<neur_cam_oculta; neur++) {
            net = net + (propag_o[neur] * pesos_s[s][neur]);
            //printf("%lf * %f + \n", pesos_s[s][neur], propag_o[neur]);
        }
        nets_s[s] = net;
        //printf("net s = %lf\n\n", nets_s[s]);
    }
    FuncaoPropagacao(nets_s, saida, neur_cam_saida);

    printf("Valores p/ propagação: \n");
    for (int i=0; i<neur_cam_oculta; i++) {
        printf("o->s: %e    |   s: %e \n", propag_o[i], saida[i]);
    }

    CalcularErrosSaida(erros_s, valores_entrada[tam_entrada], saida, neur_cam_saida, nets_s);
    CalcularErrosOculta(erros_o, nets_o, neur_cam_oculta, erros_s, neur_cam_saida, pesos_s);
    printf("Erros da camada de saida e oculta: \n");
    for (int i=0; i<neur_cam_saida && i<neur_cam_oculta; i++) {
        printf("Erros Saida: %e | Erros Oculta: %e \n", erros_s[i], erros_o[i]);
    }

    AjustaPesosSaida(pesos_s, erros_s, propag_o, neur_cam_saida, neur_cam_oculta);
    printf("\nMatriz com os pesos da camada de saida refinados: \n");
    ExibeMatrizDouble(pesos_s, neur_cam_saida, neur_cam_oculta);
    AjustaPesosOculta(pesos_o, erros_o, valores_entrada, neur_cam_entrada, neur_cam_oculta);
    printf("\nMatriz com os pesos da camada oculta refinados: \n");
    ExibeMatrizDouble(pesos_o, neur_cam_oculta, neur_cam_entrada);

    return ErroRede(erros_s, neur_cam_saida);
}


void FuncaoPropagacao(double *nets, double *propag, int quant_neur) {
    if(opcoes[0] == 1) { // Logistica
        for (int i=0; i<quant_neur; i++) {
            propag[i] = Logistica(nets[i]);
        }
    } else { //Tg Hiperbolica
        for (int i=0; i<quant_neur; i++) {
            propag[i] = TangHiperbolica(nets[i]);
        }
    }
}

void CalcularErrosSaida(double *erros_s, int desejado, double *saida, int neur_cam_saida, double *nets_s) {
    //printf("%d\n", desejado);
    int desejados[neur_cam_saida];
    desejados[desejado-1] = 1;
    for (int i=0; i<neur_cam_saida; i++) {
        if (desejados[i] != 1) desejados[i] = 0;
        //printf(" %i | ", desejados[i]);
    }
    if (opcoes[0] == 1) 
        for (int i=0; i<neur_cam_saida; i++)
            erros_s[i] = (desejados[i]-saida[i]) * DerLogistica(nets_s[i]);
    else 
        for (int i=0; i<neur_cam_saida; i++)
            erros_s[i] = (desejados[i]-saida[i]) * DerTgHiperbolica(nets_s[i]);
}

void CalcularErrosOculta(double *erros_o, double *nets_o, int neur_cam_oculta, double *erros_s, int neur_cam_saida, double **pesos_s) {
    double soma;
    for (int neur_o=0; neur_o<neur_cam_oculta; neur_o++) {
        soma=0;
        for (int neur_s=0; neur_s<neur_cam_saida; neur_s++) {
            soma = soma + (erros_s[neur_s] * pesos_s[neur_s][neur_o]);
        }
        if (opcoes[0] == 1)
            erros_o[neur_o] = soma * DerLogistica(nets_o[neur_o]);
        else erros_o[neur_o] = soma * DerTgHiperbolica(nets_o[neur_o]);
    }
}

void AjustaPesosSaida(double **pesos_s, double *erros_s, double *propag_o, int neur_cam_saida, int neur_cam_oculta){
    for (int neur_s=0; neur_s<neur_cam_saida ; neur_s++) {
        for (int neur_o=0; neur_o<neur_cam_oculta ; neur_o++) {
            pesos_s[neur_s][neur_o] = pesos_s[neur_s][neur_o] + (erros_s[neur_s] * propag_o[neur_o]);
        }
    }
}

void AjustaPesosOculta(double **pesos_o, double *erros_o, int *valor_e, int neur_cam_entrada, int neur_cam_oculta) {
    for (int neur_o=0; neur_o<neur_cam_oculta; neur_o++) {
        for (int neur_e=0; neur_e<neur_cam_entrada; neur_e++) {
            pesos_o[neur_o][neur_e] = pesos_o[neur_o][neur_e] + (erros_o[neur_o] * valor_e[neur_e]);
        }
    }
}

double ErroRede(double *erros_saida, int neur_cam_saida) {
    double soma = 0;
    for (int er=0; er<neur_cam_saida; er++) soma =+ pow(erros_saida[er], 2.0);
    return soma/2.0;
}