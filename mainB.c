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
   ListNode* list1 = NULL;
   insert_sort(&list1, 3, 3);
   insert_sort(&list1, 2, 3);
   insert_sort(&list1, 1, 1);
   push(&stack, list1);

   ListNode* list2 = NULL;
    insert_sort(&list2, 3, 3);
    insert_sort(&list2, 2, 2);
    insert_sort(&list2, 1, 2);
    insert_sort(&list2, 2, 2);
    push(&stack, list2);

    bonus(&stack, mat, N, M, argv[2]);

    return 0;
}
