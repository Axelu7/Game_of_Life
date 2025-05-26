#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dead '+'
#define alive 'X'

struct coordinates
{
    int l, c;

};
typedef struct coordinates coords;


struct l
{
    coords poz;
    struct l* next;

};
typedef struct l list;

struct treeNode
{
    list* elem;
    struct treeNode* left;
    struct treeNode* right;

};
typedef struct treeNode bnrTree;

char** alloc_mat(int, int);
char** read(int*, int*, int*, int*, const char*);
void addAtEnd_list(list**, coords);
void free_mem_mat(char**, int);
int vecini(char**, int, int, int, int);
void B_rule(char**, int, int, bnrTree**);
void GoL_rule(char**, int, int, bnrTree**);
void free_mem_list(list**);
void populate_root(bnrTree**, char**, int, int);
void free_mem_tree(bnrTree**);
void modify_mat(char**, list*);
void new_rules(bnrTree**, char**, int, int, int);
void print_tree(bnrTree*, FILE*, char**, int, int);
void print_root(bnrTree*, const char*, char**, int, int);