#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "permutacao.h"


//pega o resto da divisao entre a soma os algarismos da matricula e N retornando X
int X(int N, int matricula[N], int tamanho){
    int soma = 0;
    for(int i = 0; i < tamanho; i++) {
        soma += matricula[i];
    }

    int X = soma % N;
    return X;
}
//cria uma matriz com valores aleatórios e diagonal principal = 0
void criaMatrizAleatoria(int N, int matriz[N][N]) {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                matriz[i][j] = (rand() % 10) + 1;// numeros aleatorios entre 1 e 10
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}
//imprime a matriz
void imprimirMatriz(int N, int matriz[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
//Imprime a matriz dentro do Arquivo//
void imprimirMatrizArq(int N, int matriz[N][N],FILE *arq) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            fprintf(arq,"%d ",matriz[i][j]);
        }
        fprintf(arq,"\n");
    }
    fprintf(arq,"\n");
}

//cria o vetor cidades de acordo com N
void vetorCidades(int N, int v[N]){
    for (int i = 0; i < N; i++){
        v[i] = i;
    }
}
//retira a cidade X do vetor de cidades
void vetorCidadesSemX(int v[], int N, int X) {
    if (X < 0 || X >= N) {
        // Verifica se X está dentro dos limites do vetor.
        printf("Indice X fora dos limites do vetor.\n");
        return;
    }
    for (int i = X; i < N - 1; i++) {
        // Move os elementos para preencher a posição de X.
        v[i] = v[i + 1];
    }
    printf("\n");
    for(int i = 0; i < N - 1; i++){
        printf(" %d",v[i]);
    }
    printf("\n");
}

//imprime um vetor
void imprimirVetor(int N, int v[N]){
    for (int i = 0; i < N; i++){
        printf("%d",v[i]);
    }
    printf("\n");
}
//Imprime o vetor dentro do Arquivo//
void imprimirVetorArq(int N, int v[N], FILE * arq){
    fprintf(arq,"\nMelhor Percurso: ");
    for (int i = 0; i < N; i++){
        fprintf(arq,"%d",v[i]);
    }
    printf("\n");
}

//calcula a distancia de cada permutação
void calcularDistancia(int N, int a[N], int X, int *menor_distancia, int *menor_caminho,int P, int matriz[P][P]) {
    int i, dist = 0;
    dist += matriz[X][a[0]];// coloca a cidade X na primeira posição
    for(i = 0; i < N-1; i++) {
        dist += matriz[a[i]][a[i + 1]];
    }
    dist += matriz[a[N - 1]][X];// coloca a cidade X no final do vetor

    if (dist < *menor_distancia) {
        *menor_distancia = dist;
        menor_caminho[0] = X;
        for (i = 0; i < N; i++) {
            menor_caminho[i + 1] = a[i];
        }
        menor_caminho[N + 1] = X;
    }

}

