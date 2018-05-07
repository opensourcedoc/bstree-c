#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "algo/bstree.h"
#include "bstree_internal.h"
#include "bstnode.h"
#include "algo/bstiter.h"

typedef struct snode SNodeInt;

struct snode {
    NodeInt *data;
    SNodeInt *next;
    SNodeInt *prev;
};

// BSTIterInt is a deque.
struct bstiter_int {
    SNodeInt *head;
    SNodeInt *tail;
};

static SNodeInt * snode_new(NodeInt *value);
static BSTIterInt * bstiter_new();
static bool bstiter_is_empty(BSTIterInt *self);
static SNodeInt * bstiter_peek_front(BSTIterInt* self);
static SNodeInt * bstiter_peek_rear(BSTIterInt *self);
static bool bstiter_unshift(BSTIterInt *self, NodeInt *data);
static NodeInt * bstiter_shift(BSTIterInt *self);
static bool bstiter_push(BSTIterInt *self, NodeInt *data);
static NodeInt * bstiter_pop(BSTIterInt *self);

static void _algo_bstree_int_pre_order(NodeInt *node);

void algo_bstree_int_pre_order(BSTreeInt *self)
{
    assert(self);

    _algo_bstree_int_pre_order(self->root);

    printf("\n");
}

static void _algo_bstree_int_pre_order(NodeInt *node)
{
    if (!node) {
        return;
    }

    printf("%d ", node->data);
    _algo_bstree_int_pre_order(node->left);
    _algo_bstree_int_pre_order(node->right);
}

static void _algo_bstree_int_in_order(NodeInt *node);

void algo_bstree_int_in_order(BSTreeInt *self)
{
    assert(self);

    _algo_bstree_int_in_order(self->root);

    printf("\n");
}

static void _algo_bstree_int_in_order(NodeInt *node)
{
    if (!node) {
        return;
    }

    _algo_bstree_int_in_order(node->left);
    printf("%d ", node->data);
    _algo_bstree_int_in_order(node->right);
}

static void _algo_bstree_int_post_order(NodeInt *node);

void algo_bstree_int_post_order(BSTreeInt *self)
{
    assert(self);

    _algo_bstree_int_post_order(self->root);

    printf("\n");
}

static void _algo_bstree_int_post_order(NodeInt *node)
{
    if (!node) {
        return;
    }

    _algo_bstree_int_post_order(node->left);
    _algo_bstree_int_post_order(node->right);
    printf("%d ", node->data);
}

static void _algo_bstree_int_pre_order_iter(BSTIterInt *iter, NodeInt *node);

BSTIterInt * algo_bstree_int_pre_order_start_r(BSTreeInt *tree)
{
    assert(tree);

    BSTIterInt *iter = bstiter_new();
    if (!iter) {
        return iter;
    }

    _algo_bstree_int_pre_order_iter(iter, tree->root);

    return iter;
}

static void _algo_bstree_int_pre_order_iter(BSTIterInt *iter, NodeInt *node)
{
    if (!node) {
        return;
    }

    bstiter_push(iter, node);
    _algo_bstree_int_pre_order_iter(iter, node->left);
    _algo_bstree_int_pre_order_iter(iter, node->right);
}

bool algo_bstree_int_pre_order_next_r(BSTIterInt *iter, int *out)
{
    NodeInt *node = bstiter_shift(iter);
    if (!node) {
        return false;
    }

    *out = node->data;

    return true;
}

bool algo_bstree_int_pre_order_end_r(BSTIterInt *iter)
{
    return bstiter_is_empty(iter);
}

static void _algo_bstree_int_in_order_iter(BSTIterInt *iter, NodeInt *node);

BSTIterInt * algo_bstree_int_in_order_start_r(BSTreeInt *tree)
{
    assert(tree);

    BSTIterInt *iter = bstiter_new();
    if (!iter) {
        return iter;
    }

    _algo_bstree_int_in_order_iter(iter, tree->root);

    return iter;
}

static void _algo_bstree_int_in_order_iter(BSTIterInt *iter, NodeInt *node)
{
    if (!node) {
        return;
    }

    _algo_bstree_int_in_order_iter(iter, node->left);
    bstiter_push(iter, node);
    _algo_bstree_int_in_order_iter(iter, node->right);
}

