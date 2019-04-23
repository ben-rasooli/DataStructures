#include "pch.h"
#include <stdexcept>
#include <gtest/gtest.h>
#include "../DataStructuresLib/DoublyLinkedList.h"
#include "../DataStructuresLib/LinkedListNode.h"

using namespace std;

template<typename T>
class DoublyLinkedListTests : public testing::Test
{
protected:
	DoublyLinkedList<int> _sut;
};

using MyTypes = testing::Types< int >;
TYPED_TEST_CASE(DoublyLinkedListTests, MyTypes);

TYPED_TEST(DoublyLinkedListTests, a_new_linkedList_has_zero_count_and_is_empty)
{
	int actualCount = _sut.Count();
	bool actualIfEmpty = _sut.IsEmpty();

	EXPECT_EQ(actualCount, 0);
	EXPECT_TRUE(actualIfEmpty);
}

TYPED_TEST(DoublyLinkedListTests, a_linkedList_becomes_non_empty_when_pushing_new_item)
{
	_sut.PushBack(1);

	bool actualIfEmpty = _sut.IsEmpty();

	EXPECT_FALSE(actualIfEmpty);
}

TYPED_TEST(DoublyLinkedListTests, Count_is_incremented_when_pushing_an_item)
{
	_sut.PushBack(1);
	_sut.PushBack(1);
	int actualCountAfterPush = _sut.Count();

	EXPECT_EQ(actualCountAfterPush, 2);

	_sut.PushFront(1);
	_sut.PushFront(1);
	actualCountAfterPush = _sut.Count();

	EXPECT_EQ(actualCountAfterPush, 4);
}

TYPED_TEST(DoublyLinkedListTests, accessing_first_or_last_item_on_empty_linkedList_throws_exception)
{
	EXPECT_THROW(_sut.First(), out_of_range);
	EXPECT_THROW(_sut.Last(), out_of_range);
}

TYPED_TEST(DoublyLinkedListTests, PushBack_adds_the_item_to_end_of_the_linkedList)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(3);

	int actualFirstItem = _sut.First();
	int actualLastItem = _sut.Last();

	EXPECT_EQ(actualFirstItem, 1);
	EXPECT_EQ(actualLastItem, 3);
}

TYPED_TEST(DoublyLinkedListTests, PushFront_adds_the_item_to_start_of_the_linkedList)
{
	_sut.PushFront(1);
	_sut.PushFront(2);
	_sut.PushFront(3);

	int actualFirstItem = _sut.First();
	int actualLastItem = _sut.Last();

	EXPECT_EQ(actualFirstItem, 3);
	EXPECT_EQ(actualLastItem, 1);
}

TYPED_TEST(DoublyLinkedListTests, Find_throws_exception_on_empty_linkedList)
{
	EXPECT_THROW(_sut.Find(1), out_of_range);
}

TYPED_TEST(DoublyLinkedListTests, Find_returns_a_LinkedListNode_based_on_searching_value)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(3);

	LinkedListNode* actualReturnedNode = _sut.Find(2);

	EXPECT_EQ(actualReturnedNode->Value, 2);
	EXPECT_EQ(actualReturnedNode->prevItem->Value, 1);
	EXPECT_EQ(actualReturnedNode->nextItem->Value, 3);
}
