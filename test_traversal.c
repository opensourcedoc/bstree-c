#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "bstree.h"
#include "test_traversal.h"

bool test_tree_pre_order()
{
    bool failed = false;
    
    BSTree *tr = bstree_new();
    
    int in[] = {4, 2, 6, 1, 3, 5, 7};
    
    for (size_t i = 0; i < 7; i++) {
        if (!bstree_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    printf("pre-order: ");
    bstree_pre_order(tr);

BSTREE_FREE:
    bstree_free(tr);
    
    if (failed) {
        return false;
    }
    
    return true;
}

bool test_tree_in_order()
{
    bool failed = false;
    
    BSTree *tr = bstree_new();
    
    int in[] = {4, 2, 6, 1, 3, 5, 7};
    
    for (size_t i = 0; i < 7; i++) {
        if (!bstree_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    printf("in-order: ");
    bstree_in_order(tr);

BSTREE_FREE:
    bstree_free(tr);
    
    if (failed) {
        return false;
    }
    
    return true;
}

bool test_tree_post_order()
{
    bool failed = false;
    
    BSTree *tr = bstree_new();
    
    int in[] = {4, 2, 6, 1, 3, 5, 7};
    
    for (size_t i = 0; i < 7; i++) {
        if (!bstree_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    printf("post-order: ");
    bstree_post_order(tr);

BSTREE_FREE:
    bstree_free(tr);
    
    if (failed) {
        return false;
    }
    
    return true;
}

bool test_tree_pre_order_iter()
{
    bool failed = false;

    BSTree *tr = bstree_new();
    
    int in[] = {4, 2, 6, 1, 3, 5, 7};
    
    for (size_t i = 0; i < 7; i++) {
        if (!bstree_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }
    
    BSTIter *iter = bstree_pre_order_start(tr);
    int arr[] = {4, 2, 1, 3, 6, 5, 7};
    size_t i = 0;
    while (!bstree_pre_order_end(iter)) {
        int n = 0;
        if (!bstree_pre_order_next(iter, &n)) {
            failed = true;
            goto BSTREE_ITER_TREE;
        }
        
        if (n != arr[i]) {
            failed = true;
            goto BSTREE_ITER_TREE;
        }
        
        i++;
    }
    
BSTREE_ITER_TREE:
    bstiter_free(iter);
BSTREE_FREE:
    bstree_free(tr);
    
    if (failed) {
        return false;
    }
    
    return true;
}

bool test_tree_in_order_iter()
{
    bool failed = false;

    BSTree *tr = bstree_new();
    
    int in[] = {4, 2, 6, 1, 3, 5, 7};
    
    for (size_t i = 0; i < 7; i++) {
        if (!bstree_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }
    
    BSTIter *iter = bstree_in_order_start(tr);
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t i = 0;
    while (!bstree_in_order_end(iter)) {
        int n = 0;
        if (!bstree_in_order_next(iter, &n)) {
            failed = true;
            goto BSTREE_ITER_TREE;
        }
        
        if (n != arr[i]) {
            failed = true;
            goto BSTREE_ITER_TREE;
        }
        
        i++;
    }
    
BSTREE_ITER_TREE:
    bstiter_free(iter);
BSTREE_FREE:
    bstree_free(tr);
    
    if (failed) {
        return false;
    }
    
    return true;
}