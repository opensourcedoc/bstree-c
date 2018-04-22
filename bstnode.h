#ifndef BSTNODE_H
#define BSTNODE_H

#include <stdlib.h>

typedef struct node Node;

struct node {
    int data;
    Node *left;
    Node *right;
};

Node * node_new(int value);

#endif  // BSTNODE_H