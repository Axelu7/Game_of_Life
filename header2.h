#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define dead '+'
#define alive 'X'

struct ListN
{
    int l;
    int c;
    struct ListN* next;
};
typedef struct ListN ListNode;

struct StackN
{
    ListNode* list;
    struct StackN* next;
};
typedef struct StackN StackNode;

char** alloc_mat(int, int);
char** read(int*, int*, int*, int*, const char*);
void insert_sort(ListNode**, int, int);
void push(StackNode**, ListNode*);
void reverse_stack(StackNode**);
void write(StackNode**, const char*);
void free_mem_mat(char**, int);
void free_mem_list(ListNode*);
void free_mem_stack(StackNode**);
int vecini(char**, int, int, int, int);
void GoL(StackNode**, int, int, int, char**, const char*);