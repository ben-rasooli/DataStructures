#include "pch.h"
#include "../DataStructuresLib/List.h"
#include <stdexcept>

using namespace std;

class ListTests : public testing::Test
{
protected:
	List _list;
};

TEST_F(ListTests, a_new_list_has_zero_count_and_is_empty)
{
	int actualCount = _list.Count();
	bool actualIfEmpty = _list.IsEmpty();

	EXPECT_EQ(actualCount, 0);
	EXPECT_TRUE(actualIfEmpty);

}

TEST_F(ListTests, a_list_becomes_non_empty_when_pushing_new_items)
{
	_list.PushBack(1);

	bool actualIfEmpty = _list.IsEmpty();

	EXPECT_FALSE(actualIfEmpty);
}


TEST_F(ListTests, a_list_becomes_empty_if_no_item_left_in_it)
{
	_list.PushBack(1);
	_list.PushBack(1);
	_list.PushBack(1);

	_list.PopFront();
	_list.PopBack();
	_list.PopBack();

	bool actualIfEmpty = _list.IsEmpty();

	EXPECT_TRUE(actualIfEmpty);
}

TEST_F(ListTests, Count_is_incremented_when_pushing_an_item)
{
	_list.PushBack(1);
	_list.PushBack(1);
	int actualCountAfterPush = _list.Count();

	EXPECT_EQ(actualCountAfterPush, 2);

	_list.PushFront(1);
	_list.PushFront(1);
	actualCountAfterPush = _list.Count();

	EXPECT_EQ(actualCountAfterPush, 4);
}

TEST_F(ListTests, a_new_list_has_non_zero_size)
{
	int actualSize = _list.Size();

	EXPECT_NE(actualSize, 0);
}

TEST_F(ListTests, Size_is_increased_when_not_enough_space_to_push_a_new_item)
{
	int initialSize = _list.Size();

	for (auto i = 0; i < initialSize + 1; i++)
		_list.PushBack(i);

	int actualSizeAfterPush = _list.Size();

	EXPECT_NE(actualSizeAfterPush, initialSize);
	for (auto i = 0; i < _list.Count(); i++)
		EXPECT_EQ(_list[i], i);

	initialSize = _list.Size();

	for (auto i = 0; i < initialSize + 1; i++)
		_list.PushFront(1);

	actualSizeAfterPush = _list.Size();

	EXPECT_NE(actualSizeAfterPush, initialSize);
}

TEST_F(ListTests, Size_is_increased_when_not_enough_space_to_insert_a_new_item)
{
	int initialSize = _list.Size();

	for (auto i = 0; i < initialSize; i++)
		_list.PushBack(i);

	int insertionIndex = 5;
	_list.Insert(insertionIndex,0);

	int actualSizeAfterPush = _list.Size();

	EXPECT_NE(actualSizeAfterPush, initialSize);
	for (auto i = 0; i < _list.Count(); i++)
	{
		if (i < insertionIndex)
			EXPECT_EQ(_list[i], i);
		else if (i > insertionIndex)
			EXPECT_EQ(_list[i], i - 1);
		else
			EXPECT_EQ(_list[i], 0);
	}
}

TEST_F(ListTests, accessing_out_of_range_index_throws_exception)
{
	EXPECT_THROW(_list[1], out_of_range);
	EXPECT_THROW(_list[0], out_of_range);
	EXPECT_THROW(_list[-1], out_of_range);
}

TEST_F(ListTests, PushBack_add_the_item_to_end_of_the_list)
{
	int item_1 = 1;
	int item_2 = 2;

	_list.PushBack(item_1);
	_list.PushBack(item_2);

	int actualCount = _list.Count();
	int lastIndex = actualCount - 1;
	int actualLastItem = _list[lastIndex];

	EXPECT_EQ(actualCount, 2);
	EXPECT_EQ(actualLastItem, item_2);
}

TEST_F(ListTests, PushFront_add_the_item_to_start_of_the_list)
{
	int item_1 = 1;
	int item_2 = 2;

	_list.PushFront(item_1);
	_list.PushFront(item_2);

	int actualFirstItem = _list[0];
	int actualSecondItem = _list[1];

	EXPECT_EQ(actualFirstItem, item_2);
	EXPECT_EQ(actualSecondItem, item_1);
}

TEST_F(ListTests, First_returns_the_first_item_in_the_list)
{
	_list.PushBack(1);
	_list.PushBack(2);
	_list.PushBack(3);

	int actualFirstItem = _list.First();

	EXPECT_EQ(actualFirstItem, 1);
}

