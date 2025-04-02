#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define dead '+'
#define alive 'X'

struct N
{
    int l;
    int c;
    struct N* next;
};
typedef struct N Node;

char** alloc_mat(int, int);
char** read(int*, int*, int*, int*, const char*);
void free_mem(char**, int);
void push(Node**, int, int);
int vecini(char**, int, int, int, int);
void write(Node**, int, const char*);
void GoL(Node**, int, int, int, char**, const char*);