#ifndef PERMUTACAO_PERMUTACAO_H
#define PERMUTACAO_PERMUTACAO_H
int Numero = 0;

int X(int N, int matricula[N], int tamanho);
void criaMatrizAleatoria(int N, int matriz[N][N]);
void imprimirMatriz(int N, int matriz[N][N]);
void vetorCidades(int N, int a[N]);
void vetorCidadesSemX(int v[], int N, int X);
void imprimirVetor(int N, int a[N]);
void calcularDistancia(int N, int a[N],int X, int *menor_distancia, int *menor_caminho,int P,int  matriz[P][P]);
void permutacaoHEAP(int N, int v[N], int tamanho, int X, int *menor_distanciam, int *menor_caminho,int P, int matriz[P][P]);
void Menu(int N);
void imprimirVetorArq(int N, int v[N], FILE * arq);
void imprimirMatrizArq(int N, int matriz[N][N], FILE * arq);
#endif //PERMUTACAO_PERMUTACAO_H
