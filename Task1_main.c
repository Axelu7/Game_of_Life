#include "Task1.h"

int main(int argc, char* argv[])
{
    int T, N, M, K;
    char** mat;
    
    //Alocare dinamica a matricii de intrare
    mat = read(&T, &N, &M, &K, argv[1]);
    
    //Verifica numarul task-ului
    if(T == 1)
        GoL(K, N, M, mat, argv[2]);

    //Goleste memoria alocata dinamic din matricea de intrare
    free_mem(mat, N);
    return 0;
}