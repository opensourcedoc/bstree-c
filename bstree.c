#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "bstree_internal.h"
#include "bstnode.h"

int node_data(Node *node)
{
    assert(node);

    return node->data;
}

BSTree * bstree_new()
{
    BSTree *t = malloc(sizeof(BSTree));
    if (!t) {
        return t;
    }

    t->root = NULL;

    return t;
}

bool bstree_is_empty(BSTree* self)
{
    assert(self);

    return self->root == NULL;
}

static bool _bstree_find(Node *node, int value);

bool bstree_find(BSTree *self, int value)
{
    assert(self);

    return _bstree_find(self->root, value);
}

bool _bstree_find(Node *node, int value)
{
    if (!node) {
        return false;
    }

    if (node->data == value) {
        return true;
    } else if (node->data > value) {
        return _bstree_find(node->left, value);
    } else {
        return _bstree_find(node->right, value);
    }
}

static int _bstree_min(Node *node);

int bstree_min(BSTree *self)
{
    assert(!bstree_is_empty(self));

    return _bstree_min(self->root);
}

static int _bstree_min(Node *node)
{
    assert(node);

    while (node->left) {
        node = node->left;
    }

    return node->data;
}

int bstree_max(BSTree *self)
{
    assert(!bstree_is_empty(self));

    Node *curr = self->root;
    while (curr->right) {
        curr = curr->right;
    }

    return curr->data;
}

static bool _bstree_insert(Node **node, int value);

bool bstree_insert(BSTree *self, int value)
{
    assert(self);

    return _bstree_insert(&(self->root), value);
}

static bool _bstree_insert(Node **node, int value)
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
        return _bstree_insert(&((*node)->left), value);
    } else {
        return _bstree_insert(&((*node)->right), value);
    }
}

static bool _bstree_delete(Node **node, int value);

bool bstree_delete(BSTree *self, int value)
{
    if (bstree_is_empty(self)) {
        return false;
    }

    return _bstree_delete(&(self->root), value);
}



static bool _bstree_delete(Node **node, int value)
{
    if (!(*node)) {
        return false;
    }

    if ((*node)->data > value) {
        return _bstree_delete(&((*node)->left), value);
    }

    if ((*node)->data < value) {
        return _bstree_delete(&((*node)->right), value);
    }

    if (!((*node)->left)) {
        Node *temp = (*node)->right;
        free(*node);
        *node = temp;
    } else if (!((*node)->right)) {
        Node *temp = (*node)->left;
        free(*node);
        *node = temp;
    } else {
        int min = _bstree_min((*node)->right);
        (*node)->data = min;
        if (!_bstree_delete(&((*node)->right), min)) {
            perror("Unable to delete subsequent node");
            return false;
        }
    }

    return true;
}

static void _bstree_free(void *node);

void bstree_free(void *self)
{
    if (!self) {
        return;
    }

    _bstree_free(((BSTree *) self)->root);
    free(self);
}

static void _bstree_free(void *node)
{
    if (!node) {
        return;
    }
    _bstree_free(((Node *) node)->left);
    _bstree_free(((Node *) node)->right);
    free(node);
}
