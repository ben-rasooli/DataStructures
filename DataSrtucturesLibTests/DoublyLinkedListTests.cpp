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

	LinkedListNode* item = _sut.Find(1);
	_sut.PushAfter(item, 1);
	_sut.PushBefore(item, 1);
	actualCountAfterPush = _sut.Count();

	EXPECT_EQ(actualCountAfterPush, 6);
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

TYPED_TEST(DoublyLinkedListTests, PushAfter_inserts_the_item_after_a_specified_item)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(4);

	LinkedListNode* item_2 = _sut.Find(2);
	LinkedListNode* item_4 = _sut.Find(4);

	int actualItem_2_nextItem_beforePushing = item_2->nextNode->Value;
	int actualItem_4_prevItem_beforePushing = item_4->prevNode->Value;

	_sut.PushAfter(item_2, 3);

	int actualItem_2_nextItem_afterPushing = item_2->nextNode->Value;
	int actualItem_4_prevItem_afterPushing = item_4->prevNode->Value;

	EXPECT_EQ(actualItem_2_nextItem_beforePushing, 4);
	EXPECT_EQ(actualItem_4_prevItem_beforePushing, 2);

	EXPECT_EQ(actualItem_2_nextItem_afterPushing, 3);
	EXPECT_EQ(actualItem_4_prevItem_afterPushing, 3);
}

TYPED_TEST(DoublyLinkedListTests, Find_throws_exception_on_empty_linkedList)
{
	EXPECT_THROW(_sut.Find(1), out_of_range);
}

TYPED_TEST(DoublyLinkedListTests, Find_returns_the_first_matching_item)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(3);

	LinkedListNode* actualReturnedNode = _sut.Find(2);

	EXPECT_EQ(actualReturnedNode->Value, 2);
	EXPECT_EQ(actualReturnedNode->prevNode->Value, 1);
	EXPECT_EQ(actualReturnedNode->nextNode->Value, 3);
}

TYPED_TEST(DoublyLinkedListTests, FindLast_returns_the_last_matching_item)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(3);
	_sut.PushBack(2);
	_sut.PushBack(4);

	LinkedListNode* actualReturnedNode = _sut.FindLast(2);

	EXPECT_EQ(actualReturnedNode->Value, 2);
	EXPECT_EQ(actualReturnedNode->prevNode->Value, 3);
	EXPECT_EQ(actualReturnedNode->nextNode->Value, 4);
}

TYPED_TEST(DoublyLinkedListTests, First_returns_the_first_item_in_linkedList)
{
	int firstItem = 1;
	_sut.PushBack(firstItem);
	_sut.PushBack(2);
	_sut.PushBack(3);

	int actualFirstItem = _sut.First();

	EXPECT_EQ(actualFirstItem, firstItem);
}

TYPED_TEST(DoublyLinkedListTests, First_throws_exception_on_empty_linkedList)
{
	EXPECT_THROW(_sut.First(), out_of_range);
}

TYPED_TEST(DoublyLinkedListTests, Last_returns_the_last_item_in_linkedList)
{
	int lastItem = 3;
	_sut.PushBack(lastItem);
	_sut.PushBack(2);
	_sut.PushBack(3);

	int actualLastItem = _sut.Last();

	EXPECT_EQ(actualLastItem, lastItem);
}

TYPED_TEST(DoublyLinkedListTests, Lasst_throws_exception_on_empty_linkedList)
{
	EXPECT_THROW(_sut.First(), out_of_range);
}

TYPED_TEST(DoublyLinkedListTests, Remove_removes_an_item)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(3);

	LinkedListNode* node_1 = _sut.Find(1);
	LinkedListNode* node_2 = _sut.Find(2);
	LinkedListNode* node_3 = _sut.Find(3);

	int actualCountBeforeRemove = _sut.Count();

	_sut.Remove(node_2->Value);

	int actualCountAfterRemove = _sut.Count();

	EXPECT_EQ(actualCountBeforeRemove, 3);
	EXPECT_EQ(actualCountAfterRemove, 2);
	EXPECT_EQ(node_1->nextNode, node_3);
	EXPECT_EQ(node_3->prevNode, node_1);
}

TYPED_TEST(DoublyLinkedListTests, Remove_throws_exception_on_empty_linkedList)
{
	EXPECT_THROW(_sut.Remove(1), out_of_range);
}

TYPED_TEST(DoublyLinkedListTests, Clear_removes_all_items)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(3);

	int actualCountBeforeClear = _sut.Count();

	_sut.Clear();

	int actualCountAfterClear = _sut.Count();

	EXPECT_EQ(actualCountBeforeClear, 3);
	EXPECT_EQ(actualCountAfterClear, 0);
	EXPECT_TRUE(_sut.IsEmpty());
	EXPECT_THROW(_sut.First(), out_of_range);
	EXPECT_THROW(_sut.Last(), out_of_range);
}
