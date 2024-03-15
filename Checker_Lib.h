#include <stdio.h>
#include <stdlib.h>


typedef enum {vazio, branca, preta, dama_branca, dama_preta} checkers;

typedef struct {
  int valida, linha, coluna;
} coordenada;


/*------------------------------------------------------------------------------
<-------------------implementação e manipulação de tabuleiro------------------->
-------------------------------------------------------------------------------*/

void table_inversor(checkers tabuleiro[8][8]) {
    checkers temp;
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            temp = tabuleiro[i][j];
            tabuleiro[i][j] = tabuleiro[7 - i][7 - j];
            tabuleiro[7 - i][7 - j] = temp;
        }
    }
}

void table_filler(checkers table[8][8]){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if ( (i+j)%2 == 0 || i == 3 || i == 4){
        table[i][j] = vazio;}
      else{
        if(i <= 2){
          table[i][j] = branca;
        }
        else{
          table[i][j] = preta;
        }
      }
    }
  }
}

int table_counter_preta(checkers table[8][8]){
  int n_pretas = 0;
  for(int i = 0; i<8; i++){
    for(int j = 0; j<8; j++){
      if(table[i][j] == preta || table[i][j] == preta){
        n_pretas++;
      }
    }
  }
  return n_pretas;
}

int table_counter_branca(checkers table[8][8]){
  int n_brancas = 0;
  for(int i = 0; i<8; i++){
    for(int j = 0; j<8; j++){
      if(table[i][j] == branca || table[i][j] == dama_branca){
        n_brancas++;
      }
    }
  }
  return n_brancas;
}

void table_printer(checkers table[8][8]){
  printf("\n=======================================\n\n");
    printf("   0  1  2  3  4  5  6  7\n");
  for(int i = 0; i < 8; i++){
    printf("%d ", i);
    for(int j = 0; j<8 ; j++){
      if(table[i][j] == vazio){printf(" . ");}
      else{
        if(table[i][j] == branca){printf(" O ");}
        else if(table[i][j] == preta){printf(" X ");}
        else if(table[i][j] == dama_branca){printf(" W ");}
        else if(table[i][j] == dama_preta){printf(" B ");}
      }
    }
    printf("\n");
  }
  printf("\nPEÇAS:\nBrancas: %d\nPretas %d\n\n",table_counter_branca(table), table_counter_preta(table));
}

void table_printer_II(checkers table[8][8]){
  printf(" 0   1   2   3   4   5   6   7 \n\n");
  for (int l = 0; l < 7; l++){
    for (int c = 0; c < 7; c++){
      printf(" %c ", table[l][c]);
      if (c < 7){
        printf(" | ");
      }
      if (c==6){
        printf("   %d",l);
      }
    }
    if (l < 7){
      printf(" \n - - - - - - - - - - - - - - -   ");
    }
    printf("\n");
  }
  printf("\nPEÇAS:\nBrancas: %d\nPretas %d\n\n",table_counter_branca(table), table_counter_preta(table));
}
/*---------------------------------------------------------------------------------------
<-------------------implementação inicial das funções de movimentação------------------->
---------------------------------------------------------------------------------------*/

/*<---------verificação de movimento e captura--------->*/

int verif_sup_esq(checkers table[8][8], int linhaOrigem, int colunaOrigem){
    if((table[linhaOrigem-1][colunaOrigem-1] != vazio && table[linhaOrigem-1][colunaOrigem-1] != table[linhaOrigem][colunaOrigem]) && table[linhaOrigem-2][colunaOrigem-2] == vazio){
      if((linhaOrigem-1 >= 0 && colunaOrigem-1 >= 0) && (linhaOrigem-2 >= 0 && colunaOrigem-2 >= 0)){return 1;}
        else{return 0;}
    } else {return 0;}
}
/*caso o retorno dela seja verdadeiro, ela retorna a posição a ser jogada*/
int verif_sup_dir(checkers table[8][8], int linhaOrigem, int colunaOrigem){
    if((table[linhaOrigem-1][colunaOrigem+1] != vazio && table[linhaOrigem-1][colunaOrigem+1] != table[linhaOrigem][colunaOrigem]) && table[linhaOrigem-2][colunaOrigem+2] == vazio){
      if((linhaOrigem-1 >= 0 && colunaOrigem+1 <= 7) && (linhaOrigem-2 >= 0 && colunaOrigem+2 <= 7)){return 1;}
        else{return 0;}
    } else {return 0;}
}
int verif_inf_esq(checkers table[8][8], int linhaOrigem, int colunaOrigem){
    if((table[linhaOrigem+1][colunaOrigem-1] != vazio && table[linhaOrigem+1][colunaOrigem-1] != table[linhaOrigem][colunaOrigem]) && table[linhaOrigem+2][colunaOrigem-2] == vazio){
      if((linhaOrigem+1 <= 7 && colunaOrigem-1 >= 0) && (linhaOrigem+2 <= 7 && colunaOrigem-2 >= 0)){return 1;}
        else{return 0;}
    } else {return 0;}
}
int verif_inf_dir(checkers table[8][8], int linhaOrigem, int colunaOrigem){
    if((table[linhaOrigem+1][colunaOrigem+1] != vazio && table[linhaOrigem+1][colunaOrigem+1] != table[linhaOrigem][colunaOrigem]) && table[linhaOrigem+2][colunaOrigem+2] == vazio){
      if((linhaOrigem+1 <= 7 && colunaOrigem+1 <= 7) && (linhaOrigem+2 <= 7 && colunaOrigem+2 <= 7)){return 1;}
        else{return 0;}
    } else {return 0;}
}


