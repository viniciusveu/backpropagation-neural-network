
#ifndef FUNCOES_H
#define FUNCOES_H

int opcoes[2];  

void ExibeMatrizInt(int **matriz, int lin, int col);
void ExibeMatrizDouble(double **matriz, int lin, int col);
double Treinar(int *valores_entrada, int tam_entrada, double **pesos_o, double **pesos_s, int neur_cam_entrada, int neur_cam_oculta, int neur_cam_saida);
void FuncaoPropagacao(double *nets, double *propag, int quant_neur);
double Logistica(double net);
double TangHiperbolica(double net);
double DerLogistica(double net);
double DerTgHiperbolica(double net);
void CalcularErrosSaida(double *erros_s, int desejado, double *saida, int neur_s, double *net_s);
void CalcularErrosOculta(double *erros_o, double *nets_o, int neur_o, double *erros_s, int neur_s, double **pesos_s);
void AjustaPesosSaida(double **pesos_s, double *erros_s, double *propag_o, int neur_s, int neur_o);
void AjustaPesosOculta(double **pesos_o, double *erros_o, int *valor_e, int neur_e, int neur_o);
double ErroRede(double *erros_saida, int neur_s);



#endif /* FUNCOES_H */
