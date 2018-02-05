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
    return (tmp);
}





//aloca o vetor vetmov que contem os movimentos da peca atual
int * alocaMov(int quant){
    int * tmp;
    tmp = malloc(quant * sizeof(char));
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

    return(tmp);
}




//libera a peca atual
void liberaAtual(char ** pecaatual){
    free(pecaatual);
}




//libera os movimentos
void liberaMov(char *vetmov){
    free(vetmov);
}




//libera a tela
void liberaTela(char ** tela){
    free(tela);
}




//le as coisas principais da partida
void leArquivo(FILE *arq, int *colunas, int *tempo, int *quantpecas){

    fscanf(arq, "%d", colunas);
    fscanf(arq, "%d", tempo);
    fscanf(arq, "%d", quantpecas);

}




//le a peca que vai ser jogada
void lePecas(FILE *arq, int *colunapecaatual, char ** pecaatual, int *movimentospecaatual, int *tamanhopeca, int *tamanhopeca2, int linhadacoluna[]){
    int i,j, tam=0, tam2=0;
    char cache;
    // cria uma matriz de 2 dimensoes, sendo 1 para guardar as peças e outra para guardar os movimentos (acho que nao vou fazer)
    // acabei criando 1 vetor para guardar os movimentos, e resolvi chamar a funcao de ler pecas para cada peca do jogo
    fscanf(arq, "%d", colunapecaatual);
    for(i=0; i<3; i++){
        fscanf(arq, "%c", &cache);
        for(j=0; j<3; j++){
            fscanf(arq, "%c", &pecaatual[j][i]);
            if(pecaatual[j][i] != 46){
                    tam=i;
                    linhadacoluna[j] = i;
                    if(tam2 < j)
                        tam2=j;
            }
        }
    }
    *tamanhopeca = tam;
    *tamanhopeca2 = tam2;

    fscanf(arq, "%d", movimentospecaatual);

}




//le no arquivo os movimentos da peca
void leMovimentos(FILE *arq, int movimentospecaatual, char *vetmov){
    char cache;
    int i;

    for(i=0; i<movimentospecaatual; i++){
        fscanf(arq, "%c", &cache);
        fscanf(arq, "%c", &vetmov[i]);
    }

}





//coloca os pontos na tela
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




