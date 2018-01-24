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




void lePecas(FILE *arq, int *colunapecaatual, char ** pecaatual, int *movimentospecaatual, int *tampeca){
    int i,j,tampeca2;
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
            if(pecaatual[i][j] == 42)
                tampeca2=i;
            printf("char [%d][%d] da peca pec: %c\n",i,j,pecaatual[j][i]);
        }
    }
    printf("tamanho da peca2: %d\n", tampeca2);
    *tampeca=tampeca2;
    printf("tamanho da peca: %d\n", *tampeca);

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





void setartela(char **tela, int linhas, int colunas){
    int i,j;
    //preencher tela
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            //46 = . em ascii
            tela[i][j] = 46;
        }
    }
}




void setarpeca(char **tela, int pecaint[3][3], int colunapecaatual){
    int i,j,k=0;

    for(i=0; i<3; i++){
        k=0;
        for(j=colunapecaatual; j<colunapecaatual+3; j++){
            if(pecaint[i][k] != 46){
                tela[i][j] = pecaint[i][k];
                k++;
            }
        }
    }

}




void jogarPeca(char **tela, char *vetmov, char **pecaatual){

}




void printarTela(char **tela, int linhas, int colunas){
    system("clear");
    int i,j;
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            printf("%c", tela[i][j]);
        }
        printf("\n");
    }
}




void descerUm(char **tela, int linhas, int colunas){
    int i,j;
    char tela2[linhas][colunas];
    //zera a segunda tela
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            tela2[i][j] = 46;
        }
    }
    //passa os valores da primeira tela pra segunda
    for(i=1; i<linhas; i++){
        for(j=0; j<colunas; j++){
            tela2[i][j] = tela[i-1][j];
        }
    }

    //passa a tela 2 pra tela 1
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            tela[i][j] = tela2[i][j];
        }
    }

}




int main(){
    FILE *arq = fopen("entrada.txt", "r");
    int linhas, colunas, tempo, quantpecas, colunapecaatual, movimentospecaatual, tamanhopeca;
    int i,j,k;
    //char pecaatual[3][3];
    char ** pecaatual, ** tela;
    char * vetmov;
    leArquivo(arq, &linhas, &colunas, &tempo, &quantpecas);
    tela = alocaTela(linhas, colunas);
    pecaatual = AlocaAtual();
    
    setartela(tela, linhas, colunas);
    printarTela(tela, linhas, colunas);
    //fazer laco for para quantidade de pecas
    lePecas(arq, &colunapecaatual, pecaatual, &movimentospecaatual, &tamanhopeca);
    printf("tamanho da peca main: %d\n", tamanhopeca);

    //mudar peca atual pra int em ascii
    int pecaint[3][3];
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            pecaint[i][j] = (int) pecaatual[j][i];
        }
    }
    //printar peca int
    printf("peca int main:\n");
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            printf("%c", pecaint[i][j]);
        }
        printf("\n");
    }


    //vetmov eh o vetor que aloca os movimentos da peca atual
    vetmov = alocaMov(movimentospecaatual);
    leMovimentos(arq, movimentospecaatual, vetmov);
    setarpeca(tela, pecaint, colunapecaatual);
    printarTela(tela, linhas, colunas);
    //fazer laco para jogar a quantidade de movimentos
    for(i=0; i<movimentospecaatual; i++){
        jogarPeca(tela, vetmov, pecaatual);
        descerUm(tela,linhas,colunas);
        sleep(tempo);
        printarTela(tela,linhas,colunas);
    }
    //se acabarem os movimentos e a peca ainda estivern o alto, ela cai
    for(;i<linhas-tamanhopeca;i++){
        descerUm(tela,linhas,colunas);
        sleep(tempo);
        printarTela(tela,linhas,colunas);
    }

    //fechar laco for dos movimentos
    printf(""); //SEM ISSO AQUI BUGA NAO SEI PQ MAS NAO TIRA
    liberaMov(vetmov);
    //fechar laco for das pecas


    liberaAtual(pecaatual);
    liberaTela(tela);
    fclose(arq);
}
