#ifndef BSTITER_H
#define BSTITER_H

#include "bstree.h"

typedef struct bstIter BSTIter;

BSTIter * bstree_pre_order_start(BSTree *self);
bool bstree_pre_order_next(BSTIter *iter, int *out);
bool bstree_pre_order_end(BSTIter *iter);
void bstiter_free(void *iter);

#endif  // BSTITER_H