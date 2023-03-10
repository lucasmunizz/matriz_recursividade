//NOME: LUCAS MUNIZ DE LIMA -- NrUSP: 13728941

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void imprimirMatriz(int tamanho, int matriz[tamanho][tamanho]);
int recursar(int linhaIni, int colunaIni, int respAux, int resposta[respAux][2], int tamanhoMatriz, char matriz[tamanhoMatriz][tamanhoMatriz], int tamanho);
void criarSaida (FILE * arq, int respAux, int resposta[respAux][2]);
void lerArq(FILE * arq, int tamanho, char matriz[tamanho][tamanho], char * arg);


void imprimirMatriz(int tamanho, int matriz[tamanho][tamanho]){
    for (int i = 0; i < tamanho; i++){
        for (int j= 0; j < tamanho; j++){
            printf("%d", matriz[i][j]);
        }
        printf("\n");
    }
}


int recursar(int linhaIni, int colunaIni, int respAux, int resposta[respAux][2], int tamanhoMatriz, char matriz[tamanhoMatriz][tamanhoMatriz], int tamanho){

    if (tamanho == 1){
        if (matriz[linhaIni][colunaIni] == 0){ 
            resposta[0][1] = resposta[0][1] + 1; //elemento unitário da cor preta
        } else {
            resposta[0][0] = resposta[0][0] + 1; //elemento unitário da cor branca
        }
        return matriz[linhaIni][colunaIni];
    }

    //irá dividir até o tamanho ser 1   
    int InfE = recursar(linhaIni + tamanho / 2, colunaIni, respAux,  resposta, tamanhoMatriz, matriz, tamanho / 2); //Matriz InferiorEsquerda
    int SupE = recursar(linhaIni, colunaIni, respAux, resposta, tamanhoMatriz, matriz, tamanho / 2); //Matriz SuperiorEsquerda
    int InfD = recursar(linhaIni + tamanho / 2, colunaIni + tamanho / 2, respAux, resposta, tamanhoMatriz, matriz, tamanho / 2); //Matriz InferiorDireita
    int SupD = recursar(linhaIni, colunaIni + tamanho / 2, respAux, resposta, tamanhoMatriz, matriz, tamanho / 2); //Matriz SuperiorDireita

    int juntarMat = SupE + SupD + InfE + InfD;
    int respPos = (int)log2(tamanho);

    if (juntarMat == tamanho * tamanho){ //Quadrante maximal branco
        resposta[respPos][0] = resposta[respPos][0] + 1; //adiciono um
        resposta[respPos - 1][0] = resposta[respPos - 1][0] - 4; //removo uma (quatro valores unitarios) ordem inferior, pois na verdade é uma ordem superior
      
    } else if (juntarMat == 0){ //Se a junção de todas as partições de matrizes dar 0, é porque é preto
        resposta[respPos][1] = resposta[respPos][1] + 1; //mesmo caso anterior
        resposta[respPos - 1][1] = resposta[respPos - 1][1] - 4;
    }

    return InfE + SupE + InfD + SupD;

}

void lerArq(FILE * arq, int tamanho, char matriz[tamanho][tamanho], char * arg){

    char c;
    int i = 0;
    int j = 0;

    arq = fopen(arg, "r");
    
    for (i = 0; i < tamanho; i++){
         for (j = 0; j < tamanho; j++){
            c = fgetc(arq);
            if (c == '\n') c = fgetc(arq);
            if (c == '1') matriz[i][j] = 1;
            else if (c == '0') matriz[i][j] = 0;
        }
    }

    printf(" \n");
    fclose(arq);

}

void criarSaida (FILE * arq, int respAux, int resposta[respAux][2]){
    arq = fopen("saida.txt", "w");

    for (int i = respAux - 1; i >= 0; i--){
        int n = (int)pow(2,i);
        fprintf(arq,"%dx%d %d %d\n", n, n, resposta[i][0], resposta[i][1]);
    }

    fclose(arq);

}


int main (int argc, char *argv[]){

    int tamanho = atoi(argv[1]); //- 48;
    char matriz[tamanho][tamanho];

    //LEITURA DO ARQUIVO
    FILE * arq = fopen(argv[2], "r");
    char * arg = argv[2];
    lerArq(arq,tamanho,matriz,arg);

    //imprimirMatriz(tamanho, matriz);

    //criar um vetor bidimensional pra resposta
    int respAux = (int)log2(tamanho) + 1;
    int resposta[respAux][2];

    for (int i = 0; i < respAux; i++) {
        resposta[i][0] = 0; //cor branca
        resposta[i][1] = 0; //cor preta
    }

    //chamar a função recursiva, primeira parte da divisão e conquista
    recursar(0,0,respAux,resposta,tamanho,matriz,tamanho);

    //Após todo o procedimento, criar o arquivo de resposta
    criarSaida(arq,respAux,resposta);

    return 0;
}
