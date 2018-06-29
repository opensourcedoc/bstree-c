#ifndef BSTREE_H
#define BSTREE_H

#ifndef __cplusplus
    #include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bstree_int BSTreeInt;

BSTreeInt * algo_bstree_int_new(void);
bool algo_bstree_int_is_empty(BSTreeInt *self);
bool algo_bstree_int_find(BSTreeInt *self, int value);
int algo_bstree_int_min(BSTreeInt *self);
int algo_bstree_int_max(BSTreeInt *self);
bool algo_bstree_int_insert(BSTreeInt *self, int value);
bool algo_bstree_int_delete(BSTreeInt *self, int value);
void algo_bstree_int_free(void *self);

#ifdef __cplusplus
}
#endif

#endif // BSTREE_H
