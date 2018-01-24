#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



//aloca a peca atual
int ** AlocaAtual(){
    int ** tmp;
    int i;
    tmp = malloc(3 * sizeof(char *));
    for(i=0; i<3; i++){
        tmp[i] = malloc(3 * sizeof(char));
    }
    printf("alocouAtual\n");
    return (tmp);
}




//aloca o vetor vetmov que contem os movimentos da peca atual
int * alocaMov(int quant){
    int * tmp;
    tmp = malloc(quant * sizeof(char));
    printf("alocouMov\n");
    return (tmp);
}




//aloca a tela
int ** alocaTela(int linhas, int colunas){
    int ** tmp;
    int i,j;
    tmp = malloc(linhas * sizeof(char *));
    for(i=0; i<linhas; i++){
        tmp[i] = malloc(colunas * sizeof(char));
    }
    printf("AlocouTela\n");
    return(tmp);
}




//libera a peca atual
void liberaAtual(char ** pecaatual){
    free(pecaatual);
    printf("liberouAtual\n");
}




//libera os movimentos
void liberaMov(char *vetmov){
    free(vetmov);
    printf("liberouMov\n");
}




//libera a tela
void liberaTela(char ** tela){
    free(tela);
    printf("liberouTela\n");
}




void leArquivo(FILE *arq, int *linhas, int *colunas, int *tempo, int *quantpecas){

    fscanf(arq, "%d %d", linhas, colunas);
    fscanf(arq, "%d", tempo);
    fscanf(arq, "%d", quantpecas);

    printf("linhas arq: %d\ncolunas arq: %d\n", *linhas, *colunas);
    printf("intervalo de tempo arq: %d\n", *tempo);
    printf("quantidade de pecas arq: %d\n", *quantpecas);

}




int lePecas(FILE *arq, int *colunapecaatual, char ** pecaatual, int *movimentospecaatual){
    int i,j;
    char cache;
    //FILE *arq;
    //arq = fopen("entrada.txt", "r");
    // cria uma matriz de 2 dimensoes, sendo 1 para guardar as peças e outra para guardar os movimentos (acho que nao vou fazer)
    // acabei criando 1 vetor para guardar os movimentos, e resolvi chamar a funcao de ler pecas para cada peca do jogo
    fscanf(arq, "%d", colunapecaatual);
    for(i=0; i<3; i++){
        fscanf(arq, "%c", &cache);
        for(j=0; j<3; j++){

            fscanf(arq, "%c", &pecaatual[j][i]);
            printf("char [%d][%d] da peca pec: %c\n",i,j,pecaatual[j][i]);
        }
    }

    int pecaint[3][3];
    //mudar peca atual pra int em ascii
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            pecaint[i][j] = (int) pecaatual[j][i];
        }
    }
    //printar peca int
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            printf("%d ", pecaint[i][j]);
        }
        printf("\n");
    }



    fscanf(arq, "%d", movimentospecaatual);
    printf("colunas primeira peca pec: %d\n", *colunapecaatual);
    printf("peca atual pec:\n");
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            printf("%c", pecaatual[j][i]);
        }
        printf("\n");
    }
    printf("quant movimentos da peca pec: %d\n", *movimentospecaatual);

    return(pecaint);
}




void leMovimentos(FILE *arq, int movimentospecaatual, char *vetmov){
    char cache;
    int i;

    for(i=0; i<movimentospecaatual; i++){
        fscanf(arq, "%c", &cache);
        fscanf(arq, "%c", &vetmov[i]);
        printf("vetmov[%d] = %c\n",i,vetmov[i]);
    }

}




void setarpeca(char **tela, int **pecaatual, int colunapecaatual){
    /*int i,j,k=0;
    for(i=0; i<3; i++){
        for(j=colunapecaatual; j<colunapecaatual+k; j++){
            tela[i][j] = pecaatual[i][k];
            if(k<3)
                k++;
        }
    }

    /*printf("tela:\n");
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            printf("%c\n", tela[i][j]);
        }
    }*/
}




void jogarPeca(char **tela, char *vetmov, char **pecaatual){

}




void printarTela(char **tela, int linhas, int colunas){
    int i,j;
    //preencher tela
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            tela[i][j] = 46;
        }
    }

    //printa tela
    printf("TELA:\n");
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            printf("%c", tela[i][j]);
        }
        printf("\n");
    }
}




void descerUm(){

}




int main(){
    FILE *arq = fopen("entrada.txt", "r");
    int linhas, colunas, tempo, quantpecas, colunapecaatual, movimentospecaatual;
    int i,j,k;
    int **pecaint;
    //char pecaatual[3][3];
    char ** pecaatual, ** tela;
    char * vetmov;
    leArquivo(arq, &linhas, &colunas, &tempo, &quantpecas);
    //fazer funcao pra alocar essa matriz
    tela = alocaTela(linhas, colunas);
    pecaatual = AlocaAtual();

    //fazer laco for para quantidade de pecas
    pecaint = lePecas(arq, &colunapecaatual, pecaatual, &movimentospecaatual);

    printf("peca int main:\n");
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            printf("%c ", pecaint[i][j]);
        }
        printf("\n");
    }
    //vetmov eh o vetor que aloca os movimentos da peca atual
    vetmov = alocaMov(movimentospecaatual);
    leMovimentos(arq, movimentospecaatual, vetmov);
    //fazer laco para jogar a quantidade de movimentos
    setarpeca(tela, pecaint, colunapecaatual);
    printarTela(tela, linhas, colunas);
    /*for(k=0; k<movimentospecaatual; k++){
        jogarPeca(tela, vetmov, pecaatual);
        //printarTela();
        descerUm();
    }*/
    //debug
    for(i=0; i<movimentospecaatual; i++){
        printf("vetmov[%d] main = %c\n",i,vetmov[i]);
    }
    //fechar laco for dos movimentos
    printf(""); //SEM ISSO AQUI BUGA NAO SEI PQ MAS NAO TIRA
    liberaMov(vetmov);
    //fechar laco for das pecas

    printf("peca atual main:\n");
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            printf("%c", pecaatual[j][i]);
        }
        printf("\n");
    }

    liberaAtual(pecaatual);
    liberaTela(tela);
    fclose(arq);
}