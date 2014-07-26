typedef struct deque
{
	No* cabeca;
	No* calda;
	int tamanho;
}Deque;

Deque criarDeque(void);

void dequeInserir(Deque* deque, char dado);

void dequeRemover(Deque* deque);