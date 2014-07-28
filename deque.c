#include <stdlib.h>
#include "deque.h"

//Criar Deque 
Deque* criarDeque(void)
{
	Deque* deque=malloc(sizeof(Deque));
	deque->cabeca=NULL;
	deque->calda=NULL;
	deque->tamanho=0;
	return deque;
}

//Inserir um nó numa estrutura Deque
void dequeInserir(Deque* deque, No* no)
{
  if(no){
  	if(!deque->cabeca){
      deque->cabeca=deque->calda=no;
      no->pro=NULL;
      no->ante=NULL;
      
  	}else{
  	  no->pro=deque->cabeca; 	
  	  no->ante=NULL;
  	  deque->cabeca->ante=no;
  	  deque->cabeca=no;
    }
  }
}

//Remover um nó numa estrutura Deque
void dequeRemover(Deque* deque)
{
   No* no=deque->calda;
  if(!deque->cabeca->pro){
  	deque->cabeca=deque->cabeca->pro;
  	deque->calda=deque->cabeca;
  }else{
  	deque->calda=deque->calda->ante;
    deque->calda->pro=NULL;
  }
  free(no);
}
