#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "bstree.h"
#include "test_manipulation.h"

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

bool test_tree_min()
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

    if (bstree_min(tr) != 1) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    bstree_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_max()
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

    if (bstree_max(tr) != 7) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    bstree_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_delete_leaf()
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

    if (!bstree_delete(tr, 3)) {
        failed = true;
        goto BSTREE_FREE;
    }

    int arr[] = {4, 2, 6, 1, 5, 7};

    for (size_t i = 0; i < 6; i++) {
        if (!bstree_find(tr, arr[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (bstree_find(tr, 3)) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    bstree_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_delete_one_child()
{
    bool failed = false;

    BSTree *tr = bstree_new();

    int in[] = {4, 2, 6, 1, 3, 5};

    for (size_t i = 0; i < 6; i++) {
        if (!bstree_insert(tr, in[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (!bstree_delete(tr, 6)) {
        failed = true;
        goto BSTREE_FREE;
    }

    int arr[] = {4, 2, 1, 3, 5};

    for (size_t i = 0; i < 5; i++) {
        if (!bstree_find(tr, arr[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (bstree_find(tr, 6)) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    bstree_free(tr);

    if (failed) {
        return false;
    }

    return true;
}

bool test_tree_delete_two_childs()
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

    if (!bstree_delete(tr, 2)) {
        failed = true;
        goto BSTREE_FREE;
    }

    int arr[] = {4, 6, 1, 3, 5, 7};

    for (size_t i = 0; i < 6; i++) {
        if (!bstree_find(tr, arr[i])) {
            failed = true;
            goto BSTREE_FREE;
        }
    }

    if (bstree_find(tr, 2)) {
        failed = true;
        goto BSTREE_FREE;
    }

BSTREE_FREE:
    bstree_free(tr);

    if (failed) {
        return false;
    }

    return true;
}
