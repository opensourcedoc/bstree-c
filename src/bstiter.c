#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "algo/bstree.h"
#include "bstree_internal.h"
#include "bstnode.h"
#include "algo/bstiter.h"

typedef struct snode_int_t snode_int_t;

struct snode_int_t {
    node_int_t *data;
    snode_int_t *next;
    snode_int_t *prev;
};

// bstiter_int_t is a deque.
struct bstiter_int_t {
    snode_int_t *head;
    snode_int_t *tail;
};

static snode_int_t * snode_new(node_int_t *value);
static bstiter_int_t * bstiter_new(void);
static bool bstiter_is_empty(bstiter_int_t *self);
static snode_int_t * bstiter_peek_front(bstiter_int_t* self);
static snode_int_t * bstiter_peek_rear(bstiter_int_t *self);
static bool bstiter_unshift(bstiter_int_t *self, node_int_t *data);
static node_int_t * bstiter_shift(bstiter_int_t *self);
static bool bstiter_push(bstiter_int_t *self, node_int_t *data);
static node_int_t * bstiter_pop(bstiter_int_t *self);

static void _algo_bstree_int_pre_order(node_int_t *node);

void algo_bstree_int_pre_order(bstree_int_t *self)
{
    assert(self);

    _algo_bstree_int_pre_order(self->root);

    printf("\n");
}

static void _algo_bstree_int_pre_order(node_int_t *node)
{
    if (!node) {
        return;
    }

    printf("%d ", node->data);
    _algo_bstree_int_pre_order(node->left);
    _algo_bstree_int_pre_order(node->right);
}

static void _algo_bstree_int_in_order(node_int_t *node);

void algo_bstree_int_in_order(bstree_int_t *self)
{
    assert(self);

    _algo_bstree_int_in_order(self->root);

    printf("\n");
}

static void _algo_bstree_int_in_order(node_int_t *node)
{
    if (!node) {
        return;
    }

    _algo_bstree_int_in_order(node->left);
    printf("%d ", node->data);
    _algo_bstree_int_in_order(node->right);
}

static void _algo_bstree_int_post_order(node_int_t *node);

void algo_bstree_int_post_order(bstree_int_t *self)
{
    assert(self);

    _algo_bstree_int_post_order(self->root);

    printf("\n");
}

static void _algo_bstree_int_post_order(node_int_t *node)
{
    if (!node) {
        return;
    }

    _algo_bstree_int_post_order(node->left);
    _algo_bstree_int_post_order(node->right);
    printf("%d ", node->data);
}

static void _algo_bstree_int_pre_order_iter(bstiter_int_t *iter, node_int_t *node);

bstiter_int_t * algo_bstree_int_pre_order_start_r(bstree_int_t *tree)
{
    assert(tree);

    bstiter_int_t *iter = bstiter_new();
    if (!iter) {
        return iter;
    }

    _algo_bstree_int_pre_order_iter(iter, tree->root);

    return iter;
}

static void _algo_bstree_int_pre_order_iter(bstiter_int_t *iter, node_int_t *node)
{
    if (!node) {
        return;
    }

    bstiter_push(iter, node);
    _algo_bstree_int_pre_order_iter(iter, node->left);
    _algo_bstree_int_pre_order_iter(iter, node->right);
}

bool algo_bstree_int_pre_order_next_r(bstiter_int_t *iter, int *out)
{
    node_int_t *node = bstiter_shift(iter);
    if (!node) {
        return false;
    }

    *out = node->data;

    return true;
}

bool algo_bstree_int_pre_order_end_r(bstiter_int_t *iter)
{
    return bstiter_is_empty(iter);
}

static void _algo_bstree_int_in_order_iter(bstiter_int_t *iter, node_int_t *node);

bstiter_int_t * algo_bstree_int_in_order_start_r(bstree_int_t *tree)
{
    assert(tree);

    bstiter_int_t *iter = bstiter_new();
    if (!iter) {
        return iter;
    }

    _algo_bstree_int_in_order_iter(iter, tree->root);

    return iter;
}

static void _algo_bstree_int_in_order_iter(bstiter_int_t *iter, node_int_t *node)
{
    if (!node) {
        return;
    }

    _algo_bstree_int_in_order_iter(iter, node->left);
    bstiter_push(iter, node);
    _algo_bstree_int_in_order_iter(iter, node->right);
}

bool algo_bstree_int_in_order_next_r(bstiter_int_t *iter, int *out)
{
    node_int_t *node = bstiter_shift(iter);
    if (!node) {
        return false;
    }

    *out = node->data;

    return true;
}

bool algo_bstree_int_in_order_end_r(bstiter_int_t *iter)
{
    return bstiter_is_empty(iter);
}

static void _algo_bstree_int_post_order_iter(bstiter_int_t *iter, node_int_t *node);

bstiter_int_t * algo_bstree_int_post_order_start_r(bstree_int_t *tree)
{
    assert(tree);

    bstiter_int_t *iter = bstiter_new();
    if (!iter) {
        return iter;
    }

    _algo_bstree_int_post_order_iter(iter, tree->root);

    return iter;
}

