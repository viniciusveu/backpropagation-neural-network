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
void ExibeMatrizInt(int **matriz, int lin, int col);
void ExibeMatrizDouble(double **matriz, int lin, int col);
void Treinar(int *pesos_e, int e_tam, double **pesos_o, int neur_o, int neur_e, double **pesos_s, int lin_s, int col_s, double erro);
void FuncaoPropagacao(double *nets, double *propag, int quant_neur);



// =========================================== 
// Funcoes

double Logistica(double net) {
    return (1.0/(1.0+exp(-net)));
}


double TangHiperbolica(double net) {
    return (1.0-exp(-2.0*net))/(1.0+exp(-2.0*net));
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


void Treinar(int *valor_e, int e_tam, double **pesos_o, int neur_o, int neur_e, double **pesos_s, int lin_s, int col_s, double erro) {
    double net;
    double nets[neur_o];
    double propag[neur_o];
    
    for (int o=0; o<neur_o; o++) {
        net = 0;
        for (int neur=0; neur<neur_e; neur++) {
            net = net + (valor_e[neur] * pesos_o[o][neur]);
            printf("%lf * %d + \n", pesos_o[o][neur], valor_e[neur]);
        }
        nets[o] = net;
        printf("net = %lf\n\n", nets[o]);
        //scanf("%c", &tt);
    }

    FuncaoPropagacao(nets, propag, neur_o);

    // for (int i=0; i<neur_o; i++) {
    //     printf("nets: %f\n", nets[i]);
    // }
    
    for (int i=0; i<neur_o; i++) {
        printf("Valores p/ propagação de o -> s: %lf\n", propag[i]);
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