//permutação entre n elementos de um vetor
void permutacaoHEAP(int N, int v[N], int tamanho, int X, int *menor_distancia, int *menor_caminho, int P, int matriz[P][P]) {
    //se o tamanho é 1 imprime a permutação obtida
    if (tamanho == 1) {
        calcularDistancia(N, v, X, menor_distancia, menor_caminho,P, matriz);
    }
    for (int i = 0; i < tamanho; i++) {
        permutacaoHEAP(N, v, tamanho - 1, X, menor_distancia, menor_caminho, P, matriz);
        //se o tamanho é par, troca o primeiro com o ultimo
        if (tamanho % 2 == 1) {
            int temp = v[0];
            v[0] = v[tamanho - 1];
            v[tamanho - 1] = temp;
        }
            //se o tamanho é ímpar, troca o i-ésimo e o ultimo elemento
        else {
            int temp = v[i];
            v[i] = v[tamanho - 1];
            v[tamanho - 1] = temp;
        }
    }
}
//Função Para escolher como a Matriz devera ser preenchida Aleatoria ou por Arquivo//
//Alem de também rodar o programa//
void Menu(int N){

    //definições de variaveis e a parte da escolha//
    int menor_distancia = INT_MAX;
    int matriculas[] = {4,7,0,3,5,7,8,5,5,7,8,6};
    FILE * arq;

    printf("Preenchimento da Matriz:\nDigite : |[1] -> Aleatorio  |---|  [2] -> Por Arquivo|\n");
    int escolha;
    scanf("%d",&escolha);

    //Caso o usuario digite 1, a matriz sera preenchida Aleatoriamente//
    //Nessa parte a tanto o calculo do tempo gasto, quanto a definição do N(Numero de cidades), qunato a parte principal
    // do programa, onde ele chama as funções nescessarias para tudo acontecer.
    if(escolha == 1){
        //Definição de variaveis//
        int matriz1[N][N];
        int cidades[N];
        int menor_caminho[N + 1];
        int x= X(N,matriculas,12);

        // para armazenar o tempo de execução do código
        double time_spent = 0.0;
        // função para medir tempo de execução;
        //Inicio do programa, permutação + calculo da distancia//
        clock_t begin = clock();

        vetorCidades(N,cidades);
        vetorCidadesSemX(cidades,N,x);

        criaMatrizAleatoria(N,matriz1);
        imprimirMatriz(N,matriz1);

        permutacaoHEAP(N-1, cidades,N-1, x, &menor_distancia, menor_caminho,N,matriz1);

        clock_t end = clock();
        // calcula o tempo decorrido encontrando a diferença (end - begin) e
        // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

        //Exibi a saida de dados//
        printf("\nMelhor Percurso: ");
        imprimirVetor(N + 1, menor_caminho);

        printf("Saida de Dados (Aleatorio)\n"
               "|Primeira Cidade  :[%d         ]|\n"
               "|Menor Distancia  :[%d        ]|\n"
               "|Tempo de Execucao:[%f  ]|\n",x,menor_distancia, time_spent);

        //Cria um arquivo 'Resultado' ou altera se ja criado
        // Colocando nele a saida de dados pedido
        arq = fopen("Resultado", "w");
        imprimirMatrizArq(N,matriz1,arq);
        imprimirVetorArq(N + 1, menor_caminho,arq);
        fprintf(arq,"\n"
                    "╔══════════════════════════════════╦══════════╦\n"
                    "║   Saida de Dados (Por Aleatorio) ║Resultados║\n"
                    "╠══════════════════════════════════╬══════════╬\n"
                    "║ Primeira Cidade                  ║%d         ║\n"
                    "║ Menor Distancia                  ║%d        ║\n"
                    "║ Tempo de Execução                ║%f  ║\n"
                    "╚══════════════════════════════════╩══════════╩\n",x,menor_distancia,time_spent);
        fclose(arq);

    }
    //Caso escolha 2, A matriz sera preenchida por meio da leitura de um arquivo//
    else if(escolha == 2){
        //Localização do Arquivo, mais variaveis e definições para ler um arquivo//
        printf("Digite o nome do Arquivo:\n");

        int h,N;
        char Nome_Arquivo[50];
        scanf("%s",Nome_Arquivo);

        FILE * pfile;
        pfile= fopen(Nome_Arquivo, "r");
        fscanf(pfile,"%d",&N);

        //Leitura do arquivo / preenchendo a matriz//
        int matriz1[N][N];
        for(int i =0; i < N;i ++){
            for(int j = 0; j< N; j++){
                if(i != j){
                    fscanf(pfile,"%d",&h);
                    matriz1[i][j] = h;
                }
                else{
                    matriz1[i][j] = 0;
                }
            }
        }
        fclose(pfile);
        imprimirMatriz(N,matriz1);
        //Definição de variaveis que servem de parametro para as funções//
        int cidades[N];
        int menor_caminho[N + 1];
        int x= X(N,matriculas,12);
        // para armazenar o tempo de execução do código
        double time_spent = 0.0;
        // função para medir tempo de execução;

        //Inicio do programa//
        clock_t begin = clock();
        //Permutação + calculo da distancia//

        vetorCidades(N,cidades);
        vetorCidadesSemX(cidades,N,x);
        permutacaoHEAP(N-1, cidades,N-1, x, &menor_distancia, menor_caminho, N, matriz1);

        clock_t end = clock();
        // calcula o tempo decorrido encontrando a diferença (end - begin) e
        // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

        //Exibi a saida de dados esperado//
        printf("\nMelhor Percuso: ");
        imprimirVetor(N + 1, menor_caminho);
        printf("Saida de Dados (Arquivo)\n"
               "|Primeira Cidade  :[%d          ]|\n"
               "|Menor Distancia  :[%d        ]|\n"
               "|Tempo de Execucao:[%f   ]|\n",x,menor_distancia, time_spent);

        //Cria um arquivo 'Resultado' ou altera se ja criado
        // Colocando nele a saida de dados pedido
        arq = fopen("Resultado", "w");
        imprimirMatrizArq(N,matriz1,arq);
        imprimirVetorArq(N + 1, menor_caminho,arq);
        fprintf(arq,"\n"
                    "╔══════════════════════════════════╦══════════╦\n"
                    "║     Saida de Dados (Por Arquivo) ║Resultados║\n"
                    "╠══════════════════════════════════╬══════════╬\n"
                    "║ Primeira Cidade                  ║%d         ║\n"
                    "║ Menor Distancia                  ║%d       ║\n"
                    "║ Tempo de Execução                ║%f  ║\n"
                    "╚══════════════════════════════════╩══════════╩\n"
                    ,x,menor_distancia,time_spent);
        fclose(arq);

    }

    //Caso o usuario digite um numero diferente de 1 ou 2//
    else{
        printf("Escolha Invalida");
    }
}













