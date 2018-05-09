#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "algo/bstree.h"
#include "bstree_internal.h"
#include "bstnode.h"

int node_data(NodeInt *node)
{
    assert(node);

    return node->data;
}

BSTreeInt * algo_bstree_int_new(void)
{
    BSTreeInt *t = malloc(sizeof(BSTreeInt));
    if (!t) {
        return t;
    }

    t->root = NULL;

    return t;
}

bool algo_bstree_int_is_empty(BSTreeInt* self)
{
    assert(self);

    return self->root == NULL;
}

static bool _algo_bstree_int_find(NodeInt *node, int value);

bool algo_bstree_int_find(BSTreeInt *self, int value)
{
    assert(self);

    return _algo_bstree_int_find(self->root, value);
}

bool _algo_bstree_int_find(NodeInt *node, int value)
{
    if (!node) {
        return false;
    }

    if (node->data == value) {
        return true;
    } else if (node->data > value) {
        return _algo_bstree_int_find(node->left, value);
    } else {
        return _algo_bstree_int_find(node->right, value);
    }
}

static int _algo_bstree_int_min(NodeInt *node);

int algo_bstree_int_min(BSTreeInt *self)
{
    assert(!algo_bstree_int_is_empty(self));

    return _algo_bstree_int_min(self->root);
}

static int _algo_bstree_int_min(NodeInt *node)
{
    assert(node);

    while (node->left) {
        node = node->left;
    }

    return node->data;
}

int algo_bstree_int_max(BSTreeInt *self)
{
    assert(!algo_bstree_int_is_empty(self));

    NodeInt *curr = self->root;
    while (curr->right) {
        curr = curr->right;
    }

    return curr->data;
}

static bool _algo_bstree_int_insert(NodeInt **node, int value);

bool algo_bstree_int_insert(BSTreeInt *self, int value)
{
    assert(self);

    return _algo_bstree_int_insert(&(self->root), value);
}

static bool _algo_bstree_int_insert(NodeInt **node, int value)
{
    if (!(*node)) {
        *node = node_new(value);
        if (!(*node)) {
            perror("Failed to allocate node");
            return false;
        }

        return true;
    }

    if ((*node)->data > value) {
        return _algo_bstree_int_insert(&((*node)->left), value);
    } else {
        return _algo_bstree_int_insert(&((*node)->right), value);
    }
}

static bool _algo_bstree_int_delete(NodeInt **node, int value);

bool algo_bstree_int_delete(BSTreeInt *self, int value)
{
    if (algo_bstree_int_is_empty(self)) {
        return false;
    }

    return _algo_bstree_int_delete(&(self->root), value);
}



static bool _algo_bstree_int_delete(NodeInt **node, int value)
{
    if (!(*node)) {
        return false;
    }

    if ((*node)->data > value) {
        return _algo_bstree_int_delete(&((*node)->left), value);
    }

    if ((*node)->data < value) {
        return _algo_bstree_int_delete(&((*node)->right), value);
    }

    if (!((*node)->left)) {
        NodeInt *temp = (*node)->right;
        free(*node);
        *node = temp;
    } else if (!((*node)->right)) {
        NodeInt *temp = (*node)->left;
        free(*node);
        *node = temp;
    } else {
        int min = _algo_bstree_int_min((*node)->right);
        (*node)->data = min;
        if (!_algo_bstree_int_delete(&((*node)->right), min)) {
            perror("Unable to delete subsequent node");
            return false;
        }
    }

    return true;
}

static void _algo_bstree_int_free(void *node);

void algo_bstree_int_free(void *self)
{
    if (!self) {
        return;
    }

    _algo_bstree_int_free(((BSTreeInt *) self)->root);
    free(self);
}

static void _algo_bstree_int_free(void *node)
{
    if (!node) {
        return;
    }
    _algo_bstree_int_free(((NodeInt *) node)->left);
    _algo_bstree_int_free(((NodeInt *) node)->right);
    free(node);
}
