#include "bstnode.h"

NodeInt * node_new(int value)
{
    NodeInt *n = malloc(sizeof(NodeInt));

    if (!n) {
        return n;
    }

    n->data = value;
    n->left = NULL;
    n->right = NULL;

    return n;
}
