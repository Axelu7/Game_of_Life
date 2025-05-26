#include "header2.h"

char** read(int *t, int *n, int *m, int *k, const char* fisier_intrare)
{
    FILE *f = fopen(fisier_intrare, "rt");
    if(f == NULL)
    {
        printf("Eroare la deschiderea fisierului de intrare!\n");
        exit(1);
    }

    fscanf(f, "%d", t);
    fscanf(f, "%d%d", n, m);
    fscanf(f, "%d", k);

    char** mat = alloc_mat(*n, *m);

    for(int i = 0; i < *n; i++)
        fscanf(f,"%s", mat[i]);

    fclose(f);
    return mat;
}

void free_mem_mat(char** mat, int n)
{
    for(int i = 0; i < n; i++)
        free(mat[i]);
    
    free(mat);
}

void free_mem_list(ListNode* list)
{
    ListNode* aux;
    while(list != NULL)
    {
        aux = list;
        list = list->next;
        free(aux);
    }
}

void free_mem_stack(StackNode** stack)
{
    StackNode* aux;
    while(*stack != NULL)
    {
        aux = *stack;
        *stack = (*stack)->next;
        free_mem_list(aux->list);
        free(aux);
    }
}

void bonus(StackNode** stack, char** mat, int n, int m, const char* fisier_iesire)
{
    reverse_stack(stack);

    StackNode* current = *stack;
    while (current != NULL)
    {
        ListNode* list = current->list;
        while (list != NULL)
        {
            mat[list->l][list->c] = (mat[list->l][list->c] == alive) ? dead : alive;
            list = list->next;
        }
        current = current->next;
    }

    FILE *f = fopen(fisier_iesire, "wt");
    if (!f)
    {
        printf("Eroare la deschiderea fisierului de iesire!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fprintf(f, "%c", mat[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);

    free_mem_mat(mat, n);
    free_mem_stack(stack);
}
