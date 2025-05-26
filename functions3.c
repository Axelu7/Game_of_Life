#include "header3.h"

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

char** read(int* t, int* n, int* m, int* k, const char* fisier_intrare)
{
    FILE* f = fopen(fisier_intrare, "rt");
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

void addAtEnd_list(list** head, coords v)
{
    list* aux = *head;
    list* new_node = malloc(sizeof(list));
    if (new_node == NULL)
    {
        printf("Eroare la alocarea dinamica a listei!\n");
        return;
    }

    new_node->poz.l = v.l;
    new_node->poz.c = v.c;
    new_node->next = NULL;

    if (*head == NULL)
        *head = new_node;

    else
    {
        while (aux->next != NULL)
            aux = aux->next;

        aux->next = new_node;
        new_node->next = NULL;
    }
}

void free_mem_mat(char** mat, int n)
{
    for(int i = 0; i < n; i++)
        free(mat[i]);
    
    free(mat);

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

void B_rule(char** mat, int n, int m, bnrTree** root)
{
    char** temp = alloc_mat(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int nr_vecini = vecini(mat, n, m, i, j);

            if (nr_vecini == 2 && mat[i][j] == '+')
                temp[i][j] = 'X';

            else
                temp[i][j] = mat[i][j];
        }

        temp[i][m] = '\0';
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] != temp[i][j])
            {
                coords cord;
                cord.l = i;
                cord.c = j;
                addAtEnd_list(&((*root)->elem), cord);
            }
        }
    }
    
    free_mem_mat(temp, n);
}

void GoL_rule(char** mat, int n, int m, bnrTree** root)
{
    char** aux = alloc_mat(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int nr_vecini = vecini(mat, n, m, i, j);
            if (mat[i][j] == 'X')
            {
                if (nr_vecini < 2 || nr_vecini > 3)
                    aux[i][j] = '+';

                else
                    aux[i][j] = 'X';
            }

            else
            {
                if (nr_vecini == 3)
                    aux[i][j] = 'X';

                else
                    aux[i][j] = '+';
            }
        }

        aux[i][m] = '\0';
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] != aux[i][j])
            {
                coords cord;
                cord.l = i;
                cord.c = j;
                addAtEnd_list(&((*root)->elem), cord);
            }
        }
    }

    free_mem_mat(aux, n);
}

void free_mem_list(list** head)
{
    list* current = *head;
    while (current != NULL)
    {
        list* next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

void populate_root(bnrTree** root, char** mat, int n, int m)
{
    *root = malloc(sizeof(bnrTree));
    (*root)->elem = NULL;
    (*root)->left = NULL;
    (*root)->right = NULL;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 'X')
            {
                coords cord;
                cord.l = i;
                cord.c = j;
                addAtEnd_list(&((*root)->elem), cord);
            }
        }
    }
}

void free_mem_tree(bnrTree** root)
{
    if (*root == NULL)
        return;

    free_mem_tree(&(*root)->left);
    free_mem_tree(&(*root)->right);
    free_mem_list(&(*root)->elem);
    free(*root);

    *root = NULL;
}

void modify_mat(char** mat, list* l)
{
    while (l != NULL)
    {
        if (mat[l->poz.l][l->poz.c] == 'X')
        {
            mat[l->poz.l][l->poz.c] = '+';
        }
        else
        {
            mat[l->poz.l][l->poz.c] = 'X';
        }
        l = l->next;
    }
}

void new_rules(bnrTree** root, char** mat, int n, int m, int k)
{
    if (k == 0)
        return;

    char** mat_left = alloc_mat(n, m);
    char** mat_right = alloc_mat(n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mat_left[i][j] = mat[i][j];
            mat_right[i][j] = mat[i][j];
        }

        mat_left[i][m] = '\0';
        mat_right[i][m] = '\0';
    }

    (*root)->left = (bnrTree *)malloc(sizeof(bnrTree));
    (*root)->right = (bnrTree *)malloc(sizeof(bnrTree));

    (*root)->left->elem = NULL;
    (*root)->left->left = NULL;
    (*root)->left->right = NULL;

    (*root)->right->elem = NULL;
    (*root)->right->left = NULL;
    (*root)->right->right = NULL;

    B_rule(mat_left, n, m, &(*root)->left);
    modify_mat(mat_left, (*root)->left->elem);

    GoL_rule(mat_right, n, m, &(*root)->right);
    modify_mat(mat_right, (*root)->right->elem);

    new_rules(&(*root)->left, mat_left, n, m, k - 1);
    new_rules(&(*root)->right, mat_right, n, m, k - 1);

    free_mem_mat(mat_left, n);
    free_mem_mat(mat_right, n);
}

void print_tree(bnrTree *root, FILE *f, char **mat, int n, int m)
{
    if (root == NULL)
        return;

    char** aux = alloc_mat(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            aux[i][j] = mat[i][j];
        }
    }
    list *l = root->elem;
    while (l != NULL)
    {

        if (aux[l->poz.l][l->poz.c] == 'X')
            aux[l->poz.l][l->poz.c] = '+';

        else if (aux[l->poz.l][l->poz.c] == '+')
            aux[l->poz.l][l->poz.c] = 'X';

        l = l->next;
    }

    for (int i = 0; i < n; i++)
        fprintf(f, "%s\n", aux[i]);

    fprintf(f, "\n");

    print_tree(root->left, f, aux, n, m);
    print_tree(root->right, f, aux, n, m);
    free_mem_mat(aux, n);
}

void print_root(bnrTree* root, const char* fisier_iesire, char **mat, int n, int m)
{
    FILE *f = fopen(fisier_iesire, "wt");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului de iesire!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
        fprintf(f, "%s\n", mat[i]);

    fprintf(f, "\n");

    if (root != NULL)
    {
        print_tree(root->left, f, mat, n, m);
        print_tree(root->right, f, mat, n, m);
    }

    fclose(f);
}