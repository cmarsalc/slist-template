#include "unity.h"
#include "slist_template.h"

#include <stdint.h>


typedef struct {
	uint8_t var1;
	uint8_t var2;
} sTestType;

SLIST_DECLARE_STATIC(sTestType);
SLIST_DEFINE_STATIC(sTestType);

void test_WhenNoElements_NoForEachExecuted(void)
{
	// Arrange
	SLIST_CREATE_LIST(sTestType, list);
	// Act and assert
	SLIST_FOR_EACH_NODE_PTR(sTestType, list, node)
	{
		TEST_FAIL();
	}
}

void test_WhenOneElement_ForEachFindsThatElement(void)
{
	// Arrange
	SLIST_CREATE_LIST(sTestType, list);
	SLIST_NODE(sTestType) node1;
	node1.data.var1 = 1;
	node1.data.var2 = 2;
	SLIST_ADD_NODE(sTestType, list, node1);
	// Act and assert
	uint8_t found = 0;
	SLIST_FOR_EACH_NODE_PTR(sTestType, list, node)
	{
		found++;
		TEST_ASSERT_EQUAL(node1.data.var1, node->data.var1);
		TEST_ASSERT_EQUAL(node1.data.var2, node->data.var2);
	}
	TEST_ASSERT_EQUAL(1, found);
}

void test_WhenTwoElements_ForEachFindsThoseTwoElements(void)
{
	// Arrange
	SLIST_CREATE_LIST(sTestType, list);
	SLIST_NODE(sTestType) node1, node2;
	node1.data.var1 = 1;
	node1.data.var2 = 2;
	node2.data.var1 = 3;
	node2.data.var2 = 4;
	SLIST_ADD_NODE(sTestType, list, node1);
	SLIST_ADD_NODE(sTestType, list, node2);
	// Act and assert
	uint8_t found = 0;
	SLIST_FOR_EACH_NODE_PTR(sTestType, list, node)
	{
		TEST_ASSERT_EQUAL_MESSAGE(++found, node->data.var1, "Unexpected var1 field");
		TEST_ASSERT_EQUAL_MESSAGE(++found, node->data.var2, "Unexpected var2 field");
	}
	TEST_ASSERT_EQUAL_MESSAGE(2, found/2, "Unexpected number of nodes found");
}
