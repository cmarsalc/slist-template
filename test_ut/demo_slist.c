/**
 * Simple demo to be compiled and executed in a host PC
 */

#include "../slist_template.h"
#include <stdint.h>
#include <stdio.h>

SLIST_DECLARE(uint32_t);
SLIST_DEFINE(uint32_t);

void print_list(SLIST_NODE(uint32_t)* list)
{
    printf("---\n");
    SLIST_FOR_EACH_NODE_PTR(uint32_t, list, node)
    {
        printf("%d\n", node->data);
    }
}

void main(void)
{
	SLIST_CREATE_LIST(uint32_t, list);

    SLIST_NODE(uint32_t) a1, a2, a3, a4, a5;

    a1.data = 1;
    a2.data = 2;
    a3.data = 3;
    a4.data = 4;
    a5.data = 5;

    SLIST_ADD_NODE(uint32_t, list, a1);
    print_list(list);
    SLIST_ADD_NODE(uint32_t, list, a2);
    print_list(list);
    SLIST_ADD_NODE(uint32_t, list, a3);
    print_list(list);
    SLIST_ADD_NODE(uint32_t, list, a4);
    print_list(list);
    SLIST_ADD_NODE(uint32_t, list, a5);
    print_list(list);
    // same node cannot be repeated
    SLIST_ADD_NODE(uint32_t, list, a5);
    print_list(list);
}
