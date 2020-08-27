
#ifndef FUNCOES_H
#define FUNCOES_H

int opcoes[2];  

void ExibeMatrizInt(int **matriz, int lin, int col);
void ExibeMatrizDouble(double **matriz, int lin, int col);
void Treinar(int *pesos_e, int e_tam, double **pesos_o, int neur_o, int neur_e, double **pesos_s, int lin_s, int col_s, double erro);
void FuncaoPropagacao(double *nets, double *propag, int quant_neur);
double Logistica(double net);
double TangHiperbolica(double net);
double DerLogistica(double net);
double DerTgHiperbolica(double net);
void CalcularErrosSaida(double *erros_s, int desejado, double *saida, int neur_s, double *propagacao, double *net_s);




#endif /* FUNCOES_H */
