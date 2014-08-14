#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deque.h"

#define NUM_LINHA 25
#define NUM_COLUNA 75
#define SPACE 32
#define POSICAO_LINHA_PAREDE 16
#define POSICAO_COLUNA_PAREDE 3
void imprimirCobra(Deque* deque,WINDOW* parede)
{
  No* no=deque->cabeca;
  while(no){
    mvwprintw(parede,no->linha,no->coluna,"%c",no->dado);
    //wrefresh(parede);
    no=no->pro;
  }
}
void static inserirCorpo(Deque* deque,char dado, int linha,int coluna)
{
  No* no=criarNo(dado,linha,coluna);
  dequeInserir(deque,no);
}

void atualizarCobra(Deque* deque,int linha, int coluna)
{
   inserirCorpo(deque,'*',linha,coluna);
   dequeRemover(deque);
}


// Função para imprimir as paredes do jogo Snake
WINDOW* imprimirParedes()
{
  WINDOW* parede=newwin(NUM_LINHA, NUM_COLUNA, POSICAO_LINHA_PAREDE, POSICAO_COLUNA_PAREDE);
  init_pair(4,COLOR_WHITE,COLOR_GREEN); 
  wbkgd(parede,COLOR_PAIR(4));
  return parede;
}
void static _moverCobra(int* caracterAnterior,int* linha, int* coluna)
{
        if(*caracterAnterior==KEY_LEFT)
          (*coluna)--;

        if(*caracterAnterior==KEY_RIGHT)
          (*coluna)++; 

        if(*caracterAnterior==KEY_UP)
          (*linha)--;

        if(*caracterAnterior==KEY_DOWN)
          (*linha)++;
}
void moverCobra(Deque* deque,int* caracter, int* caracterAnterior,int* linha, int* coluna)
{

      if (*caracter!=ERR)
      {
        if((*caracter==KEY_LEFT && *caracterAnterior!=KEY_RIGHT) ||
          (*caracter==KEY_RIGHT && *caracterAnterior!=KEY_LEFT) ||
          (*caracter==KEY_UP && *caracterAnterior!=KEY_DOWN) ||
          (*caracter==KEY_DOWN && *caracterAnterior!=KEY_UP) )

          *caracterAnterior=*caracter;
        
        if(*caracter==SPACE){
          dequeReverter(deque);
          No* noAnterior=deque->cabeca->pro;
          if(deque->cabeca->coluna==noAnterior->coluna && deque->cabeca->linha > noAnterior->linha){
            *caracterAnterior=KEY_DOWN;
          }else if(deque->cabeca->linha==noAnterior->linha && deque->cabeca->coluna > noAnterior->coluna){
            *caracterAnterior=KEY_RIGHT;
          }else if(deque->cabeca->coluna==noAnterior->coluna && deque->cabeca->linha < noAnterior->linha){
            *caracterAnterior=KEY_UP;
          }else *caracterAnterior=KEY_LEFT;
          *linha=deque->cabeca->linha;
          *coluna=deque->cabeca->coluna;
        }
      }
      _moverCobra(caracterAnterior,linha,coluna);
  
}
void posicionarComida(Deque* deque, No* comida)
{ 
    int linhaComida, colunaComida;
    No* aux=deque->cabeca;
    srand (time(NULL));
    linhaComida = (rand() % NUM_LINHA);
    colunaComida =(rand() % NUM_COLUNA);
    while(aux){
       if(aux->linha==linhaComida && aux->coluna==colunaComida){
        linhaComida = (rand() % NUM_LINHA);
        colunaComida =(rand() % NUM_COLUNA);
        aux=deque->cabeca;
       }else
       aux=aux->pro;
    }
    comida->linha=linhaComida;
    comida->coluna=colunaComida;
}
int verificarColisaoCobra(Deque* deque){
  No* no=deque->cabeca->pro;
   while(no){
     if(deque->cabeca->linha==no->linha && deque->cabeca->coluna==no->coluna){
      return 1;
     }
     no=no->pro;
   }
   if(deque->cabeca->linha<0 || deque->cabeca->linha>=NUM_LINHA || deque->cabeca->coluna<0 || deque->cabeca->coluna>=NUM_COLUNA)
    return 1;
   return 0;
}
int verificarColisaoComida(Deque* deque, No* comida, int linha, int coluna)
{
  if(linha==comida->linha && coluna==comida->coluna){
    inserirCorpo(deque,'*',linha,coluna);
    return 1;
  }return 0;
}
int main(int argc, char** argv)
{
   initscr();
   int caracter, linha=NUM_LINHA/2, coluna=NUM_COLUNA/2,i,caracterAnterior=KEY_RIGHT,pontuacao=0;  
   No* comida=criarNo('O',0,0);
   WINDOW* parede;
   Deque* deque=criarDeque();
   start_color(); 
   init_pair(1,COLOR_WHITE,COLOR_BLUE);
   bkgd(COLOR_PAIR(1));
   raw();   /* configura entrada por caracter */
   echo(); 
   curs_set(0);     //não mostra o cursor 
   keypad(stdscr,10);    //habilita o recebimento de teclas especiais 
   
   printw("      _    _                                    \n");   
   printw(",-(|)--(|)-.\n");
   printw("\\_   ..   _/\n");
   printw("  \\______/\n");
   printw("    V  V                                  ____\n");
   printw("    `.^^`.                               /^,--`\n");
   printw("      \\^^^\\                             (^^\\    \n"); 
   printw("      |^^^|                  _,-._       \\^^\\   \n"); 
   printw("     (^^^^\\      __      _,-'^^^^^`.    _,'^^)\n");
   printw("      \\^^^^`._,-'^^`-._.'^^^^__^^^^ `--'^^^_/   \n");
   printw("       \\^^^^^ ^^^_^^^^^^^_,-'  `.^^^^^^^^_/\n");
   printw("        `.____,-' `-.__.'        `-.___.'       \n");









   parede=imprimirParedes();
   wrefresh(parede);
   //criar corpo
   for (i = 0; i < 4; ++i)
   {
     inserirCorpo(deque,'*',linha, coluna++);
   }
   coluna--;
   posicionarComida(deque,comida);
   imprimirCobra(deque,parede);
        //sem mostrar os caracteres digitados 
    halfdelay(1);  //configura espera por tecla no máximo o tempo fornecido 
   for(;;)
   {  
      caracter = getch();
      moverCobra(deque,&caracter,&caracterAnterior,&linha,&coluna);
      if(verificarColisaoComida(deque,comida,linha,coluna)){
        posicionarComida(deque,comida);
        pontuacao++;
      }else atualizarCobra(deque,linha,coluna);
      wclear(parede);
       if(verificarColisaoCobra(deque)) break;
      mvwprintw(stdscr,POSICAO_LINHA_PAREDE-1,POSICAO_COLUNA_PAREDE,"A sua pontuacao eh: %d",pontuacao);
      mvwprintw(parede,comida->linha,comida->coluna,"%c",comida->dado);
      imprimirCobra(deque,parede);
      wrefresh(parede);
   }
   clear();
   endwin();      /* função para finalizar NCURSES */
   return pontuacao;
}