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
};

// BSTIter is a stack.
struct bstIter {
    SNode *top;
};

static SNode * snode_new(Node *value);
static BSTIter * bstiter_new();
static bool bstiter_is_empty(BSTIter *self);
static SNode * bstiter_peek(BSTIter* self);
static bool bstiter_push(BSTIter *self, Node *data);
static Node * bstiter_pop(BSTIter *self);

BSTIter * bstree_pre_order_start(BSTree *tree)
{
    BSTIter *iter = bstiter_new();
    if (!iter) {
        return iter;
    }
    
    if (tree->root) {
        if (!bstiter_push(iter, tree->root)) {
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
    Node *n = bstiter_pop(iter);
    if (!n) {
        return false;
    }

    if (n->right) {
        if (!bstiter_push(iter, n->right)) {
            return false;
        }
    }

    if (n->left) {
        if (!bstiter_push(iter, n->left)) {
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

static SNode * snode_new(Node *value)
{
    SNode *sn = malloc(sizeof(BSTIter));
    if (!sn) {
        return sn;
    }
    
    sn->data = value;
    sn->next = NULL;
    
    return sn;
}

static BSTIter * bstiter_new()
{
    BSTIter *iter = malloc(sizeof(BSTIter));
    if (!iter) {
        return iter;
    }
    
    iter->top = NULL;
    
    return iter;
}

static bool bstiter_is_empty(BSTIter *self)
{
    assert(self);
    
    if (self->top) {
        return false;
    }
    
    return true;
}

static SNode * bstiter_peek(BSTIter* self)
{
    assert(!bstiter_is_empty(self));
    
    return self->top;
}

static Node * bstiter_pop(BSTIter *self)
{
    assert(!bstiter_is_empty(self));
    
    SNode * curr = self->top;
    Node * popped = curr->data;
    self->top = curr->next;
    free(curr);
    
    return popped;
}

static bool bstiter_push(BSTIter *self, Node *value)
{
    assert(self);
    
    SNode *sn = snode_new(value);
    if (!sn) {
        return false;
    }
    
    if (!(self->top)) {
        self->top = sn;
        return true;
    }
    
    sn->next = self->top;
    self->top = sn;
    
    return true;
}

void bstiter_free(void *self)
{
    if (!self) {
        return;
    }
    
    SNode *curr = ((BSTIter *) self)->top;
    SNode *temp;
    while (curr) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    
    free(self);
}