#include "header2.h"

int main(int argc, char* argv[])
{
    int T, N, M, K;
    char** mat;
    StackNode* stack = NULL;

    //Alocare dinamica a matricii de intrare
    mat = read(&T, &N, &M, &K, argv[1]);

    //Verifica numarul task-ului
    if(T == 2)
        GoL(&stack, K, N, M, mat, argv[2]);

    else
    {
        printf("Numar de task invalid!\n");
        free_mem_mat(mat, N);
        free_mem_stack(&stack);
    }
    
    return 0;
}