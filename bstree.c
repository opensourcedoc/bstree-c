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

int bstree_min(BSTree *self)
{
    assert(!bstree_is_empty(self));
    
    Node *curr = self->root;
    while (curr->left) {
        curr = curr->left;
    }
    
    return curr->data;
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

static void _bstree_pre_order(Node *node);

void bstree_pre_order(BSTree *self)
{
    assert(self);
    
    _bstree_pre_order(self->root);
    
    printf("\n");
}

static void _bstree_pre_order(Node *node)
{
    if (!node) {
        return;
    }

    printf("%d ", node->data);
    _bstree_pre_order(node->left);
    _bstree_pre_order(node->right);
}

static void _bstree_in_order(Node *node);

void bstree_in_order(BSTree *self)
{
    assert(self);
    
    _bstree_in_order(self->root);
    
    printf("\n");
}

static void _bstree_in_order(Node *node)
{
    if (!node) {
        return;
    }
    
    _bstree_in_order(node->left);
    printf("%d ", node->data);
    _bstree_in_order(node->right);
}

static void _bstree_post_order(Node *node);

void bstree_post_order(BSTree *self)
{
    assert(self);
    
    _bstree_post_order(self->root);
    
    printf("\n");
}

static void _bstree_post_order(Node *node)
{
    if (!node) {
        return;
    }
    
    _bstree_post_order(node->left);
    _bstree_post_order(node->right);
    printf("%d ", node->data);
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