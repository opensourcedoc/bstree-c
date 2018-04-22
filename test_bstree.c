#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "test_manipulation.h"

#define TEST(test) { \
        if (!(test)) { \
            fprintf(stderr, "%s on %d: Failed on %s", __FILE__, __LINE__, #test); \
            exit(EXIT_FAILURE); \
        } \
    }

bool test_tree_pre_order();
bool test_tree_in_order();
bool test_tree_post_order();
bool test_tree_pre_order_iter();

int main()
{
    TEST(test_tree_is_empty());
    TEST(test_tree_insert());
    TEST(test_tree_min());
    TEST(test_tree_max());
    TEST(test_tree_delete_leaf());
    TEST(test_tree_delete_one_child());
    TEST(test_tree_delete_two_childs());
    TEST(test_tree_pre_order());
    TEST(test_tree_in_order());
    TEST(test_tree_post_order());
    TEST(test_tree_pre_order_iter());
    
    return 0;
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