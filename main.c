#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

void imprimirCobra(Deque* deque)
{
  No* no=deque->cabeca;
  while(no){
    move(no->linha,no->coluna);
    printw("%c",no->dado);
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
      move(linhaParedeCima,i);
      printw("*");
      
   }

   //Parede esquerda
   for (i = linhaParedeCima+1; i <linhaParedeBaixo; ++i)
   {
      move(i,colunaParedeEsquerda);
      printw("*");
      refresh();
   }

   //Parede de Baixo  
   for (i = colunaParedeEsquerda; i <colunaParedeDireita; ++i)
   {
      move(linhaParedeBaixo,i);
      printw("*");
      refresh();
   }

   //Parede direita
      for (i = linhaParedeCima+1; i <linhaParedeBaixo; ++i)
   {
       move(i,colunaParedeDireita);
       printw("*");
       refresh();
   }
}


int main(int argc, char** argv)
{
   initscr();
   int linhaParedeCima, linhaParedeBaixo,colunaParedeEsquerda,colunaParedeDireita,caracter, linha=5, coluna=20,i;
   linhaParedeCima=1;
   linhaParedeBaixo=25;
   colunaParedeEsquerda=4;
   colunaParedeDireita=50;
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
   imprimirCobra(deque);
   clear();
   for (i = 0; i < 10; ++i)
   {
      andarCobra(deque,linha,coluna++);
      imprimirParedes(linhaParedeCima,linhaParedeBaixo,colunaParedeEsquerda,colunaParedeDireita);
      imprimirCobra(deque);
      keypad(stdscr, 1);
      getch();
      clear();
   }
   //criarCobra(deque,'*');
    //Parede de cima

 
   //raw();       //configura entrada por caracter 
   
   
   echo();       //sem mostrar os caracteres digitados 
   curs_set(1);     //não mostra o cursor 
   keypad(stdscr, 10);    //habilita o recebimento de teclas especiais 
   halfdelay(100000000*10);  //configura espera por tecla no máximo o tempo fornecido 
   caracter = wgetch(stdscr);
   refresh();
   endwin();      /* função para finalizar NCURSES */
   return 0;
}