//coloca a peca na tela
void setarpeca(char **tela, int colunas, int pecaint[3][3], int colunapecaatual, int *gameover){
    int i=0,j=0,k;

    for(j=colunapecaatual; j<colunapecaatual+2; j++){
        if(tela[i][j] != 46){
            //se a coluna que a peca for descer estiver cheia, GAME OVER!
            *gameover = 1;
        }
    }

    //se nao for game over, coloca a peca na tela
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



//verifica se tem alguma linha cheia, e se tiver, limpa ela e desce a tela
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

    //roda as linhas e colunas, se alguma estiver cheia, joga pra baixo
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



//faz os movimentos do jogador (baixo, esquerda, direita)
void jogarPeca(char **tela, char vetmov, char **pecaatual, int *linhapecaatual, int *colunapecaatual, int movimentotual, int linhas, int colunas, int tamanhopeca, int tamanhopeca2, int *check, int linhadacoluna[]){
    int i,j,k, check2=0;
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

    //se o comando for pra baixo (b)
    if(mov == 98){

        //checa se vai colidir em baixo
        i=linhaat+tamanhopeca+1;
        for(j=colunaat; j<=colunaat+tamanhopeca2 && j<colunas; j++){
            if(tela2[i][j]!=46)
                check2=1;
        }

        //se nao colidir, desce a peca apenas ate a linha que cada coluna vai
        if(check2==0){
            k=0;
            for(j=colunaat; j<colunaat+tamanhopeca2+1; j++){
                for(i=linhaat; i<linhaat+linhadacoluna[k]+1; i++){
                    tela2[i+1][j] = tela[i][j];
                }
                k++;
            }

            //limpa a linha de antes
            i=linhaat;
            for(j=colunaat; j<colunaat+tamanhopeca2+1; j++){
                tela2[i][j] = 46;
            }

        *linhapecaatual = *linhapecaatual+1;
        }

    }


    //se o comando for pra esquerda(e)
    if(mov == 101){

        //checa se vai colidir na esquerda
        //se colidir o ID de colisao vai ser 2, indicando que nao eh pra baixo
        j=colunaat-1;
        //checa se colide com alguma peca
        for(i=linhaat; i<=linhaat+tamanhopeca && i<linhas; i++){
            if(tela2[i][j]!=46)
                check2=2;
        }
        //checa se colide com a tela
        if(j<0)
            check2=2;

        //se nao colidir com nada
        if(check2==0){

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

    }


    //se o comando for pra direita(d)
    if(mov == 100){

        //checa se vai colidir na direita
        //se colidir o ID de colisao vai ser 2, indicando que eh pro lado, nao pra baixo
        j=colunaat+tamanhopeca2+1;
        //checa se colide com alguma peca
        for(i=linhaat; i<=linhaat+tamanhopeca && i<linhas; i++){
            if(tela2[i][j]!=46)
                check2=2;
        }
        //checa se colide com a tela
        if(j>=linhas)
            check2=2;

        //se nao colidir
        if(check2==0){

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
    }

    //se nao colidiu, passa a tela2 pra tela
    if(check2==0){
        //passa a tela 2 pra tela 1
        for(i=0; i<linhas; i++){
            for(j=0; j<colunas; j++){
                tela[i][j] = tela2[i][j];
            }
        }
    }


    //verificar se alguma linhas esta cheia
    *check=check2;
    limpalinha(tela, linhas, colunas);
}




//printa a tela no terminal
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




//desce a peca 1 linha
void descerUm(char **tela, int linhas, int colunas, int linhapecaatual,int colunapecaatual, int tamanhopeca, int tamanhopeca2, int *check, int linhadacoluna[]){
    int i,j,k,check2=0;
    char tela2[linhas][colunas];

    //zera a segunda tela
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            tela2[i][j] = tela[i][j];
        }
    }

    //checa se vai colidir
    for(j=0; j<=tamanhopeca2; j++){
        if(tela2[linhadacoluna[j]+1+linhapecaatual][colunapecaatual+j] != 46)
            check2=1;
    }

    //se nao colidir
    if(check2==0){
        k=0;
        for(j=colunapecaatual; j<colunapecaatual+tamanhopeca2+1; j++){
            for(i=linhapecaatual; i<linhapecaatual+linhadacoluna[k]+1; i++){
                tela2[i+1][j] = tela[i][j];
            }
            k++;
        }

        //limpa a linha de antes
        i=linhapecaatual;
        for(j=colunapecaatual; j<colunapecaatual+tamanhopeca2+1; j++){
            tela2[i][j] = 46;
        }

        //passa a tela 2 pra tela 1
        for(i=0; i<linhas; i++){
            for(j=0; j<colunas; j++){
                tela[i][j] = tela2[i][j];
            }
        }
    }

    *check=check2;
}



//meio obvio
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
    int i,j,k,check=0, gameover=0;
    int linhadacoluna[3]; //linhacompeca[0] segura o valor de qual linha da coluna 0 tem peca
    //char pecaatual[3][3];
    char ** pecaatual, ** tela;
    char * vetmov;


    //enquanto a leitura nao der End Of File, continua lendo
    while(fscanf(arq, "%d ", &linhas) != EOF){
        leArquivo(arq, &colunas, &tempo, &quantpecas);

        //aloca a tela e a peca
        tela = alocaTela(linhas, colunas);
        pecaatual = AlocaAtual();

        //coloca os pontinhos na tela
        setartela(tela, linhas, colunas);
        printarTela(tela, linhas, colunas);

        gameover=0; //ainda nao deu game over, pode ir pro jogo
        //aqui eh o jogo, vai rodar pela quantidade de pecas que tem
        for(k=0; k<quantpecas && gameover==0; k++){

            lePecas(arq, &colunapecaatual, pecaatual, &movimentospecaatual, &tamanhopeca, &tamanhopeca2, &linhadacoluna);

            //mudar peca atual pra int em ascii
            //a peca em char da bug, em ascii nao
            int pecaint[3][3];
            for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                    pecaint[i][j] = (int) pecaatual[j][i];
                }
            }

            //a peca sempre comeca na linha 0
            linhapecaatual=0;

            //vetmov eh o vetor que aloca os movimentos da peca atual
            vetmov = alocaMov(movimentospecaatual);
            //le os movimentos da peca e passa pro vetmov
            leMovimentos(arq, movimentospecaatual, vetmov);
            setarpeca(tela, colunas, pecaint, colunapecaatual, &gameover);
            printarTela(tela, linhas, colunas);

            //esse laco eh pra mesma peca, roda de acordo com a quantidade de movimentos
            for(i=0; i<movimentospecaatual && gameover==0; i++){
                check=0;    //nao ta colidindo com nada

                jogarPeca(tela, vetmov[i], pecaatual, &linhapecaatual, &colunapecaatual, i, linhas, colunas, tamanhopeca, tamanhopeca2, &check, linhadacoluna);
                sleep(tempo);
                printarTela(tela,linhas,colunas);
                //se ainda nao estiver no fundo e nao tiver colidido com alguma em baixo, desce uma linha
                if(i<linhas-tamanhopeca-1 && check!=1){
                    descerUm(tela,linhas,colunas, linhapecaatual, colunapecaatual, tamanhopeca, tamanhopeca2, &check, linhadacoluna);
                    //se desceu direitinho, aumenta 1 linha
                    if(check!=1){
                        linhapecaatual++;
                    }
                    sleep(tempo);
                    printarTela(tela,linhas,colunas);
                }
            }


            //se acabarem os movimentos e a peca ainda estiver no alto, ela cai
            for(i=linhapecaatual;i<linhas-tamanhopeca-1 && check!=1 && gameover==0;i++){
                descerUm(tela,linhas,colunas, linhapecaatual, colunapecaatual, tamanhopeca, tamanhopeca2, &check, linhadacoluna);
                //se desceu direitinho, aumenta 1 linha
                if(check==0){
                    linhapecaatual++;
                }
                sleep(tempo);
                limpalinha(tela, linhas, colunas);
                printarTela(tela,linhas,colunas);
            }
            //acabaram os movimentos, libera da memoria
            liberaMov(vetmov);
        }
        //acabou o jogo, salvar a tela no arquivo de saida, liberar a peca e a tela
        salvarTela(cya, tela, linhas, colunas);
        liberaAtual(pecaatual);
        liberaTela(tela);
    }
    //FIM, fechando os arquivos
    printf("\nFIM\n");
    fclose(arq);
    fclose(cya);
}
