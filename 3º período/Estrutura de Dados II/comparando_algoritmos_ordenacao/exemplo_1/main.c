#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "ordenacao.h"
#define TAM 10000

void use_sort(int op2, TipoItem* vet, int* cp, int* mv, int n);
void sequence_generator(TipoItem *vet1, int op, int n);
void copy_array(TipoItem* vet1, TipoItem* vet2, int n);
void shuffle(TipoItem*, int);
char* sort_name(int n);
int choose_sort_method(int op1);
int choose_sequence(void);
int sequence_scale(void);



int main(void)
{
    setlocale(LC_ALL, "");

    int cp = 0, mv = 0, op1, op2;

    int scale = sequence_scale();

    // escolhe crescente, decrescente ou embaralhado
    op1 = choose_sequence();

    // escolhe o método de ordenação
    op2 = choose_sort_method(scale);

    int repetitions = (op1 == 3 || scale == 0) ? 10 : 1; // 10 repetições para cada algoritmo se for sequência embaralhada
    if (scale == 0) scale = 10;                          // ou uma repetição para cada tamanho.

    int arraySize = TAM * scale + 1; // + 1 devido à necessidade do sentinela em alguns métodos

    TipoItem vet[arraySize], vet1[arraySize];

    // gera a sequência com TAM valores a serem ordenados
    sequence_generator(vet1, op1, arraySize);
    copy_array(vet, vet1, arraySize);

    int start, finish;
    double time;
    if(op2 != 8)
    {
        for(int i = 0; i < repetitions; i++)
        {
            start = clock();
            use_sort(op2, vet, &cp, &mv, arraySize);
            finish = clock() - start;
            time = (double)finish / CLOCKS_PER_SEC;
            printf(" Tamanho -> %i\n Tempo estimado -> %fs (%.0fms)\n\n", arraySize - 1,time, time*1000);
            arraySize -= TAM;
            copy_array(vet, vet1, arraySize);
        }
    }
    else
    {
        char* sortName;
        for (int i = 1; i <= 7; i++)
        {
            sortName = sort_name(i);
            int sum = 0;
            for (int j = 0; j < repetitions; j++)
            {
                start = clock();
                use_sort(i, vet, &cp, &mv, arraySize);
                finish = clock() - start;
                time = (double)finish / CLOCKS_PER_SEC;
                sum += time*1000;
                copy_array(vet, vet1, arraySize);

                if (repetitions == 1) break;

                printf("%.0fms", time*1000);
                if (j < repetitions - 1) printf(" + ");
                else printf(" / %i\n", repetitions);
                shuffle(vet, arraySize);
            }
            time = (double)sum / repetitions;
            printf(" %s sort -> %fs (%.1fms)\n\n", sortName, time/1000.0, time);
        }
    }

    // imprime as quantidades de comparações e de trocas (apenas para os métodos simples)
    if (op2 == 1 || op2 == 2 || op2 == 3)
    {
        printf("\n Comparações -> %i", cp);
        printf("\n\n Movimentações -> %i\n", mv);
    }

    return 0;
}

void sequence_generator(TipoItem *vet1, int op, int n)
{
    int i;
    vet1[0].chave = -1;

    for (i = 1; i <= n; i++)
    {
        if (op == 1 || op == 3) vet1[i].chave = i - 1;  // sequência em ordem crescente
        else vet1[i].chave = n - i;  // sequência em ordem decrescente
    }

    if (op == 3) shuffle(vet1, n); // algoritmo de Fisher-Yates para embaralhamento de sequências

}

int choose_sequence(void)
{
    int op;

    do
    {
        printf("\n Opções de sequências:\n\n");
        printf("  1 - valores em ordem crescente\n");
        printf("  2 - valores em ordem decrescente\n");
        printf("  3 - valores embaralhados\n\n");
        printf(" Informe a opção desejada -> ");
        scanf("%i", &op);
        fflush(stdin);
    }while (op != 1 && op != 2 && op != 3);

    return op;
}

int choose_sort_method(int scale)
{
    int op;

    do
    {
        printf("\n Opcões de métodos de ordenação:\n\n");
        printf("  1 - Seleção\n");
        printf("  2 - Inserção\n");
        printf("  3 - Bolha\n");
        printf("  4 - Merge\n");
        printf("  5 - Shell\n");
        printf("  6 - Quick\n");
        printf("  7 - Heap\n");
        if(scale) printf("  8 - Todos\n");
        printf("\n");
        printf(" Informe a opção desejada -> ");
        scanf("%i", &op);
        printf("\n");
        fflush(stdin);
    }while (op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7 && (op != 8 || !scale));

    return op;
}

int sequence_scale()
{
    int scale;
    do
    {
        printf("\n Opcões de tamanho de amostra:\n\n");
        printf("  0 - Todos\n");
        printf("  1 - 10.000\n");
        printf("  2 - 20.000\n");
        printf("  3 - 30.000\n");
        printf("  4 - 40.000\n");
        printf("  5 - 50.000\n");
        printf("  6 - 60.000\n");
        printf("  7 - 70.000\n");
        printf("  8 - 80.000\n");
        printf("  9 - 90.000\n");
        printf(" 10 - 100.000\n\n");
        printf(" Informe a opção desejada -> ");
        scanf("%i", &scale);
        printf("\n");
        fflush(stdin);
    }while (scale < 0 || scale > 10);

    return scale;
}

void use_sort(int op2, TipoItem* vet, int* cp, int* mv, int n)
{
    switch (op2)
    {
        case 1 : { select_sort(vet, n, &cp, &mv); break; }
        case 2 : { insert_sort(vet, n, &cp, &mv); break; }
        case 3 : { bubble_sort(vet, n, &cp, &mv); break; }
        case 4 : { merge_sort(vet, n); break; }
        case 5 : { shell_sort(vet, n); break; }
        case 6 : { quick_sort(vet, n); break; }
        case 7 : { heap_sort(vet, n); break; }
    }
}

char* sort_name(int n)
{
    switch (n)
    {
        case 1 : return "Selection";
        case 2 : return "Insertion";
        case 3 : return "Bubble";
        case 4 : return "Merge";
        case 5 : return "shell";
        case 6 : return "Quick";
        case 7 : return "Heap";
    }
    return NULL;
}

void copy_array(TipoItem* vet1, TipoItem* vet2, int n)
{
    for(int i = 1; i < n; i++)
    {
        vet1[i] = vet2[i];
    }
}

void shuffle(TipoItem *vet, int n)
{
    srand(time(NULL));

    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        TipoItem temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }
}
