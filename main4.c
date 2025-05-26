#include "header4.h"

int main(int argc, char *argv[])
{
    

    FILE* f = fopen(argv[1], "rt");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului de intrare!\n");
        exit(1);
    }

    int T, N, M, K;
    char** mat;
    mat = read(&T, &N, &M, &K, argv[1]);

    list* initial_alive_cells = alive_cells(mat, N, M);
    bnrTree* root = create_node(initial_alive_cells);

    build_generation_tree(root, mat, N, M, 0, K);

    hamilton_recursiv(root, mat, N, M, argv[2]);

    eliberare_memorie_matrice(&mat, N);
    free_tree(root);

    return 0;
}