#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"

#define TEST(test) { \
        if (!(test)) { \
            fprintf(stderr, "%s on %d: Failed on %s", __FILE__, __LINE__, #test); \
            exit(EXIT_FAILURE); \
        } \
    }

bool test_tree_is_empty();
bool test_tree_insert();
bool test_tree_pre_order();
bool test_tree_pre_order_iter();

int main()
{
    TEST(test_tree_is_empty());
    TEST(test_tree_insert());
    TEST(test_tree_pre_order());
    TEST(test_tree_pre_order_iter());
    
    return 0;
}

bool test_tree_is_empty()
{
    bool failed = false;

    BSTree *t = bstree_new();
    if (!t) {
        perror("Failed to allocate BSTree t");
        return false;
    }
    
    if (!bstree_is_empty(t)) {
        perror("It should be empty");
        failed = true;
        goto BSTREE_FREE;
    }
    
BSTREE_FREE:
    bstree_free(t);
    
    if (failed) {
        return false;
    }
    
    return true;
}

bool test_tree_insert()
{
    bool failed = false;
    
    BSTree *t = bstree_new();
    if (!t) {
        perror("Failed to allocate BSTree t");
        return false;
    }
    
    if (!bstree_insert(t, 3)) {
        failed = true;
        goto BSTREE_FREE;
    }
    
    if (!bstree_find(t, 3)) {
        perror("It should be true");
        failed = true;
        goto BSTREE_FREE;
    }
    
    if (bstree_find(t, 5)) {
        failed = true;
        goto BSTREE_FREE;
    }
    
    if (!bstree_insert(t, 5)) {
        failed = true;
    }
    
    if (!bstree_find(t, 3)) {
        perror("It should be true");
        failed = true;
        goto BSTREE_FREE;
    }
    
    if (!bstree_find(t, 5)) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    bstree_free(t);
    
    if (failed) {
        return false;
    }
    
    return true;
}

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

    bstree_pre_order(tr);

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