#ifndef BSTITER_H
#define BSTITER_H

#include "bstree.h"

typedef struct bstIter BSTIter;

// Recursive Tree Traversal
void bstree_pre_order(BSTree *tree);
void bstree_in_order(BSTree *tree);
void bstree_post_order(BSTree *tree);

// Recursive Pre-order Traversal Iterator.
BSTIter * bstree_pre_order_start_r(BSTree *tree);
bool bstree_pre_order_next_r(BSTIter *iter, int *out);
bool bstree_pre_order_end_r(BSTIter *iter);

// Recursive In-order Traversal Iterator.
BSTIter * bstree_in_order_start_r(BSTree *tree);
bool bstree_in_order_next_r(BSTIter *iter, int *out);
bool bstree_in_order_end_r(BSTIter *iter);

// Recursive Post-order Traversal Iterator.
BSTIter * bstree_post_order_start_r(BSTree *tree);
bool bstree_post_order_next_r(BSTIter *iter, int *out);
bool bstree_post_order_end_r(BSTIter *iter);

// Non-Recursive Pre-order Traversal Iterator.
BSTIter * bstree_pre_order_start(BSTree *tree);
bool bstree_pre_order_next(BSTIter *iter, int *out);
bool bstree_pre_order_end(BSTIter *iter);

// Non-Recursive In-order Traversal Iterator.
BSTIter * bstree_in_order_start(BSTree *tree);
bool bstree_in_order_next(BSTIter *iter, int *out);
bool bstree_in_order_end(BSTIter *iter);

// Non-Recursive Post-order Traversal Iterator.
BSTIter * bstree_post_order_start(BSTree *tree);
bool bstree_post_order_next(BSTIter *iter, int *out);
bool bstree_post_order_end(BSTIter *iter);

void bstiter_free(void *iter);

#endif  // BSTITER_H