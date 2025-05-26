#include "header4.h"

int** alloc_mat(int n, int m)
{
    int i;
    int** mat;
    mat = malloc(n * sizeof(int*));
    if (mat == NULL)
    {
        printf("Eroare la alocarea dinamica a matricei!\n");
        exit(1);
    }
    for (i = 0; i < n; i++)
    {
        mat[i] = malloc((m + 1) * sizeof(int));
        if (mat[i] == NULL)
        {
            printf("Eroare la alocarea dinamica a liniei %d din matrice!\n", i);
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

void free_mem_mat(char** mat, int n)
{
    for(int i = 0; i < n; i++)
        free(mat[i]);
    
    free(mat);

}

int vecinity(coords x, coords y)
{
    if (x.l == y.l && x.c == y.c)
        return 0;

    else if ((x.l - y.l >= -1 && x.l - y.l <= 1) && (x.c - y.c >= -1 && x.c - y.c <= 1))
        return 1;

    return 0;
}

list* alive_cells(char** mat, int n, int m)
{
    list* cells = NULL;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 'X')
            {
                coords c;
                c.l = i;
                c.c = j;
                addAtEnd_list(&cells, c);
            }
        }
    }
    return cells;
}

int nr_alive_cells(list* l)
{
    int cnt = 0;
    list* aux = l;

    while (aux != NULL)
    {
        cnt++;
        aux = aux->next;
    }
    return cnt;
}

void transform_vector(list* l, int nr, coords** v)
{
    list* aux = l;
    
    for (int i = 0; i < nr; i++)
    {
        *(v[i]) = aux->poz;
        aux = aux->next;
    }
}

void complete_adjacency(int*** adj, int n, const coords* v)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (vecinity(v[i], v[j]) == 1)
            {
                (*adj)[i][j] = 1;
                (*adj)[j][i] = 1;
            }
        }
    }
}

void adjacency_mat(char** mat, int n, int m, int*** adj, coords** v, int* nr)
{
    list* cells = alive_cells(mat, n, m);
    (*nr) = nr_alive_cells(cells);
    *v = malloc((*nr) * sizeof(coords));

    if ((*v) == NULL)
    {
        printf("Eroare la alocarea vectorului!");
        exit(1);
    }

    transform_vector(cells, *nr, v);
    *(adj) = alocare_matrice_int(*nr, *nr);
    complete_adjacency(adj, *nr, *v);
    eliberare_l(&cells);
}

void DFS(int** adj, int* viz, int* drum, int* lungime, int node, int nr, int* max, int* cale_max)
{
    viz[node] = 1;
    drum[*lungime] = node;
    (*lungime)++;

    if ((*lungime) > (*max))
    {
        *max = *lungime;
        for (int i = 0; i < (*lungime); i++)
            cale_max[i] = drum[i];
    }

    for (int i = 0; i < nr; i++)
        if (adj[node][i] != 0 && viz[i] == 0)
            DFS(adj, viz, drum, lungime, i, nr, max, cale_max);

    (*lungime)--;
    viz[node] = 0;
}

void update_mat(char*** mat, bnrTree* root, bnrTree* node)
{
    if (root == NULL || node == NULL)
        return;

    if (root == node)
    {
        modify_mat(*mat, root->elem);
        return;
    }

    update_mat(mat, root->left, node);
    update_mat(mat, root->right, node);
    modify_mat(*mat, root->elem);
}

void write_graph(const char* nume, int max, const coords* v, const int* cel_mai_lung_drum)
{
    FILE* f = fopen(nume, "a");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului!");
        exit(1);
    }

    if (max == -1)
        fprintf(f, "-1\n");

    else
    {
        fprintf(f, "%d\n", max);
        for (int i = 0; i < max; i++)
            fprintf(f, "(%d,%d) ", v[cel_mai_lung_drum[i]].l, v[cel_mai_lung_drum[i]].c);

        fprintf(f, "\n");
    }

    fclose(f);
}

void free_dfs(int** a, int** b, int** c, coords** d)
{
    free(*a);
    free(*b);
    free(*c);
    free(*d);
}

void apply_hamilton(bnrTree* root, bnrTree* node, char** init_mat, int n, int m, const char* nume)
{

    char** current_mat = mat_alloc(n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            current_mat[i][j] = init_mat[i][j];

    update_mat(&current_mat, root, node);

    int** adj, nr;
    coords* v;

    adjacency_mat(current_mat, n, m, &adj, &v, &nr);
    int* viz = malloc(nr * sizeof(int));

    int* drum = malloc(nr * sizeof(int));
    int* cel_mai_lung_drum = malloc(nr * sizeof(int));
    int max = -1;

    for (int i = 0; i < nr; i++)
    {
        for(int k=0;k<nr;k++)
            viz[i]=0;

        int lungime = 0;
        DFS(adj, viz, drum, &lungime, i, nr, &max, cel_mai_lung_drum);
    }

    write_graph(nume, max, v, cel_mai_lung_drum);

    eliberare_matrice_int(&adj, nr);
    eliberare_memorie_matrice(&current_mat,n);
    free_dfs(&viz, &drum, &cel_mai_lung_drum, &v);
}

void hamilton(bnrTree* root, bnrTree* node, int n, int m, char** mat, const char* nume)
{
    if (node == NULL)
    {
        return;
    }
    char** mat_left = mat_alloc(n,m);
    char** mat_right = mat_alloc(n,m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            mat_left[i][j]=mat[i][j];
            mat_right[i][j]=mat[i][j];
        }
    }
    
    apply_hamilton(root, node, mat, n, m, nume);
    hamilton(root, node->left, n, m, mat_left, nume);
    hamilton(root, node->right, n, m, mat_right, nume);
    eliberare_memorie_matrice(&mat_left,n);
    eliberare_memorie_matrice(&mat_right,n);
}

void apply_hamilton_node(const bnrTree* node,char** mat, int n, int m, const char* nume)
{
    if(node==NULL)
        return;

    int** adj, nr;
    coords* v;

    adjacency_mat(mat, n, m, &adj, &v, &nr);

    int* viz = malloc(nr * sizeof(int));
    int* drum = malloc(nr * sizeof(int));
    int* cel_mai_lung_drum = malloc(nr * sizeof(int));
    int max = -1;

    for (int i = 0; i < nr; i++)
    {
        for(int k = 0; k < nr; k++)
            viz[i]=0;

        int lungime = 0;
        DFS(adj, viz, drum, &lungime, i, nr, &max, cel_mai_lung_drum);
    }

    write_graph(nume, max, v, cel_mai_lung_drum);
    eliberare_matrice_int(&adj, nr);
    free_dfs(&viz, &drum, &cel_mai_lung_drum, &v);
}

void hamilton_recursiv(bnrTree* node, char** init_mat, int n, int m, const char* nume)
{
    char** current_mat = mat_alloc(n,m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            current_mat[i][j] = init_mat[i][j];

    modify_mat(current_mat, node->elem);
    aplicare_hamilton_node(node, current_mat, n, m, nume);
    hamiltton_recursiv(node->left, current_mat, n, m, nume);
    hamilton_recursiv(node->right, current_mat, n, m, nume);

    eliberare_memorie_matrice(&current_mat, n);
}