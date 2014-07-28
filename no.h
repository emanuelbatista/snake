
typedef struct no
{
	char dado;
	int linha,coluna;
	struct no* pro;
	struct no* ante;
}No;

No* criarNo(char dado, int linha,int coluna);