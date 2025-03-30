#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define dead '+'
#define alive 'X'

char** alloc_mat(int, int);
char** read(int*, int*, int*, int*, const char*);
void free_mem(char**, int);
int vecini(char**, int, int, int, int);
void write(int, char**, const char*);
void GoL(int, int, int, char**, const char*);