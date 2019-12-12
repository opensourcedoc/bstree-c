#ifndef ALGO_BSTREE_H
#define ALGO_BSTREE_H

#ifndef __cplusplus
    #include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bstree_int_t bstree_int_t;

bstree_int_t * algo_bstree_int_new(void);
bool algo_bstree_int_is_empty(bstree_int_t *self);
bool algo_bstree_int_find(bstree_int_t *self, int value);
int algo_bstree_int_min(bstree_int_t *self);
int algo_bstree_int_max(bstree_int_t *self);
bool algo_bstree_int_insert(bstree_int_t *self, int value);
bool algo_bstree_int_delete(bstree_int_t *self, int value);
void algo_bstree_int_free(void *self);

#ifdef __cplusplus
}
#endif

#endif  /* ALGO_BSTREE_H */