/*-------------------------------------------------------------------*/

int mov_sup_esq(checkers table[8][8], int linhaOrigem, int colunaOrigem){
    if(table[linhaOrigem-1][colunaOrigem-1] == vazio && (linhaOrigem-1 >= 0 && colunaOrigem-1 >= 0)){
        //realmente era o contrario. o que era pra ser verdadeiro é falso.
        return 1;
    } else {
        return 0;}
}
/*caso o retorno dela seja verdadeiro, ela retorna a posição a ser jogada*/
int mov_sup_dir(checkers table[8][8], int linhaOrigem, int colunaOrigem){
    if(table[linhaOrigem-1][colunaOrigem+1] == vazio && (linhaOrigem-1 >= 0 && colunaOrigem+1 < 8)){
        return 2;
    } else {return 0;}
}
int mov_inf_esq(checkers table[8][8], int linhaOrigem, int colunaOrigem){
    if(table[linhaOrigem+1][colunaOrigem-1] == vazio && (linhaOrigem+1 < 8 && colunaOrigem-1 >= 0)){
        return 3;
    } else {return 0;}
}
int mov_inf_dir(checkers table[8][8], int linhaOrigem, int colunaOrigem){
    if(table[linhaOrigem+1][colunaOrigem+1] == vazio && (linhaOrigem+1 < 8 && colunaOrigem+1 < 8)){
        return 4;
    } else {return 0;}
}

/*<---------verificação de peças comuns--------->*/



/*<---------movimentação de peças e damas--------->*/
void movimento_pedra(checkers table[8][8], int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino){
  checkers aux;
  aux = table[linhaOrigem][colunaOrigem];
  table[linhaOrigem][colunaOrigem] = table[linhaDestino][colunaDestino];
  table[linhaDestino][colunaDestino] = aux;
}


/*---------------------------------------------------------------------------
<-------------------implementação de jogadas obrigatórias------------------->
----------------------------------------------------------------------------*/

/*<---------captura de peças comuns--------->*/
void captura_comum(checkers table[8][8], int linhaComida, int colunaComida, int posicao_captura){
  if(posicao_captura == 1){
    table[linhaComida+1][colunaComida+1] = vazio;
    printf("\nCaptura realizada em %d %d.\n",linhaComida+1, colunaComida+1);
  }
  else if(posicao_captura == 2){
    table[linhaComida+1][colunaComida-1] = vazio;
    printf("\nCaptura realizada em %d %d.\n",linhaComida+1, colunaComida-1);
  }
  else if(posicao_captura == 3){
    table[linhaComida-1][colunaComida+1] = vazio;
    printf("\nCaptura realizada em %d %d.\n",linhaComida-1, colunaComida+1);
  }
  else if(posicao_captura == 4){
    table[linhaComida-1][colunaComida-1] = vazio;
    printf("\nCaptura realizada em %d %d.\n",linhaComida-1, colunaComida-1);
  }
}

/*--------------------------------------------------------------------------------
-------------------implementação de interação humano-computador-------------------
--------------------------------------------------------------------------------*/

void checker_choice(checkers table[8][8], int *linhaOrigem, int *colunaOrigem, int rodada) {
  if(rodada % 2 == 0){printf("========== Rodada das pretas ==========\n\n");} 
  else{printf("========== Rodada das brancas ==========\n\n");}
    printf("Escolha uma peça, inserindo sua posição.\n(Exemplo: 1 2).\n");

    do {
        scanf("%d %d", linhaOrigem, colunaOrigem);
    } while (((*linhaOrigem < 0 || *linhaOrigem > 7) || ((*colunaOrigem < 0 || *colunaOrigem > 7))) || table[*linhaOrigem][*colunaOrigem] == vazio || (rodada % 2 == 0 && (table[*linhaOrigem][*colunaOrigem] != preta && table[*linhaOrigem][*colunaOrigem] != dama_preta) ) || (rodada % 2 != 0 && (table[*linhaOrigem][*colunaOrigem] != branca && table[*linhaOrigem][*colunaOrigem] != dama_branca)));

    return;
}

