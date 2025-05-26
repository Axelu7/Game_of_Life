#include "header2.h"

int main(int argc, char* argv[])
{
    int T, N, M, K;
    char** mat = read(&T, &N, &M, &K, argv[1]);

    StackNode* stack = NULL;
    /*
    Daca bonusul este folosit in task 2 pentru a readuce la matricea initiala, atunci se va apela GoL pentru a creea stiva si a o parcurge prin functia bonus pentru a recrea matricea initiala.
    GoL(&stack, K, N, M, mat, argv[2]);
    */

    bonus(&stack, mat, N, M, argv[2]);

    return 0;
}