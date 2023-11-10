//Aluno: Jonatha Salles Menezes
//Matrícula: 2211312125
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "TADs_pilha_fila_aloc_enc.h"

//
TipoFila* le_expressao(char *exp);
int avalia_expressao(TipoFila *exp, int);
//

int menu()
{
    int opcao;
    do{
        printf("\n\t  Avaliacao de expressoes posfixas\n");
        printf("\t=====================================");
        printf("\n\t\tModo rapido    [1]");
        printf("\n\t\tModo detalhado [2]");
        printf("\n\t\tSair           [3]");
        printf("\n\t=====================================\n");
        printf("\t-> ");
        scanf("%i", &opcao);
        fflush(stdin);
        system("cls");
    }while(opcao < 1 || opcao > 3);
    return opcao;
}

int main(void)
{
    int opcao;
    do{
        opcao = menu();
        if(opcao == 3) break;
        int modoDetalhado = opcao == 2;
        char expressao[30];

        printf("\n\033[36mEntre com a expressao posfixa -> \033[46;30m");
        scanf("%s", expressao);
        printf("\033[m");
        TipoFila* fila = (TipoFila*)malloc(sizeof(TipoFila));
        CriaFilaVazia(fila);
        system("cls");

        fila = le_expressao(expressao);

        printf("\n\033[4;32mResultado final -> %i\n\033[m", avalia_expressao(fila, modoDetalhado));
        sleep(2);
        system("cls");
    }while(opcao != 3);
    return 0;
}

TipoFila* le_expressao(char *exp)
{
    TipoFila* fila = (TipoFila*)malloc(sizeof(TipoFila));
    CriaFilaVazia(fila);
    TipoItem item;
    int cont = 0;
    while (exp[cont] != '\0')
    {
        item.valor = exp[cont];
        InsereFila(fila, item);
        cont++;
    }
    return fila;
}

int avalia_expressao(TipoFila *exp, int modoDetalhado)
{
    TipoPilha* pilha = (TipoPilha*)malloc(sizeof(TipoPilha));
    CriaPilhaVazia(pilha);
    TipoItem item, A, B;
    while(!TestaFilaVazia(exp))
    {
        RemoveFila(exp, &item);
        system("cls");
        if(item.valor == '+' || item.valor == '-' || item.valor == '*' || item.valor == '/')
        {
            RemovePilha(pilha, &B);
            RemovePilha(pilha, &A);
            char operador = item.valor;
            switch(operador)
            {
                case '+':
                    item.valor = A.valor + B.valor;
                    break;
                case '-':
                    item.valor = A.valor - B.valor;
                    break;
                case '*':
                    item.valor = A.valor * B.valor;
                    break;
                case '/':
                    item.valor = A.valor / B.valor;
                    break;
            }
            if (modoDetalhado)
                printf("\n\033[34m%i \033[33m%c \033[34m%i \033[33m= \033[34m%i \033[m\n", A.valor, operador, B.valor, item.valor);
        }
        else
        {
            printf("\n\033[36mEntre com um valor para %c -> ", item.valor);
            scanf("%i", &(item.valor));
            printf("\033[m");
        }

        InserePilha(pilha, item);

        if(modoDetalhado)
        {
            printf("\n\033[32mExpressao -> ");
            ImprimeFila(exp);
            printf("\033[m");
            printf("\n\033[32mPilha -> ");
            ImprimePilha(pilha);
            printf("\033[m\n");
            sleep(2);
            system("cls");
        }
    }
    RemovePilha(pilha, &item);
    return item.valor;
}
