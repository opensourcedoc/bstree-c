#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "bstree_internal.h"
#include "bstnode.h"
#include "bstiter.h"

typedef struct snode SNode;

struct snode {
    Node *data;
    SNode *next;
    SNode *prev;
};

// BSTIter is a deque.
struct bstIter {
    SNode *head;
    SNode *tail;
};

static SNode * snode_new(Node *value);
static BSTIter * bstiter_new();
static bool bstiter_is_empty(BSTIter *self);
static SNode * bstiter_peek_front(BSTIter* self);
static SNode * bstiter_peek_rear(BSTIter *self);
static bool bstiter_unshift(BSTIter *self, Node *data);
static Node * bstiter_shift(BSTIter *self);
static bool bstiter_push(BSTIter *self, Node *data);
static Node * bstiter_pop(BSTIter *self);

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

BSTIter * bstree_pre_order_start(BSTree *tree)
{
    assert(tree);

    BSTIter *iter = bstiter_new();
    if (!iter) {
        return iter;
    }
    
    if (tree->root) {
        if (!bstiter_unshift(iter, tree->root)) {
            perror("Failed to push data to iter");
            bstiter_free(iter);
            iter = NULL;
            return iter;
        }
    }
    
    return iter;
}

bool bstree_pre_order_next(BSTIter *iter, int *out)
{
    Node *n = bstiter_shift(iter);
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

bool bstree_pre_order_end(BSTIter *iter)
{
    return bstiter_is_empty(iter);
}

BSTIter * bstree_in_order_start(BSTree *tree)
{
    assert(tree);

    BSTIter *iter = bstiter_new();
    if (iter) {
        return iter;
    }
    
    Node *curr = tree->root;
    while (curr) {
        if (!bstiter_unshift(iter, tree->root)) {
            bstiter_free(iter);
            iter = NULL;
            return iter;
        }
        
        curr = curr->left;
    }
    
    return iter;
}

bool bstree_in_order_next(BSTIter *iter, int *out)
{
    assert(iter);
    
    Node *curr = bstiter_shift(iter);
    
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

bool bstree_in_order_end(BSTIter *iter)
{
    return bstiter_is_empty(iter);
}

BSTIter * bstree_post_order_start(BSTree *tree)
{
    assert(tree);

    bool failed = false;

    // iter is a queue.
    BSTIter *iter = bstiter_new();
    if (!iter) {
        return iter;
    }
    
    // st is a stack.
    BSTIter *st = bstiter_new();
    if (!st) {
        failed = true;
        goto ITER_FREE;
    }

    if (tree->root && !bstiter_push(st, tree->root)) {
        failed = true;
        goto ST_FREE;
    }

    SNode *temp;
    Node *prev = NULL;
    Node *curr;
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
    bstiter_free(st);

ITER_FREE:
    if (failed) {
        bstiter_free(iter);
        iter = NULL;
    }
    
    return iter;
}

bool bstree_post_order_next(BSTIter *iter, int *out)
{
    assert(iter);
    
    Node *n = bstiter_shift(iter);
    if (!n) {
        return false;
    }

    *out = n->data;
    
    return true;
}

bool bstree_post_order_end(BSTIter *iter)
{
    return bstiter_is_empty(iter);
}

static SNode * snode_new(Node *value)
{
    SNode *sn = malloc(sizeof(BSTIter));
    if (!sn) {
        return sn;
    }
    
    sn->data = value;
    sn->prev = NULL;
    sn->next = NULL;
    
    return sn;
}

static BSTIter * bstiter_new()
{
    BSTIter *iter = malloc(sizeof(BSTIter));
    if (!iter) {
        return iter;
    }
    
    iter->head = NULL;
    
    return iter;
}

static bool bstiter_is_empty(BSTIter *self)
{
    assert(self);
    
    if (self->head) {
        return false;
    }
    
    return true;
}

static SNode * bstiter_peek_front(BSTIter* self)
{
    assert(!bstiter_is_empty(self));
    
    return self->head;
}

static SNode * bstiter_peek_rear(BSTIter *self)
{
    assert(!bstiter_is_empty(self));
    
    return self->tail;
}

static Node * bstiter_shift(BSTIter *self)
{
    assert(!bstiter_is_empty(self));

    if (self->head == self->tail) {
        Node *popped = self->head->data;
        
        free(self->head);
        self->head = NULL;
        self->tail = NULL;
        
        return popped;
    }

    SNode * curr = self->head;
    Node *popped = curr->data;

    self->head = curr->next;
    free(curr);
    self->head->prev = NULL;
    
    return popped;
}

static bool bstiter_unshift(BSTIter *self, Node *value)
{
    assert(self);
    
    SNode *sn = snode_new(value);
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

static bool bstiter_push(BSTIter *self, Node *data)
{
    assert(self);

    SNode *sn = snode_new(data);
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

static Node * bstiter_pop(BSTIter *self)
{
    assert(!bstiter_is_empty(self));
    
    if (self->head == self->tail) {
        Node *popped = self->tail->data;
        
        free(self->tail);
        self->head = NULL;
        self->tail = NULL;
        
        return popped;
    }
    
    SNode *curr = self->tail;
    Node *popped = curr->data;
    
    self->tail = curr->prev;
    free(curr);
    self->tail->next = NULL;
    
    return popped;
}

void bstiter_free(void *self)
{
    if (!self) {
        return;
    }
    
    SNode *curr = ((BSTIter *) self)->head;
    SNode *temp;
    while (curr) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    
    free(self);
}