#include "bstnode.h"

Node * node_new(int value)
{
    Node *n = malloc(sizeof(Node));
    
    if (!n) {
        return n;
    }
    
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    
    return n;
}