#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

void imprimirCobra(Deque* deque)
{
  No* no=deque->cabeca;
  while(no){
    mvprintw(no->linha,no->coluna,"%c",no->dado);
    refresh();
    no=no->pro;
  }
}
void static inserirCorpo(Deque* deque,char dado, int linha,int coluna)
{
  No* no=criarNo(dado,linha,coluna);
  dequeInserir(deque,no);
}

void andarCobra(Deque* deque,int linha, int coluna)
{
   inserirCorpo(deque,'*',linha,coluna);
   dequeRemover(deque);
}


// Função para imprimir as paredes do jogo Snake
void imprimirParedes(int linhaParedeCima,int linhaParedeBaixo,int colunaParedeEsquerda,int colunaParedeDireita)
{

    int i;

    //Parede de Cima
   for (i = colunaParedeEsquerda; i <colunaParedeDireita+1; ++i)
   {
      mvprintw(linhaParedeCima,i,"*");
   }

   //Parede esquerda
   for (i = linhaParedeCima+1; i <linhaParedeBaixo; ++i)
   {
      mvprintw(i,colunaParedeEsquerda,"*");
   }

   //Parede de Baixo  
   for (i = colunaParedeEsquerda; i <colunaParedeDireita+1; ++i)
   {
      mvprintw(linhaParedeBaixo,i,"*");
   }

   //Parede direita
      for (i = linhaParedeCima+1; i <linhaParedeBaixo; ++i)
   {
       mvprintw(i,colunaParedeDireita,"*");
   }
   refresh();
}

void moverCobra(int* caracter, int* caracterAnterior,int* linha, int* coluna)
{

      if (*caracter!=ERR)
      {
        if(*caracter==KEY_LEFT && *caracterAnterior!=KEY_RIGHT ||
          *caracter==KEY_RIGHT && *caracterAnterior!=KEY_LEFT ||
          *caracter==KEY_UP && *caracterAnterior!=KEY_DOWN ||
          *caracter==KEY_DOWN && *caracterAnterior!=KEY_UP )

          *caracterAnterior=*caracter;
        
      }
        if(*caracterAnterior==KEY_LEFT)
          (*coluna)--;

        if(*caracterAnterior==KEY_RIGHT)
          (*coluna)++; 

        if(*caracterAnterior==KEY_UP)
          (*linha)--;

        if(*caracterAnterior==KEY_DOWN)
          (*linha)++;
}
int main(int argc, char** argv)
{
   initscr();
   int linhaParedeCima=1, linhaParedeBaixo=20,colunaParedeEsquerda=4,colunaParedeDireita=50,caracter, linha=5, coluna=20,i,aux=KEY_RIGHT;
   Deque* deque=criarDeque();
   start_color(); 
   init_pair(1,COLOR_WHITE,COLOR_BLUE);
   bkgd(COLOR_PAIR(1));
   curs_set(0);
   imprimirParedes(linhaParedeCima,linhaParedeBaixo,colunaParedeEsquerda,colunaParedeDireita);
   //criar corpo
   for (i = 0; i < 4; ++i)
   {
     inserirCorpo(deque,'*',linha, coluna++);
   }
   coluna--;
   imprimirCobra(deque);
   for (i = 0; i < 100; ++i)
   {  
      echo();       //sem mostrar os caracteres digitados 
      keypad(stdscr, 10);    //habilita o recebimento de teclas especiais 
      halfdelay(1*10);  //configura espera por tecla no máximo o tempo fornecido 
      caracter = wgetch(stdscr);
      curs_set(0);     //não mostra o cursor 
      moverCobra(&caracter,&aux,&linha,&coluna);
      andarCobra(deque,linha,coluna);
      clear();
      imprimirParedes(linhaParedeCima,linhaParedeBaixo,colunaParedeEsquerda,colunaParedeDireita);
      imprimirCobra(deque);
   }
   
   refresh();
   endwin();      /* função para finalizar NCURSES */
   return 0;
}