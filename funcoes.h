
#ifndef FUNCOES_H
#define FUNCOES_H

// Variaveis globais
int opcoes[2];  // Onde: opcoes[0] armazena a func de transf escolhida e opcoes[1] a opcao de parada do treinamento
float tx_aprendizado; // n

// Prototipo das funcoes 
void ExibeMatrizInt(int **matriz, int lin, int col);
/* Exibe matriz de inteiros com dimensao lin x col */

void ExibeMatrizDouble(double **matriz, int lin, int col);
/* Exibe matriz de doubles com dimensao lin x col */

void EmbaralharLinhas(int **matriz, int linha);
/* Embaralha a matriz com as amostras para as
classes ficarem desagrupadas e obter um melhor 
ajustamento dos pesos */

double Treinar(int *valores_entrada, int tam_entrada, double **pesos_o, double **pesos_s, int neur_cam_entrada, int neur_cam_oculta, int neur_cam_saida);
/* Faz o treinamento da RNA e retorna o erro da rede */

void FuncaoPropagacao(double *nets, double *propag, int quant_neur);
/* Verifica a Funcao de Propagacao escolhida pelo usuario para o treinamento e para o teste */

double Logistica(double net);
/* Faz o calculo da funcao de transferencia logistica */

double TangHiperbolica(double net);
/* Faz o calculo da funcao de transferencia tangente hiperbolica */

double DerLogistica(double net);
/* Faz o calculo da derivada da funcao logistica para poder calcular o erro da camada de saida e da camada oculta */

double DerTgHiperbolica(double net);
/* Faz o calculo da derivada da funcao tangente hiperbolica para poder calcular o erro da camada de saida e da camada oculta */

void CalcularErrosSaida(double *erros_s, int desejado, double *saida, int neur_s, double *net_s);
/* Faz o calculo do erro dos neuronios da camada de saida */

void CalcularErrosOculta(double *erros_o, double *nets_o, int neur_o, double *erros_s, int neur_s, double **pesos_s);
/* Faz o calculo do erro dos neuronios da camada oculta */

void AjustaPesosSaida(double **pesos_s, double *erros_s, double *propag_o, int neur_s, int neur_o);
/* Ajusta os pesos dos neuronios da camada de saida */

void AjustaPesosOculta(double **pesos_o, double *erros_o, int *valor_e, int neur_e, int neur_o);
/* Ajusta os pesos dos neuronios da camada oculta */

double ErroRede(double *erros_saida, int neur_s);
/* Faz o calculo do erro da rede */

void NetInt(double *nets, int quant_neur, int quant_neur_ant, int *valores, double **pesos);
/* Calcula o net dos neuronios na camada oculta, pois entram valores inteiros */

void NetDouble(double *nets, int quant_neur, int quant_neur_ant, double *valores, double **pesos);
/* Calcula o net dos neuronios na camada de saida, pois entram valores double */

void Testar(int **matriz_confusao, int *valores_entrada, double **pesos_o, double **pesos_s, int neur_cam_entrada, int neur_cam_oculta, int neur_cam_saida);
/* Testa a rede a partir dos pesos encontrados com o conjunto de teste e retorna a matriz de confusao */


#endif /* FUNCOES_H */
