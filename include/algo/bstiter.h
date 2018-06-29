#ifndef BSTITER_H
#define BSTITER_H

#include "bstree.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bstiter_int BSTIterInt;

// Recursive Tree Traversal
void algo_bstree_int_pre_order(BSTreeInt *tree);
void algo_bstree_int_in_order(BSTreeInt *tree);
void algo_bstree_int_post_order(BSTreeInt *tree);

// Recursive Pre-order Traversal Iterator.
BSTIterInt * algo_bstree_int_pre_order_start_r(BSTreeInt *tree);
bool algo_bstree_int_pre_order_next_r(BSTIterInt *iter, int *out);
bool algo_bstree_int_pre_order_end_r(BSTIterInt *iter);

// Recursive In-order Traversal Iterator.
BSTIterInt * algo_bstree_int_in_order_start_r(BSTreeInt *tree);
bool algo_bstree_int_in_order_next_r(BSTIterInt *iter, int *out);
bool algo_bstree_int_in_order_end_r(BSTIterInt *iter);

// Recursive Post-order Traversal Iterator.
BSTIterInt * algo_bstree_int_post_order_start_r(BSTreeInt *tree);
bool algo_bstree_int_post_order_next_r(BSTIterInt *iter, int *out);
bool algo_bstree_int_post_order_end_r(BSTIterInt *iter);

// Non-Recursive Pre-order Traversal Iterator.
BSTIterInt * algo_bstree_int_pre_order_start(BSTreeInt *tree);
bool algo_bstree_int_pre_order_next(BSTIterInt *iter, int *out);
bool algo_bstree_int_pre_order_end(BSTIterInt *iter);

// Non-Recursive In-order Traversal Iterator.
BSTIterInt * algo_bstree_int_in_order_start(BSTreeInt *tree);
bool algo_bstree_int_in_order_next(BSTIterInt *iter, int *out);
bool algo_bstree_int_in_order_end(BSTIterInt *iter);

// Non-Recursive Post-order Traversal Iterator.
BSTIterInt * algo_bstree_int_post_order_start(BSTreeInt *tree);
bool algo_bstree_int_post_order_next(BSTIterInt *iter, int *out);
bool algo_bstree_int_post_order_end(BSTIterInt *iter);

void algo_bstiter_int_free(void *iter);

#ifdef __cplusplus
}
#endif

#endif  // BSTITER_H
