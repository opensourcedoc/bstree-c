#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "test_manipulation.h"
#include "test_traversal.h"

#define TEST(test) { \
        if (!(test)) { \
            fprintf(stderr, "%s on %d: Failed on %s", __FILE__, __LINE__, #test); \
            exit(EXIT_FAILURE); \
        } \
    }

int main()
{
    TEST(test_tree_is_empty());
    TEST(test_tree_insert());
    TEST(test_tree_min());
    TEST(test_tree_max());
    TEST(test_tree_delete_leaf());
    TEST(test_tree_delete_one_child());
    TEST(test_tree_delete_two_childs());
    TEST(test_tree_pre_order());
    TEST(test_tree_in_order());
    TEST(test_tree_post_order());
    TEST(test_tree_pre_order_iter());
    
    return 0;
}
