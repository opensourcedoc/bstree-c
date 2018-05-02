#ifndef BSTREE_H
#define BSTREE_H

#include <stdbool.h>

typedef struct bstree_int BSTreeInt;

#include "bstiter.h"

BSTreeInt * algo_bstree_int_new();
bool algo_bstree_int_is_empty(BSTreeInt *self);
bool algo_bstree_int_find(BSTreeInt *self, int value);
int algo_bstree_int_min(BSTreeInt *self);
int algo_bstree_int_max(BSTreeInt *self);
bool algo_bstree_int_insert(BSTreeInt *self, int value);
bool algo_bstree_int_delete(BSTreeInt *self, int value);
void algo_bstree_int_free(void *self);

#endif // BSTREE_H
