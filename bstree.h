#ifndef BSTREE_H
#define BSTREE_H

#include <stdbool.h>

typedef struct bstree BSTree;

#include "bstiter.h"

BSTree * algo_bstree_int_new();
bool algo_bstree_int_is_empty(BSTree *self);
bool algo_bstree_int_find(BSTree *self, int value);
int algo_bstree_int_min(BSTree *self);
int algo_bstree_int_max(BSTree *self);
bool algo_bstree_int_insert(BSTree *self, int value);
bool algo_bstree_int_delete(BSTree *self, int value);
void algo_bstree_int_free(void *self);

#endif // BSTREE_H
