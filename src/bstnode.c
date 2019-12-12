#include "bstnode.h"

node_int_t * node_new(int value)
{
    node_int_t *n = malloc(sizeof(node_int_t));

    if (!n) {
        return n;
    }

    n->data = value;
    n->left = NULL;
    n->right = NULL;

    return n;
}
