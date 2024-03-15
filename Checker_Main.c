#include "Checker_Lib.h"

int main(){
  checkers tabuleiro[8][8];
  table_filler(tabuleiro);
  int rodada = 1;

    while(table_counter_preta(tabuleiro) != 0 || table_counter_branca(tabuleiro) != 0){
        /*Visualização do tabuleiro
        Inicialização das variáveis ponteiros para a passagem de argumentos*/
        table_inversor(tabuleiro);
        table_printer(tabuleiro);
        int linhaEscolha, colunaEscolha;
        do {
    checker_choice(tabuleiro, &linhaEscolha, &colunaEscolha, rodada);
} while ((mov_sup_esq(tabuleiro, linhaEscolha, colunaEscolha) == 0 && mov_sup_dir(tabuleiro, linhaEscolha, colunaEscolha) == 0) && 
verif_sup_dir(tabuleiro, linhaEscolha, colunaEscolha) == 0 && verif_sup_esq(tabuleiro, linhaEscolha, colunaEscolha) == 0);

        
        //adicionar exceção para casos em que o jogador escolher uma casa vazia.

        /*VARIÁVEIS DE PONTO DE PARTIDA (ORIGEM)*/
        int linhaOrigem = linhaEscolha, colunaOrigem = colunaEscolha;
        int linhaDestino, colunaDestino;

        if(tabuleiro[linhaOrigem][colunaOrigem] == dama_branca || tabuleiro[linhaOrigem][colunaOrigem] == dama_preta){
            /*Coordenadas de direção para armazenar retornos de cada função de verificação.
            Vetores de armazenamento de jogadas válidas e de direcionamento.
            Contagem de jogadas válidas possíveis para retorno de condição de captura ou condição de movimento.*/

            int sup_esq, sup_dir, inf_esq, inf_dir;
            int v_sup_esq, v_sup_dir, v_inf_esq, v_inf_dir;
            coordenada Jogadas[4];
            int jogadas_validas = 4;

            /*--------------------- INICIO DA VARREDURA DAS DIAGONAIS EM 4 DIREÇÕES ---------------------*/

            sup_esq = var_sup_esq(tabuleiro, linhaOrigem, colunaOrigem);
            if(sup_esq != 0){
                v_sup_esq = verif_sup_esq(tabuleiro, linhaOrigem-sup_esq, colunaOrigem-sup_esq); 
                if(v_sup_esq != 0){
                    Jogadas[0].valida = 1; Jogadas[0].linha = (linhaOrigem-sup_esq)-2; Jogadas[0].coluna = (colunaOrigem-sup_esq)-2;
                    printf("\nCaptura obrigatória na posição: %d %d", (linhaOrigem-sup_esq)-2, (colunaOrigem-sup_esq)-2);}
                    else{jogadas_validas--;}
            } else{jogadas_validas--;}

            sup_dir = var_sup_dir(tabuleiro, linhaOrigem, colunaOrigem);
            if(sup_dir != 0){
                v_sup_dir = verif_sup_dir(tabuleiro, linhaOrigem-sup_esq, colunaOrigem+sup_esq); 
                if(v_sup_dir != 0){
                    Jogadas[1].valida = 2; Jogadas[1].linha = (linhaOrigem-sup_dir)-2; Jogadas[1].coluna = (colunaOrigem+sup_dir)+2;
                    printf("\nCaptura obrigatória na posição: %d %d", (linhaOrigem-sup_dir)-2, (colunaOrigem+sup_dir)+2);}
                    else{jogadas_validas--;}
            } else{jogadas_validas--;}
            
            inf_esq = var_inf_esq(tabuleiro, linhaOrigem, colunaOrigem);
            if(inf_esq != 0){
                v_inf_esq = verif_inf_esq(tabuleiro, linhaOrigem+inf_esq, colunaOrigem-inf_esq); 
                if(v_inf_esq != 0){
                    Jogadas[2].valida = 3; Jogadas[2].linha = (linhaOrigem+inf_esq)+2; Jogadas[2].coluna = (colunaOrigem-inf_esq)-2;
                    printf("\nCaptura obrigatória na posição: %d %d", (linhaOrigem+inf_esq)+2, (colunaOrigem-inf_esq)-2);}
                    else{jogadas_validas--;}
                } 
            else{jogadas_validas--;}

            inf_dir = var_inf_dir(tabuleiro, linhaOrigem, colunaOrigem);
            if(inf_dir != 0){
                v_inf_dir = verif_inf_dir(tabuleiro, linhaOrigem+inf_dir, colunaOrigem+inf_dir); 
                if(v_inf_dir != 0){
                    Jogadas[3].valida = 4; Jogadas[3].linha = (linhaOrigem+sup_dir)+2; Jogadas[3].coluna = (colunaOrigem+sup_dir)+2;
                    printf("\nCaptura obrigatória na posição: %d %d", (linhaOrigem+inf_dir)+2, (colunaOrigem+inf_dir)+2);}
                    else{jogadas_validas--;}
            } else{jogadas_validas--;}
            

            /*--------------------- FIM DA VARREDURA DAS DIAGONAIS QUADRIRECIONAIS ---------------------*/

            //Variável para salvar a direção que eu estou me dirigindo para que a função de captura possa trabalhar na maneira certa.
            if(jogadas_validas != 0){
                int jogada_feita = 0;

                while(jogada_feita == 0){
                    printf("\nEscolha um dos movimentos obrigatórios e selecione a posição.\n");
                    scanf("%d %d",&linhaDestino, &colunaDestino);

                    for(int i = 0; i<4; i++){
                        if(Jogadas[i].valida == 1 || Jogadas[i].valida == 2 || Jogadas[i].valida == 3 || Jogadas[i].valida == 4){
                            if(linhaDestino == Jogadas[i].linha && colunaDestino == Jogadas[i].coluna){
                                jogada_feita = 1;
                                break;
                            }
                        }
                    }
                }

                int captura_max; 
                movimento_pedra(tabuleiro, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);
                do{
                    captura_max = lei_da_maioria(tabuleiro, linhaDestino, colunaDestino, rodada);
                    } while(captura_max == 1);
            }
            else {
                coordenada Movimento[4];

                /*--------------------VARREDURA DE POSIÇÕES-----------------------*/

                sup_esq = var_sup_esq(tabuleiro, linhaOrigem, colunaOrigem)-1;
                if(sup_esq != 0){Movimento[0].valida = 1; Movimento[0].linha = linhaOrigem-sup_esq; Movimento[0].coluna = colunaOrigem-sup_esq;
                printf("\nMovimento na posição: %d %d", linhaOrigem-sup_esq, colunaOrigem-sup_esq);}

                sup_dir = var_sup_dir(tabuleiro, linhaOrigem, colunaOrigem)-1;
                if(sup_dir != 0){Movimento[1].valida = 2; Movimento[1].linha = linhaOrigem-sup_dir; Movimento[1].coluna = colunaOrigem+sup_dir;
                printf("\nMovimento na posição: %d %d", linhaOrigem-sup_dir, colunaOrigem+sup_dir);}

                inf_esq = var_inf_esq(tabuleiro, linhaOrigem, colunaOrigem)-1;
                if(inf_esq != 0){Movimento[2].valida = 3; Movimento[2].linha = linhaOrigem+inf_esq; Movimento[2].coluna = colunaOrigem-inf_esq;
                    printf("\nMovimento na posição: %d %d", linhaOrigem+inf_esq, colunaOrigem-inf_esq);}

                inf_dir = var_inf_dir(tabuleiro, linhaOrigem, colunaOrigem)-1;
                if(inf_dir != 0){Jogadas[3].valida = 4; Jogadas[3].linha = linhaOrigem+inf_dir; Jogadas[3].coluna = colunaOrigem+inf_dir;
                printf("\nMovimento na posição: %d %d", linhaOrigem+inf_dir, colunaOrigem+inf_dir);}

                /*---------------------- FIM DE VARREDURA ------------------------*/

                int jogada_feita = 0;

                while(jogada_feita == 0){
                    printf("\nEscolha um dos movimentos e selecione a posição.\n");
                    scanf("%d %d",&linhaDestino, &colunaDestino);

                    for(int i = 0; i<4; i++){
                        if( Movimento[i].valida == 1 || Movimento[i].valida == 2 || Movimento[i].valida == 3 || Movimento[i].valida == 4){
                            if(linhaDestino == Movimento[i].linha && colunaDestino == Movimento[i].coluna){
                                jogada_feita = 1;
                                break;
                            }
                        }
                    }
                }
                movimento_pedra(tabuleiro, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);
            }
        }

        else if(tabuleiro[linhaOrigem][colunaOrigem] == branca || tabuleiro[linhaOrigem][colunaOrigem] == preta){
            //Ccoordenadas de direção para armazenar retornos de cada função de verificação.
                int sup_esq, sup_dir, inf_esq, inf_dir;
                coordenada Jogadas[4];
                int jogadas_validas = 4;

                sup_esq = verif_sup_esq(tabuleiro, linhaOrigem, colunaOrigem);
                if(sup_esq != 0){Jogadas[0].valida = 1; Jogadas[0].linha = linhaOrigem-2; Jogadas[0].coluna = colunaOrigem-2;
                printf("\nCaptura obrigatória na posição: %d %d", linhaOrigem-2, colunaOrigem-2);}
                else{jogadas_validas--;} 

                sup_dir = verif_sup_dir(tabuleiro, linhaOrigem, colunaOrigem);
                if(sup_dir != 0){Jogadas[1].valida = 2; Jogadas[1].linha = linhaOrigem-2; Jogadas[1].coluna = colunaOrigem+2;
                printf("\nCaptura obrigatória na posição: %d %d", linhaOrigem-2, colunaOrigem+2);}
                else{jogadas_validas--;} 

                inf_esq = verif_inf_esq(tabuleiro, linhaOrigem, colunaOrigem);
                if(inf_esq != 0){Jogadas[2].valida = 3; Jogadas[2].linha = linhaOrigem+2; Jogadas[2].coluna = colunaOrigem-2;
                printf("\nCaptura obrigatória na posição: %d %d", linhaOrigem+2, colunaOrigem-2);}
                else{jogadas_validas--;} 

                inf_dir = verif_inf_dir(tabuleiro, linhaOrigem, colunaOrigem);
                if(inf_dir != 0){Jogadas[3].valida = 4; Jogadas[3].linha = linhaOrigem+2; Jogadas[3].coluna = colunaOrigem+2;
                printf("\nCaptura obrigatória na posição: %d %d", linhaOrigem+2, colunaOrigem+2);}
                else{jogadas_validas--;}


            //condição de permissão à captura de peças/damas com movimentos...
                if(jogadas_validas != 0){
                    int jogada_feita = 0;

                    while(jogada_feita == 0){
                        printf("\nEscolha um dos movimentos obrigatórios e selecione a posição.\n");
                        scanf("%d %d",&linhaDestino, &colunaDestino);

                        for(int i = 0; i<4; i++){
                            if(Jogadas[i].valida == 1 || Jogadas[i].valida == 2 || Jogadas[i].valida == 3 || Jogadas[i].valida == 4){
                                if(linhaDestino == Jogadas[i].linha && colunaDestino == Jogadas[i].coluna){
                                    jogada_feita = 1;
                                    break;
                                }
                            }
                        }
                    }

                    int captura_max;
                    movimento_pedra(tabuleiro, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);
                    do{
                    captura_max = lei_da_maioria(tabuleiro, linhaDestino, colunaDestino, rodada);
                    } while(captura_max == 1);
                    king_mode(tabuleiro, linhaDestino, colunaDestino, rodada);
                }

                else{
                    coordenada Movimento[2];

                    sup_esq = mov_sup_esq(tabuleiro, linhaOrigem, colunaOrigem);
                    if(sup_esq == 1){Movimento[0].valida = 1; Movimento[0].linha = linhaOrigem-1; Movimento[0].coluna = colunaOrigem-1;
                    printf("\nMovimento na posição: %d %d", linhaOrigem-1, colunaOrigem-1);}

                    sup_dir = mov_sup_dir(tabuleiro, linhaOrigem, colunaOrigem);
                    if(sup_dir == 2){Movimento[1].valida = 2; Movimento[1].linha = linhaOrigem-1; Movimento[1].coluna = colunaOrigem+1;
                    printf("\nMovimento na posição: %d %d", linhaOrigem-1, colunaOrigem+1);}

/*                     inf_esq = mov_inf_esq(tabuleiro, linhaOrigem, colunaOrigem);
                    if(inf_esq == 3){Movimento[2].valida = 3; Movimento[2].linha = linhaOrigem+1; Movimento[2].coluna = colunaOrigem-1;
                    printf("\nMovimento na posição: %d %d", linhaOrigem+1, colunaOrigem-1);}

                    inf_dir = mov_inf_dir(tabuleiro, linhaOrigem, colunaOrigem);
                    if(inf_dir == 4){Jogadas[3].valida = 4; Jogadas[3].linha = linhaOrigem+1; Jogadas[3].coluna = colunaOrigem+1;
                    printf("\nMovimento na posição: %d %d", linhaOrigem+1, colunaOrigem+1);} */

                    int jogada_feita = 0;

                    while(jogada_feita == 0){
                        printf("\nEscolha um dos movimentos e selecione a posição.\n");
                        scanf("%d %d",&linhaDestino, &colunaDestino);
                        // || Movimento[i].valida == 3 || Movimento[i].valida == 4
                        for(int i = 0; i<2; i++){
                            if( Movimento[i].valida == 1 || Movimento[i].valida == 2){
                                if(linhaDestino == Movimento[i].linha && colunaDestino == Movimento[i].coluna){
                                    jogada_feita = 1;
                                    break;
                                }
                            }
                        }
                    }
                    movimento_pedra(tabuleiro, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);
                    king_mode(tabuleiro, linhaDestino, colunaDestino, rodada);
                }
        }
      rodada++;
    }
return 0;
}
