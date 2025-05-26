#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define alive 'x'
#define dead '+'

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

int** alloc_mat(int, int);
char** read(int*, int*, int*, int*, const char*);
void free_mem_mat(char**, int);
int vecinity(coords, coords);
list* alive_cells(char**, int, int);
int nr_alive_cells(list*);
void transform_vector(list*, int, coords**);
void complete_adjacency(int***, int n, const coords*);
void adjacency_mat(char**, int, int, int***, coords**, int*);
void DFS(int**, int*, int*, int*, int, int, int*, int*);
void update_mat(char***, bnrTree*, bnrTree*);
void write_graph(const char*, int, const coords*, const int*);
void free_dfs(int**, int**, int**, coords**);
void apply_hamilton(bnrTree*, bnrTree*, char**, int, int, const char*);
void hamilton(bnrTree*, bnrTree*, int, int, char**, const char*);
void apply_hamilton_node(const bnrTree*,char**, int, int, const char*);
void hamilton_recursiv(bnrTree*, char**, int, int, const char*);