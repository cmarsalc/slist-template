/*************************************************************************//**
 * @copyright COPYRIGHT (C) 2021 IDNEO S.A.U.
 *
 * @file slist_template.h
 * @date 2021-03-11
 * @author Carles Marsal
 *
 * Language C99
 *
 * @version $Id$
 *
 * @addtogroup Collections
 * @{
 *
 * @brief Single list template
 *
 * @details
 *
 * 	This is a template for a single linked list FIFO ordered using static memory.
 *
 * 	This template has to be instantiated somewhere, that means declaration in
 * 	a C header or module and definition in a C module. For example:
 *
 *		```
 * 		uint32_slist_implementation.h:
 * 			SLIST_DECLARE(uint32_t)
 *
 * 		uint32_slist_implementation.c:
 * 			SLIST_DEFINE(uint32_t)
 * 		```
 *
 *  Given the templates only use static memory, the clients that are willing
 *  to be added to a given list shall provide that memory. That is accomplished
 *  by declaring a variable of type SLIST_NODE(T), where T is the target type:
 *
 * 		`SLIST_NODE(uint32_t) nodeContainingUint32;`
 *
 * 	Content of the node can be manipulated directly through the `data` field of
 * 	the node:
 *
 * 		`nodeContainingUint32.data = dataOfTypeUint32;`
 *
 * 	To add a node to a list, first a list have to be created:
 *
 * 		`SLIST_CREATE_LIST(uint32_t) uint32List;`
 *
 * 	Then, it's just a matter of calling the right macro:
 *
 * 		`SLIST_ADD_NODE(uint32_t, uint32List, nodeContainingUint32);`
 *
 * 	Due to using the client memory a node cannot be repeated on the list
 * 	as the list will be corrupted (becoming infinitely circular), so calling
 * 	again `SLIST_ADD_ADD_NODE(uint32_t, dataOfTypeUint32)` has no effect.
 *
 * 	If a node value has to be repeated a new node has to be provided by the
 * 	client with the same value, like:
 *
 * 		`SLIST_ADD_NODE(uint32_t, uint32List, anotherNodeWithTheSameValue);`
 *
 * 	Finally, to traverse the list a for each like macro can be used:
 *
 *		```
 * 		// Set all nodes data to zero
 * 		SLIT_FOR_EACH_NODE_PTR(uint32_t, uint32List, node)
 * 		{
 * 			node->data = 0;
 * 		}
 * 		```
 *
 *	Note that this is the only function suffixed with `_PTR` indicating that a reference
 *	is provided by the traversal operation, rather than a copied value.
 *
 *	If the list have to be passed to other functions it has to be passed
 *	as a pointer to `SLIST_NODE(T)` as it is just a pointer to the head of
 *	the list. Something like this:
 *
 *		```
 *		void print_list(SLIST_NODE(uint32_t)* list)
 *		{
 *	    	printf("---\n");
 *	    	SLIST_FOR_EACH_NODE_PTR(uint32_t, list, node)
 *	    	{
 *	        	printf("%d\n", node->data);
 *	    	}
 *		}
 *
 *		print_list(uint32List);
 *		```
 *
 *
 *	(*) An alternative implementation could be provided where there was
 *	no need for definition, expanding macro calls directly in client code
 *	instead of expanding a call to a function defined elsewhere. The tradeoff
 *	would be more footprint, slightly better performance, and mainly, not
 *	being necessary to have a SINGLE module defining the functionality.
 *
 *	This list is partially inspired in BSD template collection, although
 *	I wanted something a little more simple, as the use case is also more simple.
 *
 *	Anybody interested in this topic should read the following stack overflow
 *	entry as it has some very valid points and references some other implementations.
 *
 *	https://stackoverflow.com/questions/3039513/type-safe-generic-data-structures-in-plain-old-c
 *
 ****************************************************************************/

#ifndef SLIST_TEMPLATE_H_
#define SLIST_TEMPLATE_H_

/*****************************************************************************
 * INCLUDES
 ****************************************************************************/
#include <stddef.h>

/*****************************************************************************
 * MACROS
 ****************************************************************************/

/*
 * Use either:
 *
 * - SLIST_DECLARE(T) in a C header: for public declaration
 * - SLIST_DECLARE_STATIC(T) in a C module: for private declaration
 */

#define SLIST_DECLARE(T) \
SLIST_DECLARE_NODE_TYPE(T); \
SLIST_DECLARE_ADD_NODE_FUNC(T)

#define SLIST_DECLARE_STATIC(T) \
SLIST_DECLARE_NODE_TYPE(T); \
static SLIST_DECLARE_ADD_NODE_FUNC(T)

/*
 * Use either:
 *
 * - SLIST_DEFINE(T) in a C header: for public declaration
 * - SLIST_DEFINE_STATIC(T) in a C module: for private declaration
 */

#define SLIST_DEFINE(T) \
SLIST_DEFINE_ADD_NODE_FUNC(T)

#define SLIST_DEFINE_STATIC(T) \
static SLIST_DEFINE_ADD_NODE_FUNC(T)

/*
 * Usage:
 *
 *	SLIST_CREATE_LIST(T, list);		// creates a list<T>
 * 	SLIST_NODE(T) node; 			// declares a node<T>
 * 	node.data = data;				// assigns data to node<T>
 * 	SLIST_ADD_NODE(T, node)			// adds node<T> to list without repetition
 * 	SLIST_FOR_EACH_NODE_PTR(T, list, node)
 * 	{
 * 		node->data
 * 	}
 */

#define SLIST_CREATE_LIST(T, head_) \
SLIST_NODE(T)* (head_) = NULL

#define SLIST_NODE(T) \
struct sSLIST_##T##_Node

#define SLIST_ADD_NODE(T, head_, node_) \
SLIST_add_##T(&(head_), &(node_))

#define SLIST_ADD_NODE_PTR(T, head_, node_) \
SLIST_add_##T(&(head_), (node_))

#define SLIST_FOR_EACH_NODE_PTR(T, head_, node_) \
for (SLIST_NODE(T)* (node_) = (head_); (node_) != NULL ; (node_) = (node_)->next) \

/*
 * The templates themselves
 */

#define SLIST_DECLARE_NODE_TYPE(T) \
SLIST_NODE(T) { \
    T data; \
    SLIST_NODE(T)* next; \
}

#define SLIST_DECLARE_ADD_NODE_FUNC(T) \
void SLIST_add_##T(SLIST_NODE(T)** head, SLIST_NODE(T)* node)

#define SLIST_DEFINE_ADD_NODE_FUNC(T) \
SLIST_DECLARE_ADD_NODE_FUNC(T) \
{ \
    if (*head == NULL) \
    { \
        *head = node; \
        node->next = NULL; \
    } \
    else \
    { \
        SLIST_NODE(T)* curr = *head; \
        while (curr->next != NULL) \
        { \
            if (curr == node) \
            { \
                return; \
            } \
            curr = curr->next; \
        } \
        curr->next = node; \
    } \
    node->next = NULL; \
}

#endif /* SLIST_TEMPLATE_H_ */

/*************************************************************************//**
 *    End of file
 *    }@
 ***************************************************************************/