TEST_F(ListTests, Last_returns_the_last_item_in_the_list)
{
	_list.PushBack(1);
	_list.PushBack(2);
	_list.PushBack(3);

	int actualLastItem = _list.Last();

	EXPECT_EQ(actualLastItem, 3);
}

TEST_F(ListTests, Insert_adds_a_new_item_at_the_specified_index_location)
{
	_list.PushBack(1);
	_list.PushBack(2);
	_list.PushBack(4);

	_list.Insert(2, 3);
	int actualInsertedItem = _list[2];

	EXPECT_EQ(actualInsertedItem, 3);
}

TEST_F(ListTests, Insert_throws_exception_if_passed_out_of_range_index)
{
	EXPECT_THROW(_list.Insert(1, 0), out_of_range);
	EXPECT_THROW(_list.Insert(-1, 0), out_of_range);
}

TEST_F(ListTests, Erase_removes_an_item_by_its_index_and_returns_it_plus_shift_other_items_to_fill_the_gap)
{
	//arrange
	int firstItem = 1;
	int secondItem = 2;
	int thirdItem = 3;

	_list.PushBack(firstItem);
	_list.PushBack(secondItem);
	_list.PushBack(thirdItem);

	//act
	int countBeforeErase = _list.Count();
	int erasingIndex = 1;
	int actualReturnItem = _list.Erase(erasingIndex);
	int actualCountAfterErase = _list.Count();
	int actualShiftedItem = _list[erasingIndex];

	//assert
	EXPECT_EQ(actualCountAfterErase, countBeforeErase - 1);
	EXPECT_EQ(actualReturnItem, secondItem);
	EXPECT_EQ(actualShiftedItem, thirdItem);
}

TEST_F(ListTests, Erase_throws_exception_if_passed_out_of_range_index)
{
	EXPECT_THROW(_list.Erase(1), out_of_range);
	EXPECT_THROW(_list.Erase(0), out_of_range);
	EXPECT_THROW(_list.Erase(-1), out_of_range);
}

TEST_F(ListTests, Remove_removes_an_item_and_shift_other_items_to_fill_the_gap)
{
	//arrange
	int firstItem = 1;
	int itemToBeRemoved = 2;
	int thirdItem = 3;

	_list.PushBack(firstItem);
	_list.PushBack(itemToBeRemoved);
	_list.PushBack(thirdItem);

	//act
	int countBeforeErase = _list.Count();
	_list.Remove(itemToBeRemoved);
	int actualCountAfterErase = _list.Count();
	int actualShiftedItem = _list[1];

	//assert
	EXPECT_EQ(actualCountAfterErase, countBeforeErase - 1);
	EXPECT_EQ(actualShiftedItem, thirdItem);
}

TEST_F(ListTests, PopBack_removes_last_item_and_returns_it)
{
	//arrange
	int firstItem = 1;
	int middleItem = 2;
	int lastItem = 3;

	_list.PushBack(firstItem);
	_list.PushBack(middleItem);
	_list.PushBack(lastItem);

	//act
	int countBeforeErase = _list.Count();
	int actualReturnItem = _list.PopBack();
	int actualCountAfterErase = _list.Count();

	//assert
	EXPECT_EQ(actualCountAfterErase, countBeforeErase - 1);
	EXPECT_EQ(actualReturnItem, lastItem);
}

TEST_F(ListTests, PopFront_removes_first_item_and_returns_it)
{//arrange
	int firstItem = 1;
	int middleItem = 2;
	int lastItem = 3;

	_list.PushBack(firstItem);
	_list.PushBack(middleItem);
	_list.PushBack(lastItem);

	//act
	int countBeforeErase = _list.Count();
	int actualReturnItem = _list.PopFront();
	int actualCountAfterErase = _list.Count();

	//assert
	EXPECT_EQ(actualCountAfterErase, countBeforeErase - 1);
	EXPECT_EQ(actualReturnItem, firstItem);
}

TEST_F(ListTests, Clear_removes_all_items)
{
	_list.PushBack(1);
	_list.PushBack(1);
	_list.PushBack(1);

	bool actualIfEmptyBeforeClear = _list.IsEmpty();
	_list.Clear();
	bool actualIfEmptyAfterClear = _list.IsEmpty();

	EXPECT_FALSE(actualIfEmptyBeforeClear);
	EXPECT_TRUE(actualIfEmptyAfterClear);
	EXPECT_THROW(_list[0], out_of_range);
}
