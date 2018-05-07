#ifndef BSTNODE_H
#define BSTNODE_H

#include <stdlib.h>

typedef struct node_int NodeInt;

struct node_int {
    int data;
    NodeInt *left;
    NodeInt *right;
};

NodeInt * node_new(int value);

#endif  // BSTNODE_H
