/*
    Aluno: Jonatha Salles Menezes
    Matrícula: 2211312125
    Disciplina: Estrutura de dados II
    Professor: Eugênio Silva
*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAXNUMVERTICES 100
#define MAXNUMARESTAS 4500
#define PESO 1

typedef unsigned short ushort;

typedef struct TipoItem
{
    ushort vertice;
    char disciplina[10];

}TipoItem;

typedef struct TipoCelula
{
    TipoItem item;
    struct TipoCelula* proximo;

}TipoCelula;

typedef struct TipoLista
{
    TipoCelula *primeiro, *ultimo;

}TipoLista;

typedef struct TipoGrafo
{
    ushort matriz[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
    char disciplinas[MAXNUMVERTICES + 1][10];
    ushort numeroVertices;
    ushort numeroArestas;

}TipoGrafo;

///Grafo
void criaGrafoVazio(TipoGrafo*);
void imprimeGrafo(TipoGrafo*);
void visitaProfundidade(ushort, TipoGrafo*, ushort*, ushort*, ushort*, ushort*, short*, TipoLista*);
void buscaEmProfundidade(TipoGrafo*, TipoLista*);
short listaAdjacentesVazia(ushort*, TipoGrafo*);
short primeiroListaAdjacentes(ushort*, TipoGrafo*);
void proximoAdjacente(ushort*, TipoGrafo*, ushort*, ushort*, ushort*, short*);
void insereAresta(ushort, ushort, ushort, TipoGrafo*);
//Atribui o código da disciplina ao vértice
void nomeiaVertice(char*, ushort, TipoGrafo*);
//Retorna se a disciplina já foi inserida
int itemJaExiste(char*, int*, TipoGrafo*);

//Lista
void criaListaVazia(TipoLista*);
void insereLista(TipoItem*, TipoLista*);

///Arquivos
FILE* abreArquivo(const char*, const char*);

///Lê um arquivo e transcreve para um grafo
void arquivoParaGrafo(FILE*, TipoGrafo*); 

///Escreve a lista no arquivo
void listaParaArquivo(TipoLista*, FILE*);

///Retorna o próximo caractere do arquivo, util para detectar quebras de linha e fim de arquivo.
char proximoCharArquivo(FILE*);

int main()
{
    FILE* gradeCurricular = abreArquivo("grade_curricular.txt", "r");
    printf("Arquivo encontrado.\n");

    TipoGrafo* grafoCurricular = (TipoGrafo*)malloc(sizeof(TipoGrafo));
    grafoCurricular->numeroArestas = MAXNUMARESTAS;
    grafoCurricular->numeroVertices = MAXNUMVERTICES;

    TipoLista* listaOrdenacaoTopologica = (TipoLista*)malloc(sizeof(TipoLista));

    criaGrafoVazio(grafoCurricular);
    criaListaVazia(listaOrdenacaoTopologica);
    arquivoParaGrafo(gradeCurricular, grafoCurricular); 
    buscaEmProfundidade(grafoCurricular, listaOrdenacaoTopologica);

    fclose(gradeCurricular);

    FILE* ordemCurricular = abreArquivo("ordem_curricular.txt", "w"); //Cria ou sobrescreve o arquivo de saída
    listaParaArquivo(listaOrdenacaoTopologica, ordemCurricular); 

    fclose(ordemCurricular);

    printf("Processo concluido.\n");

    return 0;
}

FILE* abreArquivo(const char* nomeArquivo, const char* modo)
{
    FILE* arquivo = fopen(nomeArquivo, modo);

    if (arquivo == NULL)
    {
        printf("Nao foi possível abrir o arquivo.");
        exit(-1);
    }

    return arquivo;
}

void criaGrafoVazio(TipoGrafo* grafo)
{
    for (ushort i = 0; i < grafo->numeroVertices; i++)
    {
        for (ushort j = 0; j < grafo->numeroVertices; j++)
        {
            grafo->matriz[i][j] = 0;
        }
    }
}

void criaListaVazia(TipoLista* lista)
{
    lista->primeiro = (TipoCelula*)malloc(sizeof(TipoCelula));
    lista->ultimo = (TipoCelula*)malloc(sizeof(TipoCelula));
    lista->primeiro->proximo = NULL;
}

void arquivoParaGrafo(FILE* arquivo, TipoGrafo* grafo)
{
    char disciplinaAtual[10];
    char disciplinaAdjacente[10];

    int verticeAtual = 0,
    verticeAdjacente = 0,
    aux = -1,
    indice;

    while(1)
    {
        if(proximoCharArquivo(arquivo) == '\n' || verticeAtual == 0) 
        {
            fscanf(arquivo, "%s", disciplinaAtual); 
            if(itemJaExiste(disciplinaAtual, &indice, grafo))
            {
                verticeAtual = indice;
            } 
            else
            {
                verticeAtual = ++aux;
                nomeiaVertice(disciplinaAtual, verticeAtual, grafo);
            }
        }

        if (proximoCharArquivo(arquivo) == '\n')
        {
            verticeAtual = 0;
            continue;
        } 
        else if (proximoCharArquivo(arquivo) == EOF) break;

        fscanf(arquivo, "%s", disciplinaAdjacente);

        if(itemJaExiste(disciplinaAdjacente, &indice, grafo))
        {
            verticeAdjacente = indice;
        }
        else
        {
            verticeAdjacente = ++aux;
            nomeiaVertice(disciplinaAdjacente, verticeAdjacente, grafo);
        }
        
        insereAresta(verticeAtual, verticeAdjacente, PESO, grafo); 
    }

    grafo->numeroVertices = aux + 1;
}

char proximoCharArquivo(FILE *arquivo)
{
    char proximoChar = fgetc(arquivo);
    fpos_t posicao;

    fgetpos(arquivo, &posicao); 

    if (proximoChar != EOF)
    {
        posicao--;
        fsetpos(arquivo, &posicao);
        return proximoChar;
    }

    return EOF;
}

int itemJaExiste(char* item, int* indice, TipoGrafo* grafo)
{
    for (int i = 0; i < grafo->numeroVertices - 1; i++)
    {
        if (!strcmp(item, grafo->disciplinas[i]))
        {
            *indice = i;
            return 1;
        }
    }
    return 0;
}

void listaParaArquivo(TipoLista* lista, FILE* arquivo)
{
    fputs("Sequência válida das disciplinas a serem cursadas:\n[\n\t", arquivo);
    TipoCelula* aux = lista->primeiro->proximo;
    ushort cont = 0;
    
    while(aux != NULL)
    {
        fprintf(arquivo, "%s(%i) ", aux->item.disciplina, aux->item.vertice);
        aux = aux->proximo;

        if(aux != NULL) fputs("-> ", arquivo);

        if(cont++ == 3)
        {
            cont = 0;
            fprintf(arquivo, "%s", "\n\t");
        } 
    }

    fputs("\n]", arquivo);

    free(aux);
}

void insereAresta(ushort V1, ushort V2, ushort peso, TipoGrafo *grafo)
{
    grafo->matriz[V1][V2] = peso;
}

void nomeiaVertice(char* nome, ushort vertice, TipoGrafo *grafo)
{
    int _;
    if (!itemJaExiste(nome, &_, grafo))
        strcpy(grafo->disciplinas[vertice], nome);
}

short listaAdjacentesVazia(ushort *vertice , TipoGrafo *grafo)
{
    ushort aux = 0;
    while (aux < grafo->numeroVertices)
    {
        if (grafo->matriz[*vertice][aux] > 0 || grafo->matriz[aux][*vertice] > 0) 
        {
            return 0;
        }
        aux++;
    }
    return 1;
}

short primeiroListaAdjacentes(ushort *vertice, TipoGrafo *grafo)
{
    ushort resultado;
    if(listaAdjacentesVazia(vertice, grafo)) return -1;

    for(short i = 0; i < grafo->numeroVertices; i++)
    {
        if(grafo->matriz[*vertice][i] > 0)
        {
            resultado = i;
            break;
        }
    }
    return resultado;
}

void proximoAdjacente(ushort *vertice, TipoGrafo *grafo, ushort *adjacente,
                      ushort *peso, ushort *proximo, short *fimDaListaAdjacentes)
{
    *adjacente = *proximo;
    *peso = grafo->matriz[*vertice][*proximo];
    *fimDaListaAdjacentes = 0;
    (*proximo)++;
    while(*proximo < grafo->numeroVertices && grafo->matriz[*vertice][*proximo] == 0)
    {
        (*proximo)++;
    }
    if (*proximo == grafo->numeroVertices) *fimDaListaAdjacentes = 1;

}

void visitaProfundidade(ushort u, TipoGrafo *grafo, ushort* tempo,
                        ushort* tempoDescoberta, ushort* tempoTermino, ushort* cor, short* antecessor, TipoLista* lista)
{
    TipoItem* item = (TipoItem*)malloc(sizeof(TipoItem)); 
    short fimListaAdjacentes;
    ushort peso;
    ushort aux;
    ushort vertice;
    cor[u] = 1;
    (*tempo)++;
    tempoDescoberta[u] = (*tempo);

    if (!listaAdjacentesVazia(&u, grafo))
    {
        aux = primeiroListaAdjacentes(&u, grafo);
        fimListaAdjacentes = 0;
        while (!fimListaAdjacentes)
        {
            proximoAdjacente(&u, grafo, &vertice, &peso, &aux, &fimListaAdjacentes);
            if (cor[vertice] == 0)
            {
                antecessor[vertice] = u;
                visitaProfundidade(vertice, grafo, tempo, tempoDescoberta, tempoTermino, cor, antecessor, lista);
            }
        }
    }

    cor[u] = 2;
    (*tempo)++;
    tempoTermino[u] = (*tempo);

    item->vertice = u;
    strcpy(item->disciplina, grafo->disciplinas[u]); //Copia para o item o nome da disciplina no vértice u
    insereLista(item, lista); //Insere item na lista de ordenação topológica    

    free(item);
}

void buscaEmProfundidade(TipoGrafo *grafo, TipoLista* lista)
{
    ushort x;
    ushort tempo;
    ushort tempoDescoberta[MAXNUMVERTICES + 1], tempoTermino[MAXNUMVERTICES + 1];
    ushort cor[MAXNUMVERTICES + 1];
    short antecessor[MAXNUMVERTICES + 1];
    tempo = 0;

    for (x = 0; x <= grafo->numeroVertices - 1; x++)
    {
        cor[x] = 0;
        antecessor[x] = -1;
    }

    for (x = 0; x <= grafo->numeroVertices - 1; x++)
    {
        if (cor[x] == 0) 
        {
            visitaProfundidade(x, grafo, &tempo, tempoDescoberta, tempoTermino, cor, antecessor, lista);
        }
    }
}

void insereLista(TipoItem* item , TipoLista* lista)
{
    TipoCelula* aux;
    aux = lista->primeiro->proximo;

    lista->primeiro->proximo = (TipoCelula*)malloc(sizeof(TipoCelula));

    lista->primeiro->proximo->item = *item;

    lista->primeiro->proximo->proximo = aux;
}