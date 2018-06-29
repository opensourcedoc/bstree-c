#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "algo/bstree.h"
#include "algo/bstiter.h"
#include "test_traversal.h"

bool test_tree_pre_order(void)
{
    bool failed = false;

    BSTreeInt *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    printf("pre-order: ");
    algo_bstree_int_pre_order(tr);

BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_in_order(void)
{
    bool failed = false;

    BSTreeInt *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    printf("in-order: ");
    algo_bstree_int_in_order(tr);

BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_post_order(void)
{
    bool failed = false;

    BSTreeInt *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    printf("post-order: ");
    algo_bstree_int_post_order(tr);

BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_pre_order_iter_r(void)
{
    bool failed = false;

    BSTreeInt *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    BSTIterInt *iter = algo_bstree_int_pre_order_start_r(tr);
    int arr[] = {4, 2, 1, 3, 6, 5, 7};
    size_t i = 0;
    while (!algo_bstree_int_pre_order_end_r(iter)) {
        int n = 0;
        if (!algo_bstree_int_pre_order_next_r(iter, &n)) {
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
    algo_bstiter_int_free(iter);
BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_in_order_iter_r(void)
{
    bool failed = false;

    BSTreeInt *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    BSTIterInt *iter = algo_bstree_int_in_order_start_r(tr);
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t i = 0;
    while (!algo_bstree_int_in_order_end_r(iter)) {
        int n = 0;
        if (!algo_bstree_int_in_order_next_r(iter, &n)) {
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
    algo_bstiter_int_free(iter);
BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_post_order_iter_r(void)
{
    bool failed = false;

    BSTreeInt *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    BSTIterInt *iter = algo_bstree_int_post_order_start_r(tr);
    int arr[] = {1, 3, 2, 5, 7, 6, 4};
    size_t i = 0;
    while (!algo_bstree_int_post_order_end_r(iter)) {
        int n = 0;
        if (!algo_bstree_int_post_order_next_r(iter, &n)) {
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
    algo_bstiter_int_free(iter);
BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_pre_order_iter(void)
{
    bool failed = false;

    BSTreeInt *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    BSTIterInt *iter = algo_bstree_int_pre_order_start(tr);
    int arr[] = {4, 2, 1, 3, 6, 5, 7};
    size_t i = 0;
    while (!algo_bstree_int_pre_order_end(iter)) {
        int n = 0;
        if (!algo_bstree_int_pre_order_next(iter, &n)) {
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
    algo_bstiter_int_free(iter);
BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_in_order_iter(void)
{
    bool failed = false;

    BSTreeInt *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    BSTIterInt *iter = algo_bstree_int_in_order_start(tr);
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t i = 0;
    while (!algo_bstree_int_in_order_end(iter)) {
        int n = 0;
        if (!algo_bstree_int_in_order_next(iter, &n)) {
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
    algo_bstiter_int_free(iter);
BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_post_order_iter(void)
{
    bool failed = false;

    BSTreeInt *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    BSTIterInt *iter = algo_bstree_int_post_order_start(tr);
    int arr[] = {1, 3, 2, 5, 7, 6, 4};
    size_t i = 0;
    while (!algo_bstree_int_post_order_end(iter)) {
        int n = 0;
        if (!algo_bstree_int_post_order_next(iter, &n)) {
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
    algo_bstiter_int_free(iter);
BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}
