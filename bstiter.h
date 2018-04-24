#ifndef BSTITER_H
#define BSTITER_H

#include "bstree.h"

typedef struct bstIter BSTIter;

// Recursive Tree Traversal
void bstree_pre_order(BSTree *tree);
void bstree_in_order(BSTree *tree);
void bstree_post_order(BSTree *tree);

// Pre-order Traversal Iterator.
BSTIter * bstree_pre_order_start(BSTree *tree);
bool bstree_pre_order_next(BSTIter *iter, int *out);
bool bstree_pre_order_end(BSTIter *iter);

// In-order Traversal Iterator.
BSTIter * bstree_in_order_start(BSTree *tree);
bool bstree_in_order_next(BSTIter *iter, int *out);
bool bstree_in_order_end(BSTIter *iter);

// Post-order Traversal Iterator.
BSTIter * bstree_post_order_start(BSTree *tree);
bool bstree_post_order_next(BSTIter *iter, int *out);
bool bstree_post_order_end(BSTIter *iter);

void bstiter_free(void *iter);

#endif  // BSTITER_H