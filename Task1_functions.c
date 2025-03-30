#include "Task1.h"

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

void free_mem(char** mat, int n)
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

void write(int n, char** mat, const char* fisier_iesire)
{
    FILE* f = fopen(fisier_iesire, "at");
    if(f == NULL)
    {
        printf("Eroare la deschiderea fisierului de iesire!\n");
        exit(1);
    }

    for(int i = 0; i < n; i++)
        fprintf(f, "%s\n", mat[i]);

    fprintf(f, "\n");

    fclose(f);
}

void GoL(int k, int n, int m, char** mat, const char* fisier_iesire)
{
    FILE* f = fopen(fisier_iesire, "wt");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului de iesire!\n");
        exit(1);
    }

    write(n, mat, fisier_iesire);

    char** nou_mat = alloc_mat(n, m);
    for(int gen = 0; gen < k; gen++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                int nr_vecini = vecini(mat, n, m, i, j);

                if(mat[i][j] == alive)
                {
                    if(nr_vecini < 2 || nr_vecini > 3)
                        nou_mat[i][j] = dead;
                    else
                        nou_mat[i][j] = alive;
                }
                else
                {
                    if(nr_vecini == 3)
                        nou_mat[i][j] = alive;
                    else
                        nou_mat[i][j] = dead;
                }
            }
            nou_mat[i][m] = '\0';
        }

        write(n, nou_mat, fisier_iesire);

        for(int i = 0; i < n; i++)
            strcpy(mat[i], nou_mat[i]);
    }

    free_mem(nou_mat, n);
}