bool algo_bstree_int_in_order_next_r(BSTIterInt *iter, int *out)
{
    NodeInt *node = bstiter_shift(iter);
    if (!node) {
        return false;
    }

    *out = node->data;

    return true;
}

bool algo_bstree_int_in_order_end_r(BSTIterInt *iter)
{
    return bstiter_is_empty(iter);
}

static void _algo_bstree_int_post_order_iter(BSTIterInt *iter, NodeInt *node);

BSTIterInt * algo_bstree_int_post_order_start_r(BSTreeInt *tree)
{
    assert(tree);

    BSTIterInt *iter = bstiter_new();
    if (!iter) {
        return iter;
    }

    _algo_bstree_int_post_order_iter(iter, tree->root);

    return iter;
}

static void _algo_bstree_int_post_order_iter(BSTIterInt *iter, NodeInt *node)
{
    if (!node) {
        return;
    }

    _algo_bstree_int_post_order_iter(iter, node->left);
    _algo_bstree_int_post_order_iter(iter, node->right);
    bstiter_push(iter, node);
}

bool algo_bstree_int_post_order_next_r(BSTIterInt *iter, int *out)
{
    NodeInt *node = bstiter_shift(iter);
    if (!node) {
        return false;
    }

    *out = node->data;

    return true;
}

bool algo_bstree_int_post_order_end_r(BSTIterInt *iter)
{
    return bstiter_is_empty(iter);
}

BSTIterInt * algo_bstree_int_pre_order_start(BSTreeInt *tree)
{
    assert(tree);

    BSTIterInt *iter = bstiter_new();
    if (!iter) {
        return iter;
    }

    if (tree->root) {
        if (!bstiter_unshift(iter, tree->root)) {
            perror("Failed to push data to iter");
            algo_bstiter_int_free(iter);
            iter = NULL;
            return iter;
        }
    }

    return iter;
}

bool algo_bstree_int_pre_order_next(BSTIterInt *iter, int *out)
{
    NodeInt *n = bstiter_shift(iter);
    if (!n) {
        return false;
    }

    if (n->right) {
        if (!bstiter_unshift(iter, n->right)) {
            return false;
        }
    }

    if (n->left) {
        if (!bstiter_unshift(iter, n->left)) {
            return false;
        }
    }

    *out = n->data;

    return true;
}

bool algo_bstree_int_pre_order_end(BSTIterInt *iter)
{
    return bstiter_is_empty(iter);
}

BSTIterInt * algo_bstree_int_in_order_start(BSTreeInt *tree)
{
    assert(tree);

    BSTIterInt *iter = bstiter_new();
    if (iter) {
        return iter;
    }

    NodeInt *curr = tree->root;
    while (curr) {
        if (!bstiter_unshift(iter, tree->root)) {
            algo_bstiter_int_free(iter);
            iter = NULL;
            return iter;
        }

        curr = curr->left;
    }

    return iter;
}

bool algo_bstree_int_in_order_next(BSTIterInt *iter, int *out)
{
    assert(iter);

    NodeInt *curr = bstiter_shift(iter);

    *out = curr->data;

    if (curr->right) {
        curr = curr->right;

        while (curr) {
            if (!bstiter_unshift(iter, curr)) {
                return false;
            }

            curr = curr->left;
        }
    }

    return true;
}

bool algo_bstree_int_in_order_end(BSTIterInt *iter)
{
    return bstiter_is_empty(iter);
}

