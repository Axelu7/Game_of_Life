#include "header3.h"

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

    bnrTree *root = malloc(sizeof(bnrTree));
    if (!root)
    {
        printf("Eroare la alocarea radacinii!\n");
        free_mem_mat(mat, N);
        return 1;
    }

    root->elem = NULL;
    root->left = NULL;
    root->right = NULL;

    populate_root(&root, mat, N, M);
    new_rules(&root, mat, N, M, K);
    print_root(root, argv[2], mat, N, M);

    free_mem_mat(mat, N);
    free_mem_tree(&root);

    return 0;
}
