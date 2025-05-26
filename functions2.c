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

void write(StackNode** stack, const char* fisier_iesire)
{
    FILE *f = fopen(fisier_iesire, "wt");
    if(f == NULL)
    {
        printf("Eroare la deschiderea fisierului de iesire!\n");
        exit(1);
    }

    reverse_stack(stack);
    StackNode* current = *stack;
    int gen = 1;
    while(current != NULL)
    {
        fprintf(f, "%d", gen++);

        ListNode* list = current->list;
        while(list != NULL)
        {
            fprintf(f, " %d %d", list->l, list->c);
            list = list->next;
        }

        fprintf(f, "\n");
        current = current->next;
        }
    fclose(f);
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

int vecini(char** mat, int n, int m, int lin, int col)
{
    int nr = 0;

    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(i == 0 && j == 0)
                continue;

            int coord_lin = i + lin;
            int coord_col = j + col;
            if(coord_lin >= 0 && coord_lin < n && coord_col >= 0 && coord_col < m && mat[coord_lin][coord_col] == alive)
                nr++;
        }
    }
    return nr;
}

void GoL(StackNode** stack, int k, int n, int m, char** mat, const char* fisier_iesire)
{
    char** nou_mat = alloc_mat(n, m);
    for(int gen = 0; gen < k; gen++)
    {
        ListNode* list = NULL;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                int nr_vecini = vecini(mat, n, m, i, j);

                if(mat[i][j] == alive)
                {
                    
                    if(nr_vecini < 2 || nr_vecini > 3)
                    {
                        nou_mat[i][j] = dead;
                        insert_sort(&list, i, j);
                    }
                    else
                        nou_mat[i][j] = alive;
                }

                else
                {
                    if(nr_vecini == 3)
                    {
                        insert_sort(&list, i, j);
                        nou_mat[i][j] = alive;
                    }
                    else
                        nou_mat[i][j] = dead;
                }
            }

            nou_mat[i][m] = '\0';
        }
        
        push(stack, list);

        for(int i = 0; i < n; i++)
            strcpy(mat[i], nou_mat[i]);
        free_mem_mat(nou_mat, n);
    }

    write(stack, fisier_iesire);

    free_mem_stack(stack);
    free_mem_mat(mat, n);
}