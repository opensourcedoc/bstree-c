#ifndef BSTNODE_H
#define BSTNODE_H

#include <stdlib.h>

typedef struct node_int_t node_int_t;

struct node_int_t {
    int data;
    node_int_t *left;
    node_int_t *right;
};

node_int_t * node_new(int value);

#endif  // BSTNODE_H
