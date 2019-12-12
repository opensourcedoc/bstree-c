#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "algo/bstree.h"
#include "test_manipulation.h"

bool test_tree_is_empty(void)
{
    bool failed = false;

    bstree_int_t *t = algo_bstree_int_new();
    if (!t) {
        perror("Failed to allocate bstree_int_t t");
        return false;
    }

    if (!algo_bstree_int_is_empty(t)) {
        perror("It should be empty");
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    algo_bstree_int_free(t);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_insert(void)
{
    bool failed = false;

    bstree_int_t *t = algo_bstree_int_new();
    if (!t) {
        perror("Failed to allocate bstree_int_t t");
        return false;
    }

    if (!algo_bstree_int_insert(t, 3)) {
        failed = true;
        goto BSTREE_FREE;
    }

    if (!algo_bstree_int_find(t, 3)) {
        perror("It should be true");
        failed = true;
        goto BSTREE_FREE;
    }

    if (algo_bstree_int_find(t, 5)) {
        failed = true;
        goto BSTREE_FREE;
    }

    if (!algo_bstree_int_insert(t, 5)) {
        failed = true;
    }

    if (!algo_bstree_int_find(t, 3)) {
        perror("It should be true");
        failed = true;
        goto BSTREE_FREE;
    }

    if (!algo_bstree_int_find(t, 5)) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    algo_bstree_int_free(t);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_min(void)
{
    bool failed = false;

    bstree_int_t *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (algo_bstree_int_min(tr) != 1) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_max(void)
{
    bool failed = false;

    bstree_int_t *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (algo_bstree_int_max(tr) != 7) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_delete_leaf(void)
{
    bool failed = false;

    bstree_int_t *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (!algo_bstree_int_delete(tr, 3)) {
        failed = true;
        goto BSTREE_FREE;
    }

    int arr[] = {4, 2, 6, 1, 5, 7};

    for (size_t i = 0; i < 6; i++) {
        if (!algo_bstree_int_find(tr, arr[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (algo_bstree_int_find(tr, 3)) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_delete_one_child(void)
{
    bool failed = false;

    bstree_int_t *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5};

    for (size_t i = 0; i < 6; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (!algo_bstree_int_delete(tr, 6)) {
        failed = true;
        goto BSTREE_FREE;
    }

    int arr[] = {4, 2, 1, 3, 5};

    for (size_t i = 0; i < 5; i++) {
        if (!algo_bstree_int_find(tr, arr[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (algo_bstree_int_find(tr, 6)) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_delete_two_childs(void)
{
    bool failed = false;

    bstree_int_t *tr = algo_bstree_int_new();

    int in[] = {4, 2, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 7; i++) {
        if (!algo_bstree_int_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (!algo_bstree_int_delete(tr, 2)) {
        failed = true;
        goto BSTREE_FREE;
    }

    int arr[] = {4, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 6; i++) {
        if (!algo_bstree_int_find(tr, arr[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (algo_bstree_int_find(tr, 2)) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    algo_bstree_int_free(tr);

    if (failed) {
        return false;
    }

    return true;
}
