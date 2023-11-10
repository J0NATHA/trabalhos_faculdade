#include <stdio.h>
#include <stdlib.h>
#include "TADs_pilha_fila_aloc_enc.h"

//TAD pilha com alocação encadeada
//cria uma pilha vazia
void CriaPilhaVazia(TipoPilha *pilha)
{
    pilha->topo = (TipoCelula *)malloc(sizeof(TipoCelula));
    pilha->fundo = pilha->topo;
    pilha->topo->proximo = NULL;
}

//testa se a pilha é vazia
int TestaPilhaVazia(TipoPilha *pilha)
{
    return (pilha->topo == pilha->fundo);
}

//insere um elemento na pilha
void InserePilha(TipoPilha *pilha, TipoItem item)
{
    TipoCelula *aux = (TipoCelula *)malloc(sizeof(TipoCelula));
    pilha->topo->item = item;
    aux->proximo = pilha->topo;
    pilha->topo = aux;
}

//remove um elemento da pilha
void RemovePilha(TipoPilha *pilha, TipoItem *item)
{
    if (TestaPilhaVazia(pilha))
    {
        printf("Erro: pilha vazia\n");
        return;
    }
    TipoCelula *q = pilha->topo;
    pilha->topo = q->proximo;
    *item = q->proximo->item;
    free(q);
}

//imprime os elementos da pilha
void ImprimePilha(TipoPilha *pilha)
{
    TipoCelula *aux = pilha->topo->proximo;
    while (aux != NULL)
    {
        printf("%i ", aux->item.valor);
        aux = aux->proximo;
    }
}
