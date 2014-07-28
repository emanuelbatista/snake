#include "no.h"
#include <stdlib.h>


No* criarNo(char dado, int linha,int coluna){
	No* no=NULL; 
	no=(No*) malloc(sizeof(No));
	if(no){
		no->dado=dado;
		no->pro=NULL;
		no->ante=NULL;
		no->linha=linha;
		no->coluna=coluna;
	}
	return no;
}