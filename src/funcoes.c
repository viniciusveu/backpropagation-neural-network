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
void Treinar(int *pesos_e, int e_tam, double **pesos_o, int neur_o, int neur_e, double **pesos_s, int lin_s, int col_s, double erro);
void FuncaoPropagacao(double *nets, double *propag, int quant_neur);
void CalcularErrosSaida(double *erros_s, int desejado, double *saida, int neur_s, double *propagacao, double *net_s);



// =========================================== 
// Funcoes

double Logistica(double net) {
    //printf("net: %lf  exp(-net):  %e  (1.0+exp(-net))  %e \n", net, exp(-net), (1+exp(-net)));
    //printf("Result: %e \n\n", (1.0/(1.0+exp(-net))));
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


void Treinar(int *valor_e, int e_tam, double **pesos_o, int neur_o, int neur_e, double **pesos_s, int neur_s, int neur_oc, double erro) {
    double net;
    double nets_o[neur_o];
    double nets_s[neur_s];
    double propag_o[neur_o];
    double saida[neur_s];

    for (int o=0; o<neur_o; o++) {
        net = 0;
        for (int neur=0; neur<neur_e; neur++) {
            net = net + (valor_e[neur] * pesos_o[o][neur]);
            printf("%lf * %d + \n", pesos_o[o][neur], valor_e[neur]);
        }
        nets_o[o] = net;
        printf("net o = %lf\n\n", nets_o[o]);
        //scanf("%c", &tt);
    }
    FuncaoPropagacao(nets_o, propag_o, neur_o);
    

    for (int s=0; s<neur_s; s++) {
        net=0;
        for (int neur=0; neur<neur_o; neur++) {
            net = net + (propag_o[neur] * pesos_s[s][neur]);
            printf("%lf * %f + \n", pesos_s[s][neur], propag_o[neur]);
        }
        nets_s[s] = net;
        printf("net s = %lf\n\n", nets_s[s]);
    }
    FuncaoPropagacao(nets_s, saida, neur_s);

    printf("Valores p/ propagação: \n");
    for (int i=0; i<neur_o; i++) {
        printf("o->s: %e    |   s: %e \n", propag_o[i], saida[i]);
    }

    double erros_s[neur_s];
    CalcularErrosSaida(erros_s, valor_e[e_tam-1], saida, neur_s, propag_o, nets_s);
    printf("Erros da camada de saida: \n");
    for (int i=0; i<neur_s; i++) {
        printf("Erro: %e \n", erros_s[i]);
    }
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

void CalcularErrosSaida(double *erros_s, int desejado, double *saida, int neur_s, double *propagacao, double *nets_s) {
    printf("%d\n", desejado);
    int desejados[neur_s];
    desejados[desejado-1] = 1;
    for (int i=0; i<desejado; i++) 
        if (desejados[i] != 1) desejados[i] = 0;
    
    if (opcoes[0] == 1) 
        for (int i=0; i<neur_s; i++)
            erros_s[i] = (desejados[i]-saida[i]) * DerLogistica(nets_s[i]);
    else 
        for (int i=0; i<neur_s; i++)
            erros_s[i] = (desejados[i]-saida[i]) * DerTgHiperbolica(nets_s[i]);
}