BSTIterInt * algo_bstree_int_post_order_start(BSTreeInt *tree)
{
    assert(tree);

    bool failed = false;

    // iter is a queue.
    BSTIterInt *iter = bstiter_new();
    if (!iter) {
        return iter;
    }

    // st is a stack.
    BSTIterInt *st = bstiter_new();
    if (!st) {
        failed = true;
        goto ITER_FREE;
    }

    if (tree->root && !bstiter_push(st, tree->root)) {
        failed = true;
        goto ST_FREE;
    }

    SNodeInt *temp;
    NodeInt *prev = NULL;
    NodeInt *curr;
    while (!bstiter_is_empty(st)) {
        temp = bstiter_peek_rear(st);
        curr = temp->data;

        // we are traversing down the tree
        if (!prev || prev->left == curr || prev->right == curr) {
            if (curr->left) {
                if (!bstiter_push(st, curr->left)) {
                    failed = true;
                    goto ST_FREE;
                }
            } else if (curr->right) {
                if (!bstiter_push(st, curr->right)) {
                    failed = true;
                    goto ST_FREE;
                }
            } else {
                if (!bstiter_push(iter, curr)) {
                    failed = true;
                    goto ST_FREE;
                }

                // Discard the data.
                bstiter_pop(st);
            }
        }
        // we are traversing up the tree from the left
        else if (curr->left == prev) {
            if (curr->right) {
                if (!bstiter_push(st, curr->right)) {
                    failed = true;
                    goto ST_FREE;
                }
            } else {
                if (!bstiter_push(iter, curr)) {
                    failed = true;
                    goto ST_FREE;
                }

                // Discard the data.
                bstiter_pop(st);
            }
        }
        // we are traversing up the tree from the right
        else if (curr->right == prev) {
            if (!bstiter_push(iter, curr)) {
                failed = true;
                goto ST_FREE;
            }

            // Discard the data.
            bstiter_pop(st);
        }

        prev = curr;
    }

ST_FREE:
    algo_bstiter_int_free(st);

ITER_FREE:
    if (failed) {
        algo_bstiter_int_free(iter);
        iter = NULL;
    }

    return iter;
}

bool algo_bstree_int_post_order_next(BSTIterInt *iter, int *out)
{
    assert(iter);

    NodeInt *n = bstiter_shift(iter);
    if (!n) {
        return false;
    }

    *out = n->data;

    return true;
}

bool algo_bstree_int_post_order_end(BSTIterInt *iter)
{
    return bstiter_is_empty(iter);
}

static SNodeInt * snode_new(NodeInt *value)
{
    SNodeInt *sn = malloc(sizeof(BSTIterInt));
    if (!sn) {
        return sn;
    }

    sn->data = value;
    sn->prev = NULL;
    sn->next = NULL;

    return sn;
}

static BSTIterInt * bstiter_new()
{
    BSTIterInt *iter = malloc(sizeof(BSTIterInt));
    if (!iter) {
        return iter;
    }

    iter->head = NULL;

    return iter;
}

static bool bstiter_is_empty(BSTIterInt *self)
{
    assert(self);

    if (self->head) {
        return false;
    }

    return true;
}

static SNodeInt * bstiter_peek_front(BSTIterInt* self)
{
    assert(!bstiter_is_empty(self));

    return self->head;
}

static SNodeInt * bstiter_peek_rear(BSTIterInt *self)
{
    assert(!bstiter_is_empty(self));

    return self->tail;
}

static NodeInt * bstiter_shift(BSTIterInt *self)
{
    assert(!bstiter_is_empty(self));

    if (self->head == self->tail) {
        NodeInt *popped = self->head->data;

        free(self->head);
        self->head = NULL;
        self->tail = NULL;

        return popped;
    }

    SNodeInt * curr = self->head;
    NodeInt *popped = curr->data;

    self->head = curr->next;
    free(curr);
    self->head->prev = NULL;

    return popped;
}

static bool bstiter_unshift(BSTIterInt *self, NodeInt *value)
{
    assert(self);

    SNodeInt *sn = snode_new(value);
    if (!sn) {
        return false;
    }

    if (!(self->head)) {
        self->head = sn;
        self->tail = sn;
        return true;
    }

    sn->next = self->head;
    self->head->prev = sn;
    self->head = sn;

    return true;
}

static bool bstiter_push(BSTIterInt *self, NodeInt *data)
{
    assert(self);

    SNodeInt *sn = snode_new(data);
    if (!sn) {
        return false;
    }

    if (!(self->tail)) {
        self->head = sn;
        self->tail = sn;
        return true;
    }

    self->tail->next = sn;
    sn->prev = self->tail;
    self->tail = sn;

    return true;
}

static NodeInt * bstiter_pop(BSTIterInt *self)
{
    assert(!bstiter_is_empty(self));

    if (self->head == self->tail) {
        NodeInt *popped = self->tail->data;

        free(self->tail);
        self->head = NULL;
        self->tail = NULL;

        return popped;
    }

    SNodeInt *curr = self->tail;
    NodeInt *popped = curr->data;

    self->tail = curr->prev;
    free(curr);
    self->tail->next = NULL;

    return popped;
}

void algo_bstiter_int_free(void *self)
{
    if (!self) {
        return;
    }

    SNodeInt *curr = ((BSTIterInt *) self)->head;
    SNodeInt *temp;
    while (curr) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(self);
}
