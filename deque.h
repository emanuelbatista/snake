#include "no.h"

//Estrutura Deque
typedef struct deque
{
	No* cabeca;
	No* calda;
	int tamanho;
}Deque;

Deque* criarDeque(void);

void dequeInserir(Deque* deque, No* no);

void dequeRemover(Deque* deque);