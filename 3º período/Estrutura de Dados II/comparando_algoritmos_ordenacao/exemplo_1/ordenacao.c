#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"

void print_sequence(TipoItem *vet, int n);

//--- SELECTION SORT ---

void select_sort(TipoItem *vet, int n, int *cp, int *mv)
{
    int i, j, min;
    TipoItem item;

    for (i = 1; i <= n - 1; i++)
    {
        min = i;
        for (j = i + 1; j <= n; j++)
        {
            (*cp)++;  // contador de comparacões
            if (vet[j].chave < vet[min].chave)
                min = j;
        }
        item = vet[min];
        (*mv)++;  // contador de movimentações
        vet[min] = vet[i];
        (*mv)++;  // contador de movimentações
        vet[i] = item;
        (*mv)++;  // contador de movimentações
        print_sequence(vet, n);  // impressão do vetor atual
    }
}

//--- INSERT SORT ---

void insert_sort(TipoItem *vet, int n, int *cp, int *mv)
{
    int i, j;
    TipoItem item;

    for (i = 2; i <= n; i++)
    {
        item = vet[i];
        (*mv)++;  // contador de movimentações
        j = i - 1;
        vet[0] = item;
        (*mv)++;  // contador de movimentações
        (*cp)++;  // contador de comparacões
        while (item.chave < vet[j].chave)
        {
            (*cp)++;  // contador de comparacões
            vet[j + 1] = vet[j];
            j--;
            (*mv)++;  // contador de movimentações
        }
        vet[j + 1] = item;
        (*mv)++;  // contador de movimentações
        print_sequence(vet, n);  // impressão do vetor atual
    }
}

//--- BUBBLE SORT ---

void bubble_sort(TipoItem *vet, int n, int *cp, int *mv)
{
    int i, j;
    TipoItem item;

    for (i = n; i >= 2; i--)
    {
        for (j = 2; j <= i; j++)
        {
            (*cp)++;  // contador de comparacões
            if (vet[j].chave < vet[j - 1].chave)
            {
                item = vet[j];
                (*mv)++;  // contador de movimentações
                vet[j] = vet[j - 1];
                (*mv)++;  // contador de movimentações
                vet[j - 1] = item;
                (*mv)++;  // contador de movimentações
            }
        }
        print_sequence(vet, n);  // impressão do vetor atual
    }
}

//--- MERGE SORT ---

void sort_1(int ini, int fim, TipoItem *vet);
void merge(TipoItem *vet, int ini, int meio, int fim);

void merge_sort(TipoItem *vet, int n)
{
    sort_1(1, n, vet);
}

void sort_1(int ini, int fim, TipoItem *vet)
{
    int meio;

    if (ini < fim)
    {
        meio = (ini + fim) / 2;
        sort_1(ini, meio, vet);
        sort_1(meio + 1, fim, vet);
        merge(vet, ini, meio, fim);
    }
}

void merge(TipoItem *vet, int ini, int meio, int fim)
{
    int i = ini;
    int j = meio + 1;
    int k = 0;
    TipoItem *aux = (TipoItem *)malloc(sizeof(TipoItem) * (fim - ini + 1));

    while ((i < meio + 1) || (j < fim + 1))
    {
        if (i == meio + 1 )
        {
            aux[k] = vet[j];
            j++;
            k++;
        }
        else
        {
            if (j == fim + 1)
            {
                aux[k] = vet[i];
                i++;
                k++;
            }
            else
            {
                if (vet[i].chave < vet[j].chave)
                {
                    aux[k] = vet[i];
                    i++;
                    k++;
                }
                else
                {
                    aux[k] = vet[j];
                    j++;
                    k++;
                }
            }
        }
    }

    for(i = ini; i <= fim; i++)
        vet[i] = aux[i - ini];

    free(aux);
}

//--- SHELL SORT ---

void shell_sort(TipoItem *vet, int n)
{
    int i, j, h = 1;
    TipoItem item;

    do
        h = h * 3 + 1;
    while (h < n);
    do
    {
        h /= 3;
        for (i = h + 1; i <= n; i++)
        {
            item = vet[i];
            j = i;
            while (vet[j - h].chave > item.chave)
            {
                vet[j] = vet[j - h];
                j -= h;
                if (j <= h)
                    break;
            }
            vet[j] = item;
        }
    } while (h != 1);
}

//--- QUICK SORT ---

void sort_2(int esq, int dir, TipoItem *vet);
void partition(int esq, int dir, int *i, int *j, TipoItem *vet);

void quick_sort(TipoItem *vet, int n)
{
    sort_2(1, n, vet);
}

void sort_2(int esq, int dir, TipoItem *vet)
{
    int i, j;

    partition(esq, dir, &i, &j, vet);
    if (esq < j)
        sort_2(esq, j, vet);
    if (i < dir)
        sort_2(i, dir, vet);
}

void partition(int esq, int dir, int *i, int *j, TipoItem *vet)
{
    TipoItem pivo, item;

    *i = esq;
    *j = dir;
    pivo = vet[(*i + *j) / 2];
    do
    {
        while (pivo.chave > vet[*i].chave)
            (*i)++;
        while (pivo.chave < vet[*j].chave)
            (*j)--;
        if (*i <= *j)
        {
            item = vet[*i];
            vet[*i] = vet[*j];
            vet[*j] = item;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

// --- HEAP SORT ---

void construct(TipoItem *vet, int n);
void reconstruct(int esq, int dir, TipoItem *vet);

void heap_sort(TipoItem *vet, int n)
{
    int esq, dir;
    TipoItem item;

    construct(vet, n);
    esq = 1;
    dir = n;

    while (dir > 1)
    {
        item = vet[1];
        vet[1] = vet[dir];
        vet[dir] = item;
        dir--;
        reconstruct(esq, dir, vet);
    }
}

void construct(TipoItem *vet, int n)
{
    int esq;

    esq = n / 2 + 1;
    while (esq > 1)
    {
        esq--;
        reconstruct(esq, n, vet);
    }
}

void reconstruct(int esq, int dir, TipoItem *vet)
{
    int j, i = esq;
    TipoItem item;

    j = i * 2;
    item = vet[i];
    while (j <= dir)
    {
        if (j < dir)
            if (vet[j].chave < vet[j + 1].chave)
                j++;
        if (item.chave >= vet[j].chave)
            break;
        else
        {
            vet[i] = vet[j];
            i = j;
            j = i * 2;
        }
    }
    vet[i] = item;
}

// --- EVEN ODD SORT ---

/*
void even_odd(TipoItem *vet, int n, int *cp, int *mv)
{
    int i, troca;
    TipoItem item;

    do
    {
        troca = 0;
        for (i = 1; i < n - 1; i += 2)
            if (vet[i].chave > vet[i + 1].chave)
            {
                item = vet[i];
                vet[i] = vet[i + 1];
                vet[i + 1] = item;
                troca = 1;
            }

        for (i = 2; i < n - 1; i += 2)
            if (vet[i].chave > vet[i + 1].chave)
            {
                item = vet[i];
                vet[i] = vet[i + 1];
                vet[i + 1] = item;
                troca = 1;
            }
    } while (troca != 0);
}
*/

//---

void print_sequence(TipoItem *vet, int n)
{

}
