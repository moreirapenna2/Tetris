#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


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




void leArquivo(FILE *arq, int *colunas, int *tempo, int *quantpecas){

    fscanf(arq, "%d", colunas);
    fscanf(arq, "%d", tempo);
    fscanf(arq, "%d", quantpecas);

    printf("colunas arq: %d\n", *colunas);
    printf("intervalo de tempo arq: %d\n", *tempo);
    printf("quantidade de pecas arq: %d\n", *quantpecas);

}




void lePecas(FILE *arq, int *colunapecaatual, char ** pecaatual, int *movimentospecaatual, int *tamanhopeca, int *tamanhopeca2){
    int i,j, tam=0, tam2=0;
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
            if(pecaatual[j][i] != 46){
                    tam=i;
                    if(tam2 < j)
                        tam2=j;
                    printf("entrou aqui com i=%d e j=%d\n", i, j);
            }
            printf("char [%d][%d] da peca pec: %d\n",i,j,pecaatual[j][i]);
        }
    }
    *tamanhopeca = tam; printf("OLHA AQUI: tam=%d, tamannhopeca=%d\n", tam, *tamanhopeca);
    *tamanhopeca2 = tam2; printf("OLHA AQUI: tam2=%d, tamanhopeca2=%d\n", tam2, *tamanhopeca2);

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
    int i=0,j=0,k=0;


    for(i=0; i<3; i++){
        k=0;
        for(j=colunapecaatual; j<colunapecaatual+3; j++){
            if(pecaint[i][k] != 46){
                tela[i][j] = pecaint[i][k];
            }
            k++;
        }
    }

}



void limpalinha(char **tela, int linhas, int colunas){
    int i,j,c,k,z;  //c = contador da linha
    int enter=0;
    char tela2[linhas][colunas];

    //zera a segunda tela
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            tela2[i][j] = 46;
        }
    }

    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            if(tela[i][j] != 46){
                c++;    //C++ HEHEHEHE, QUE IRONIA
            }else{
                break;
            }
            if(c == linhas-1){
                enter=1;
                for(k=0; k<i; k++){
                    for(z=0; z<colunas; z++){
                        tela2[k+1][z] = tela[k][z];
                    }
                }
            }
        }
        c=0;
    }

    if(enter==1){
        //passa a tela 2 pra tela 1
        for(i=0; i<linhas; i++){
            for(j=0; j<colunas; j++){
                tela[i][j] = tela2[i][j];
            }
        }
        limpalinha(tela, linhas, colunas);
    }

}



void jogarPeca(char **tela, char vetmov, char **pecaatual, int *linhapecaatual, int *colunapecaatual, int movimentotual, int linhas, int colunas, int tamanhopeca, int tamanhopeca2){
    int i,j;
    int linhaat = *linhapecaatual;  //declarar nao ponteiros para comparacao, senao buga
    int colunaat = *colunapecaatual; //declarar nao ponteiros para comparacao, senao buga
    char mov = vetmov; //declarar nao ponteiros para comparacao, senao buga
    char tela2[linhas][colunas];

    //zera a segunda tela
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            tela2[i][j] = tela[i][j];
        }
    }

    //printf("vetmov jogarpeca: %c\n", * vetmov);
    printf("mov jogarpeca: %c\n", mov);
    printf("era pra entrar aqui embaixo\n");
    //se o comando for pra baixo (b)
    if(mov == 98){
        //passa os valores da primeira tela pra segunda
        for(i=linhaat; i<=linhaat+tamanhopeca && i<linhas; i++){
            for(j=colunaat; j<=colunaat+tamanhopeca2 && j<colunas; j++){
                    tela2[i+1][j] = tela[i][j];
            }
        }
        //limpa a linha de antes
        for(i=linhaat-tamanhopeca; i<=linhaat; i++){
            for(j=colunaat; j<colunaat+tamanhopeca2+1; j++){
                if(tela2[i][j] != 46)
                    tela2[i][j] = 46;
            }
        }
        *linhapecaatual = *linhapecaatual+1;
    }


    //se o comando for pra esquerda(e)
    if(mov == 101){
        //passa os valores da primeira tela pra segunda
        for(i=linhaat; i<=linhaat+2 && i<linhas; i++){
            for(j=colunaat; j<=colunaat+3 && j<colunas && j>=0; j++){
                    tela2[i][j-1] = tela[i][j];
            }
        }
        //limpa a coluna de antes(depois no caso)
        for(i=linhaat; i<=linhaat+3; i++){
            for(j=colunaat+3; j<colunaat; j++){
                tela2[i][j] = 46;
            }
        }
        *colunapecaatual = *colunapecaatual-1;
    }


    //se o comando for pra direita(d)
    if(mov == 100){
        //passa os valores da primeira tela pra segunda
        for(i=linhaat; i<=linhaat+2 && i<linhas; i++){
            for(j=colunaat; j<=colunaat+3 && j<colunas; j++){
                    tela2[i][j+1] = tela[i][j];
            }
        }
        //limpa a coluna de antes(agora eh antes mesmo)
        for(i=linhaat; i<=linhaat+3; i++){
            for(j=colunaat; j<=colunaat; j++){
                tela2[i][j] = 46;
            }
        }
        *colunapecaatual = *colunapecaatual+1;
    }



    //passa a tela 2 pra tela 1
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            tela[i][j] = tela2[i][j];
        }
    }

    //verificar se alguma linhas esta cheia
    limpalinha(tela, linhas, colunas);
}




