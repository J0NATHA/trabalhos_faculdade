/*
    Aluno: Jonatha Salles Menezes
    Matrícula: 2211312125
    Disciplina: Estrutura de dados II
    Professor: Eugênio Silva
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include "TAD_arvore_binaria_busca.h"
#define TAMANHO_MENSAGEM 200
#define PRETO "\033[30m"
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define AZUL "\033[34m"
#define AZUL_DESTAQUE "\033[44m"
#define ROXO "\033[35m"
#define LIMPA "\033[m"

///
int menu();
void entradaMensagem(char*);
int desconstroiMensagem(char*, TipoItem*); //retorna o tamanho do vetor de pacotes
void fisherYates(TipoItem*, int);
void imprimeSequencia(TipoItem*, int);
void constroiArvore(TipoCelula**, TipoItem*, int);
void reconstroiMensagem(TipoCelula**, char*);
void imprimeMensagemReconstruida(char*);
///

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    char mensagem[TAMANHO_MENSAGEM],
    mensagemReconstruida[TAMANHO_MENSAGEM];
    TipoItem pacotes [TAMANHO_MENSAGEM * 10];
    TipoCelula** arvore = (TipoCelula**)malloc(sizeof(TipoCelula*));

    while(1)
    {
        int opcao = menu();
        if (opcao == 2) break;

        entradaMensagem(mensagem);

        int tamanhoPacotes = desconstroiMensagem(mensagem, pacotes);

        fisherYates(pacotes, tamanhoPacotes);

        imprimeSequencia(pacotes, tamanhoPacotes);

        constroiArvore(arvore, pacotes, tamanhoPacotes);

        reconstroiMensagem(arvore, mensagemReconstruida);

        imprimeMensagemReconstruida(mensagemReconstruida);
    }

    return 0;
}

int menu()
{
    int opcao;

    do
    {
        system("cls");
        printf("\t%s//======================================\\\\%s\n", AMARELO, LIMPA);
        printf("\t    %sSistema de comunicação por pacotes%s\n", AZUL, LIMPA);
        printf("\t%s\\\\======================================//%s\n", AMARELO, LIMPA);
        printf("\t%s [ 1 ] Enviar uma mensagem%s\n", VERDE, LIMPA);
        printf("\t%s [ 2 ] Encerrar aplicação%s\n", VERMELHO, LIMPA);
        printf("\t%s-> ", ROXO);
        scanf("%i", &opcao);
        fflush(stdin);
        puts(LIMPA);
    } while(opcao < 1 || opcao > 2);

    system("cls");

    return opcao;
}

void entradaMensagem(char* mensagem)
{
    printf("\t%sPasso 1 / 5:\n", AMARELO);
    printf("\t%sDigite a mensagem a ser enviada%s \n\t%s-> ", AZUL_DESTAQUE, LIMPA, ROXO);
    gets(mensagem);
    puts(LIMPA);

    printf("\n\t%sA mensagem a ser enviada é: %s%s\n\t\"%s\"%s", AZUL_DESTAQUE, LIMPA, VERMELHO, mensagem, LIMPA);
    Sleep(2500);

    system("cls");
}

int desconstroiMensagem(char* mensagem, TipoItem* pacotes)
{
    int posicaoSequencia = 0;

    for (int posicaoMensagem = 0, numeroPacotes; mensagem[posicaoMensagem] != '\0'; posicaoMensagem++)
    {
        system("cls");

        numeroPacotes = (rand() % 10) + 1;

        puts(AMARELO);
        printf("Passo 2 / 5:\n");
        printf("Empacotando mensagem...\n\n");
        printf("O pacote \'%c\' será enviado %i vez", mensagem[posicaoMensagem], numeroPacotes);

        numeroPacotes > 1 ? printf("es...\n") : printf("...\n"); //Imprime o plural se o número de pacotes or maior que 1

        printf("ID = %i, DADO = \'%c\'\n", posicaoMensagem, mensagem[posicaoMensagem]);

        for (int contador = 1; contador <= numeroPacotes; contador++, posicaoSequencia++)
        {
            pacotes[posicaoSequencia].chave = posicaoMensagem; //Os pacotes repetidos recebem a mesma etiqueta
            pacotes[posicaoSequencia].pacote = mensagem[posicaoMensagem];
            printf("Pacote %i/%i... ", contador, numeroPacotes);
            Sleep(25);
        }
        puts(LIMPA);
    }
    puts(VERDE);
    printf("Mensagem empacotada.\n");

    Sleep(1000);

    return posicaoSequencia;
}

void imprimeSequencia(TipoItem* sequencia, int tamanho)
{
    for(int i = 0, delay = 50; i < tamanho; i++)
    {
        system("cls");

        puts(AMARELO);
        printf("Passo 3 / 5:\n");
        printf("Enviando pacotes...\n");

        puts(AZUL);
        printf("Pacote %i/%i: (ID = %i, DADO = %c)", i + 1, tamanho, sequencia[i].chave, sequencia[i].pacote);
        Sleep(delay);

        if (!(i % 9) && delay)
        {
            delay -= 5; //Diminui o atraso para que não haja muita espera em mensagens grandes
        }
    }
    puts(VERDE);
    printf("\nMensagem enviada.\n");

    Sleep(1000);
    system("cls");
}

void fisherYates(TipoItem* sequencia, int tamanho)
{
    for (int i = tamanho - 1; i > 0; i--)
    {
        srand(time(NULL));
        int j = rand() % (i + 1);

        TipoItem temp = sequencia[i];
        sequencia[i] = sequencia[j];
        sequencia[j] = temp;
    }
}

void constroiArvore(TipoCelula** arvore, TipoItem* sequencia, int tamanho)
{
    CriaArvoreBinariaBuscaVazia(arvore);

    for (int i = 0, delay = 120; i < tamanho; i++)
    {
        puts(PRETO); //Texto fica invisível :D
        InsereArvoreBinariaBusca(arvore, sequencia[i]);

        system("cls");
        puts(AMARELO);
        printf("Passo 4 / 5:\n");
        printf("Recebendo pacotes...\n");

        if (delay)
        {
            puts(VERDE);
            ImprimeArvoreBinariaBusca(arvore, 2);

            if (!(i % 9)) delay -= 10;
        }
        Sleep(delay);
    }
    system("cls");

    puts(AMARELO);
    printf("Passo 4 / 5:\n");
    printf("Recebendo pacotes...\n");

    puts(VERDE);
    ImprimeArvoreBinariaBusca(arvore, 2);

    printf("\n\nPacotes recebidos.\n");

    Sleep(1000);
    system("cls");
}

void reconstroiMensagem(TipoCelula** arvore, char* mensagem)
{
    TipoItem* item;

    for(int i = 0; i < TAMANHO_MENSAGEM; i++)
    {
        mensagem[i] = '\0'; //Limpeza da cadeia de caracteres para exibição
    }

    for(int chave = 0, delay = 500; !TestaArvoreBinariaBuscaVazia(arvore); chave++)
    {
        system("cls");
        item = BuscaArvoreBinariaBusca(arvore, chave);

        mensagem[chave] = item->pacote;
        RemoveArvoreBinariaBusca(arvore, *item);

        puts(AMARELO);
        printf("Passo 5 / 5:\n");
        printf("Reconstruindo mensagem...\n");

        puts(VERDE);
        ImprimeArvoreBinariaBusca(arvore, 2);

        puts(AMARELO);
        printf("\nMensagem: \n\"%s\"", mensagem);
        puts(LIMPA);

        if (!(chave % 9) && delay)
        {
            delay -= 100;
        }
        Sleep(delay);
    }
    puts(VERDE);
    printf("Mensagem reconstruída.");
    puts(LIMPA);

    Sleep(1000);
    system("cls");
}

void imprimeMensagemReconstruida(char* mensagemReconstruida)
{
    printf("//====================================================================================================================\\\\");
    printf("\n  %sA mensagem reconstruída é:%s%s\n  \"%s\"\n%s", AZUL_DESTAQUE, LIMPA, VERMELHO, mensagemReconstruida, LIMPA);
    printf("\\\\====================================================================================================================//");
    printf("\n\n%sPressione enter...%s", VERDE, LIMPA);
    while (getchar() != '\n');
}
