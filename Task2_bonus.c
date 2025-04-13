#include "header2.h"

void bonus(StackNode** stack, char** mat, int n, int m, const char* fisier_iesire)
{
    //Daca primeste stack-ul inversat (cum ramane cel din Task 2), il inverseaza la loc pentru a putea parcurge de la generatia K
    reverse_stack(stack);

    StackNode* current = *stack;
    while(current != NULL)
    {
        ListNode* list = current->list;
        while(list != NULL)
        {
            if(mat[list->l][list->c] == alive)
                mat[list->l][list->c] = dead;
            else
                mat[list->l][list->c] = alive;

            list = list->next;
            
        }
        current = current->next;
    }

    FILE *f = fopen(fisier_iesire, "wt");
    if(f == NULL)
    {
        printf("Eroare la deschiderea fisierului de iesire!\n");
        exit(1);
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(mat[i][j] == alive)
                fprintf(f, "%c", alive);
            else
                fprintf(f, "%c", dead);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    free_mem_mat(mat, n);
    free_mem_stack(stack);
}