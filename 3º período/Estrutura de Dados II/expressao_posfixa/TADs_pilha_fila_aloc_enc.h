//TADs lineares (pilha e fila) com alocação encadeada (dinâmica)

//tipo exportado
//define o TipoItem que é o tipo dos elementos dos TADs
typedef struct
{
    int valor;
    //outros campos
}TipoItem;

//tipo exportado
//define o TipoCelula que é o tipo das células que contêm os elementos que são manipulados pelos TADs
typedef struct celula
{
    TipoItem item;
    struct celula *proximo;
}TipoCelula;

//-----TAD pilha-----

//tipo exportado
//define o TipoPilha que é o tipo do TAD pilha
typedef struct
{
    TipoCelula *topo;
    TipoCelula *fundo;
}TipoPilha;

//funções exportadas
//cria uma pilha vazia
void CriaPilhaVazia(TipoPilha *pilha);

//testa se a pilha é vazia
int TestaPilhaVazia(TipoPilha *pilha);

//insere um elemento do tipo TipoItem na pilha
void InserePilha(TipoPilha *pilha, TipoItem item);

//remove um elemento do tipo TipoItem da pilha
void RemovePilha(TipoPilha *pilha, TipoItem *item);

//imprime os elementos da pilha
void ImprimePilha(TipoPilha *pilha);

//-----TAD fila-----

//tipo exportado
//define o TipoFila que é o tipo do TAD fila
typedef struct
{
    TipoCelula *frente;
    TipoCelula *tras;
}TipoFila;

//funções exportadas
//cria uma fila vazia
void CriaFilaVazia(TipoFila *fila);

//testa se a fila é vazia
int TestaFilaVazia(TipoFila *fila);

//insere um elemento do tipo TipoItem na fila
void InsereFila(TipoFila *fila, TipoItem item);

//remove um elemento do tipo TipoItem da fila
void RemoveFila(TipoFila *fila, TipoItem *item);

//imprime os elementos da fila
void ImprimeFila(TipoFila *fila);