static void _algo_bstree_int_post_order_iter(bstiter_int_t *iter, node_int_t *node)
{
    if (!node) {
        return;
    }

    _algo_bstree_int_post_order_iter(iter, node->left);
    _algo_bstree_int_post_order_iter(iter, node->right);
    bstiter_push(iter, node);
}

bool algo_bstree_int_post_order_next_r(bstiter_int_t *iter, int *out)
{
    node_int_t *node = bstiter_shift(iter);
    if (!node) {
        return false;
    }

    *out = node->data;

    return true;
}

bool algo_bstree_int_post_order_end_r(bstiter_int_t *iter)
{
    return bstiter_is_empty(iter);
}

bstiter_int_t * algo_bstree_int_pre_order_start(bstree_int_t *tree)
{
    assert(tree);

    bstiter_int_t *iter = bstiter_new();
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

bool algo_bstree_int_pre_order_next(bstiter_int_t *iter, int *out)
{
    node_int_t *n = bstiter_shift(iter);
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

bool algo_bstree_int_pre_order_end(bstiter_int_t *iter)
{
    return bstiter_is_empty(iter);
}

bstiter_int_t * algo_bstree_int_in_order_start(bstree_int_t *tree)
{
    assert(tree);

    bstiter_int_t *iter = bstiter_new();
    if (iter) {
        return iter;
    }

    node_int_t *curr = tree->root;
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

bool algo_bstree_int_in_order_next(bstiter_int_t *iter, int *out)
{
    assert(iter);

    node_int_t *curr = bstiter_shift(iter);

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

bool algo_bstree_int_in_order_end(bstiter_int_t *iter)
{
    return bstiter_is_empty(iter);
}

bstiter_int_t * algo_bstree_int_post_order_start(bstree_int_t *tree)
{
    assert(tree);

    bool failed = false;

    // iter is a queue.
    bstiter_int_t *iter = bstiter_new();
    if (!iter) {
        return iter;
    }

    // st is a stack.
    bstiter_int_t *st = bstiter_new();
    if (!st) {
        failed = true;
        goto ITER_FREE;
    }

    if (tree->root && !bstiter_push(st, tree->root)) {
        failed = true;
        goto ST_FREE;
    }

    snode_int_t *temp;
    node_int_t *prev = NULL;
    node_int_t *curr;
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

bool algo_bstree_int_post_order_next(bstiter_int_t *iter, int *out)
{
    assert(iter);

    node_int_t *n = bstiter_shift(iter);
    if (!n) {
        return false;
    }

    *out = n->data;

    return true;
}

bool algo_bstree_int_post_order_end(bstiter_int_t *iter)
{
    return bstiter_is_empty(iter);
}

static snode_int_t * snode_new(node_int_t *value)
{
    snode_int_t *sn = malloc(sizeof(bstiter_int_t));
    if (!sn) {
        return sn;
    }

    sn->data = value;
    sn->prev = NULL;
    sn->next = NULL;

    return sn;
}

static bstiter_int_t * bstiter_new(void)
{
    bstiter_int_t *iter = malloc(sizeof(bstiter_int_t));
    if (!iter) {
        return iter;
    }

    iter->head = NULL;

    return iter;
}

static bool bstiter_is_empty(bstiter_int_t *self)
{
    assert(self);

    if (self->head) {
        return false;
    }

    return true;
}

static snode_int_t * bstiter_peek_front(bstiter_int_t* self)
{
    assert(!bstiter_is_empty(self));

    return self->head;
}

static snode_int_t * bstiter_peek_rear(bstiter_int_t *self)
{
    assert(!bstiter_is_empty(self));

    return self->tail;
}

static node_int_t * bstiter_shift(bstiter_int_t *self)
{
    assert(!bstiter_is_empty(self));

    if (self->head == self->tail) {
        node_int_t *popped = self->head->data;

        free(self->head);
        self->head = NULL;
        self->tail = NULL;

        return popped;
    }

    snode_int_t * curr = self->head;
    node_int_t *popped = curr->data;

    self->head = curr->next;
    free(curr);
    self->head->prev = NULL;

    return popped;
}

static bool bstiter_unshift(bstiter_int_t *self, node_int_t *value)
{
    assert(self);

    snode_int_t *sn = snode_new(value);
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

static bool bstiter_push(bstiter_int_t *self, node_int_t *data)
{
    assert(self);

    snode_int_t *sn = snode_new(data);
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

static node_int_t * bstiter_pop(bstiter_int_t *self)
{
    assert(!bstiter_is_empty(self));

    if (self->head == self->tail) {
        node_int_t *popped = self->tail->data;

        free(self->tail);
        self->head = NULL;
        self->tail = NULL;

        return popped;
    }

    snode_int_t *curr = self->tail;
    node_int_t *popped = curr->data;

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

    snode_int_t *curr = ((bstiter_int_t *) self)->head;
    snode_int_t *temp;
    while (curr) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(self);
}
