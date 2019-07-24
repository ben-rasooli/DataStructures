#include "pch.h"

using namespace std;

template<typename T>
class StackTests : public testing::Test
{
protected:
	Stack<int> _sut;
};

using MyTypes = testing::Types< int >;
TYPED_TEST_CASE(StackTests, MyTypes);

TYPED_TEST(StackTests, a_new_stack_has_zero_count_and_is_empty)
{
	int actualCount = _sut.Count();
	bool actualIfEmpty = _sut.IsEmpty();

	EXPECT_EQ(actualCount, 0);
	EXPECT_TRUE(actualIfEmpty);
}

TYPED_TEST(StackTests, Peak_throws_exception_on_empty_stack)
{
	EXPECT_THROW(_sut.Peak(), out_of_range);
}

TYPED_TEST(StackTests, Peak_returns_the_top_item_on_stack)
{
	_sut.Push(1);

	int actualTopItem = _sut.Peak();

	EXPECT_EQ(actualTopItem, 1);
}

TYPED_TEST(StackTests, Push_adds_item_at_the_top_of_stack)
{
	_sut.Push(1);
	_sut.Push(2);

	int actualTopItem = _sut.Peak();

	EXPECT_EQ(actualTopItem, 2);

	_sut.Push(3);

	actualTopItem = _sut.Peak();

	EXPECT_EQ(actualTopItem, 3);
}

TYPED_TEST(StackTests, Pop_removes_the_top_item_and_returns_it)
{
	_sut.Push(1);
	_sut.Push(2);
	_sut.Push(3);

	int actualTopItemBeforePop = _sut.Peak();
	int actualPopedItem = _sut.Pop();
	int actualTopItemAfterPop = _sut.Peak();

	EXPECT_EQ(actualTopItemBeforePop, 3);
	EXPECT_EQ(actualPopedItem, 3);
	EXPECT_EQ(actualTopItemAfterPop, 2);
}

TYPED_TEST(StackTests, Clear_removes_all_items)
{
	_sut.Push(1);
	_sut.Push(2);
	_sut.Push(3);

	int actualCountBeforeClear = _sut.Count();
	_sut.Clear();
	int actualCountAfterClear = _sut.Count();

	EXPECT_EQ(actualCountBeforeClear, 3);
	EXPECT_EQ(actualCountAfterClear, 0);
	EXPECT_TRUE(_sut.IsEmpty());
	EXPECT_THROW(_sut.Peak(), out_of_range);
}
