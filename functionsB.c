#include "header2.h"

char** alloc_mat(int n, int m)
{
    char** mat = malloc(n * sizeof(char*));

    if(mat == NULL)
    {
        printf("Eroare la alocarea dinamica a matricei!\n");
        exit(1);
    }

    for(int i = 0; i < n; i++)
    {
        mat[i] = malloc((m+1) * sizeof(char));
        
        if(mat[i] == NULL)
        {
            printf("Eroare la alocarea dinamica a matricei la linia %d!\n", i);
            exit(1);
        }
    }

    return mat;
}

char** read(int *t, int *n, int *m, int *k, const char* fisier_intrare, StackNode** stack)
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

        for (int gen = 0; gen < *k; gen++)
        {
            int nr_modificari;
            fscanf(f, "%d", &nr_modificari);
    
            ListNode* lista = NULL;
            for (int i = 0; i < nr_modificari; i++)
            {
                int l, c;
                fscanf(f, "%d %d", &l, &c);
                insert_sort(&lista, l, c);
            }
    
            push(stack, lista);
        }
    
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

void insert_sort(ListNode** head, int i, int j)
{
    ListNode* new_node = malloc(sizeof(ListNode));
    if(new_node == NULL)
    {
        printf("Eroare la alocarea dinamica a listei!\n");
        exit(1);
    }

    new_node->l = i;
    new_node->c = j;
    new_node->next = NULL;
    
    if(*head == NULL || (*head)->l > i || ((*head)->l == i && (*head)->c > j))
    {
        new_node->next = *head;
        *head = new_node;
    }

    else
    {
        ListNode* current = *head;
        while(current->next != NULL && (current->next->l < i || (current->next->l == i && current->next->c < j)))
            current = current->next;

        new_node->next = current->next;
        current->next = new_node;
    }
}

void reverse_stack(StackNode** stack)
{
    StackNode* prev = NULL;
    StackNode* current = *stack;
    StackNode* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *stack = prev;
}

void push(StackNode** stack, ListNode* list)
{
    StackNode* new_node = malloc(sizeof(StackNode));
    if(new_node == NULL)
    {
        printf("Eroare la alocarea dinamica a stivei!\n");
        exit(1);
    }

    new_node->list = list;
    new_node->next = *stack;
    *stack = new_node;
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