void king_mode(checkers tabuleiro[8][8], int linha, int coluna, int rodada) {
    
    if ((linha == 0 && tabuleiro[linha][coluna] == preta && rodada % 2 == 0) ||
        (linha == 7 && tabuleiro[linha][coluna] == branca && rodada % 2 != 0)) {

        if(tabuleiro[linha][coluna] == preta){tabuleiro[linha][coluna] = dama_preta;}
        else if(tabuleiro[linha][coluna] == branca){tabuleiro[linha][coluna] = dama_branca;}    
        
        printf("Agora o bicho pega e a cobra fuma!\n A peça em %d %d se tornou uma dama!\n", linha, coluna);
    }
    
}

int lei_da_maioria(checkers table[8][8], int linha, int coluna, int rodada) {
    int possibilidades = 0;
    int sup_esq, sup_dir, inf_esq, inf_dir;
    int direcao_jogada = 0;

    sup_esq = verif_sup_esq(table, linha, coluna);
    if (sup_esq != 0) {
        possibilidades++;
        direcao_jogada = 1;
    }

    sup_dir = verif_sup_dir(table, linha, coluna);
    if (sup_dir != 0) {
        possibilidades++;
        direcao_jogada = 2;
    }

    inf_esq = verif_inf_esq(table, linha, coluna);
    if (inf_esq != 0) {
        possibilidades++;
        direcao_jogada = 3;
    }

    inf_dir = verif_inf_dir(table, linha, coluna);
    if (inf_dir != 0) {
        possibilidades++;
        direcao_jogada = 4;
    }

    if (possibilidades == 0) {
        return 0;
    } else {
        int linhaDestino, colunaDestino;

        if (direcao_jogada == 1) {
            linhaDestino = linha - 2;
            colunaDestino = coluna - 2;
        } else if (direcao_jogada == 2) {
            linhaDestino = linha - 2;
            colunaDestino = coluna + 2;
        } else if (direcao_jogada == 3) {
            linhaDestino = linha + 2;
            colunaDestino = coluna - 2;
        } else if (direcao_jogada == 4) {
            linhaDestino = linha + 2;
            colunaDestino = coluna + 2;
        }

        movimento_pedra(table, linha, coluna, linhaDestino, colunaDestino);
        captura_comum(table, linhaDestino, colunaDestino, direcao_jogada);
        king_mode(table, linhaDestino, colunaDestino, rodada);
        return 1;
    }
}

int var_sup_esq(checkers table[8][8], int linha, int coluna){
    int loop = 0; 
    int linhaCaptura = linha, colunaCaptura = coluna;

    int booleana; 
    do{
        if(linhaCaptura > 0 && colunaCaptura > 0){
            booleana = (table[linhaCaptura-1][colunaCaptura-1] == vazio) ? 1 : 0;
            linhaCaptura--;
            colunaCaptura--;
            loop++;
        } else {break;}
    } while (booleana == 1); 

    return loop;
}

int var_sup_dir(checkers table[8][8], int linha, int coluna){
    int loop = 0; 
    int linhaCaptura = linha, colunaCaptura = coluna;

    int booleana; 
    do{
        if(linhaCaptura > 0 && colunaCaptura <= 7){
        booleana = (table[linhaCaptura-1][colunaCaptura+1] == vazio) ? 1 : 0;
        linhaCaptura--;
        colunaCaptura++;
        loop++;
        } else {break;}
    } while (booleana == 1); 

    return loop;
}

int var_inf_esq(checkers table[8][8], int linha, int coluna){
    int loop = 0; 
    int linhaCaptura = linha, colunaCaptura = coluna;

    int booleana; 
    do{
        if(linhaCaptura <= 7 && colunaCaptura > 0){
        booleana = (table[linhaCaptura+1][colunaCaptura-1] == vazio) ? 1 : 0;
        linhaCaptura++;
        colunaCaptura--;
        loop++;
        } else {break;}
    } while (booleana == 1); 

    return loop;
}

int var_inf_dir(checkers table[8][8], int linha, int coluna){
    int loop = 0; 
    int linhaCaptura = linha, colunaCaptura = coluna;

    int booleana; 
    do{
        if (linhaCaptura <= 7 && colunaCaptura <= 7){
        booleana = (table[linhaCaptura+1][colunaCaptura+1] == vazio) ? 1 : 0;
        linhaCaptura++;
        colunaCaptura++;
        loop++;
        } else {break;}
    } while (booleana == 1); 

    return loop;
}



