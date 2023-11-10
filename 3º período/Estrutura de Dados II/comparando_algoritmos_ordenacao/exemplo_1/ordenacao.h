
typedef struct
{
    int chave;
    //outros campos
}TipoItem;    //tipo dos itens que compõem a sequência

void select_sort(TipoItem *vet, int n, int *cp, int *mv);

void insert_sort(TipoItem *vet, int n, int *cp, int *mv);

void bubble_sort(TipoItem *vet, int n, int *cp, int *mv);

void merge_sort(TipoItem *vet, int n);

void shell_sort(TipoItem *vet, int n);

void quick_sort(TipoItem *vet, int n);

void heap_sort(TipoItem *vet, int n);

//void even_odd(TipoItem *vet, int n, int *cp, int *mv);