void printarTela(char **tela, int linhas, int colunas){
    //system("clear");
    int i,j;
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            printf("%c", tela[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}




void descerUm(char **tela, int linhas, int colunas, int linhapecaatual,int colunapecaatual, int tamanhopeca, int tamanhopeca2, int *check){
    int i,j,check2=0;
    /*char tela2[linhas][colunas];
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
    }*/
    char tela2[linhas][colunas];
    //zera a segunda tela
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            tela2[i][j] = tela[i][j];
        }
    }

    //checa se vai colidir
    i=linhapecaatual+tamanhopeca+1;
    printf("tamanho da peca2: %d\n, i: %d\n, coluna da peca: %d\n", tamanhopeca2, i, colunapecaatual);
    for(j=colunapecaatual; j<=colunapecaatual+tamanhopeca2 && j<colunas; j++){
        if(tela2[i][j]!=46)
            check2=1;
    }

    if(check2==0){
        //passa os valores da primeira tela pra segunda
        for(i=linhapecaatual; i<=linhapecaatual+tamanhopeca && i<linhas; i++){
            for(j=colunapecaatual; j<=colunapecaatual+tamanhopeca2 && j<colunas; j++){
                tela2[i+1][j] = tela[i][j];
            }
        }
        //limpa a linha de antes
        for(i=linhapecaatual-tamanhopeca; i<=linhapecaatual; i++){
            for(j=colunapecaatual; j<colunapecaatual+tamanhopeca2+1; j++){
                if(tela2[i][j] != 46)
                    tela2[i][j] = 46;
            }
        }

        //passa a tela 2 pra tela 1
        for(i=0; i<linhas; i++){
            for(j=0; j<colunas; j++){
                tela[i][j] = tela2[i][j];
            }
        }
    }

    *check=check2;
    printf("check2 = %d, *check = %d\n", check2, *check);
}



salvarTela(FILE *cya, char **tela, int linhas, int colunas){
        int i,j;

        for(i=0; i<linhas; i++){
            for(j=0; j<colunas; j++){
                fprintf(cya, "%c", tela[i][j]);
            }
            fprintf(cya, "\n");
        }

        fprintf(cya, "\n");
}




int main(){
    FILE *arq = fopen("entrada.txt", "r");
    FILE *cya = fopen("saida.txt", "w");
    int linhas, colunas, tempo, quantpecas, colunapecaatual, movimentospecaatual, tamanhopeca, linhapecaatual, tamanhopeca2;
    //tamanhopeca = linhas da peca
    //tamanhopeca2 = colunas da peca
    int i,j,k,check=0;
    //char pecaatual[3][3];
    char ** pecaatual, ** tela;
    char * vetmov;
    //enquanto a leitura nao der End Of File, continua lendo
    printf("parou aqui\n");
    while(fscanf(arq, "%d ", &linhas) != EOF){
        printf("entrou aqui\n");
        leArquivo(arq, &colunas, &tempo, &quantpecas);

        printf("linhas main: %d\ncolunas main: %d\n", linhas, colunas);

        tela = alocaTela(linhas, colunas);
        pecaatual = AlocaAtual();

        setartela(tela, linhas, colunas);
        printarTela(tela, linhas, colunas);
        //fazer laco for para quantidade de pecas
        for(k=0; k<quantpecas; k++){

            lePecas(arq, &colunapecaatual, pecaatual, &movimentospecaatual, &tamanhopeca, &tamanhopeca2);
            printf("tamanho da peca main: %d\n", tamanhopeca);
            printf("col: %d\nmovs: %d, taml:%d, tamc:%d", colunapecaatual, movimentospecaatual, tamanhopeca, tamanhopeca2);
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
            linhapecaatual=0;

            //vetmov eh o vetor que aloca os movimentos da peca atual
            vetmov = alocaMov(movimentospecaatual);
            leMovimentos(arq, movimentospecaatual, vetmov);
            setarpeca(tela, pecaint, colunapecaatual);
            printarTela(tela, linhas, colunas);
            printf("\n\n");
            //fazer laco para jogar a quantidade de movimentos
            for(i=0; i<movimentospecaatual; i++){
                check=0;
                printf("ta passando o i[%d], vetmov[%c]\n", i, vetmov[i]);
                jogarPeca(tela, vetmov[i], pecaatual, &linhapecaatual, &colunapecaatual, i, linhas, colunas, tamanhopeca, tamanhopeca2);
                sleep(tempo);
                printarTela(tela,linhas,colunas);
                if(i<linhas-tamanhopeca-1 && check==0){
                    descerUm(tela,linhas,colunas, linhapecaatual, colunapecaatual, tamanhopeca, tamanhopeca2, &check);
                    if(check==0){
                        linhapecaatual++;
                    }
                    sleep(tempo);
                    printarTela(tela,linhas,colunas);
                }
            }
            //se acabarem os movimentos e a peca ainda estivern o alto, ela cai
            for(i=linhapecaatual;i<linhas-tamanhopeca-1 && check==0;i++){
                descerUm(tela,linhas,colunas, linhapecaatual, colunapecaatual, tamanhopeca, tamanhopeca2, &check);
                if(check==0){
                    linhapecaatual++;
                }
                sleep(tempo);
                limpalinha(tela, linhas, colunas);
                printarTela(tela,linhas,colunas);
                //fechar laco for dos movimentos
            }
            printf(""); //SEM ISSO AQUI BUGA NAO SEI PQ MAS NAO TIRA
            liberaMov(vetmov);
            //fechar laco for das pecas
        }
        salvarTela(cya, tela, linhas, colunas);
        liberaAtual(pecaatual);
        liberaTela(tela);
        //fechar o laco for de jogos
    }

    fclose(arq);
}
