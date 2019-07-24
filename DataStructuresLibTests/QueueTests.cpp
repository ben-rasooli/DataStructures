#include "pch.h"

using namespace std;

template<typename T>
class QueueTests : public testing::Test
{
protected:
	Queue<int> _sut;
};

using MyTypes = testing::Types< int >;
TYPED_TEST_CASE(QueueTests, MyTypes);

TYPED_TEST(QueueTests, a_new_queue_has_zero_count_and_is_empty)
{
	int actualCount = _sut.Count();
	bool actualIfEmpty = _sut.IsEmpty();

	EXPECT_EQ(actualCount, 0);
	EXPECT_TRUE(actualIfEmpty);
}

TYPED_TEST(QueueTests, Peak_throws_exception_on_empty_queue)
{
	EXPECT_THROW(_sut.Peak(), out_of_range);
}

TYPED_TEST(QueueTests, Peak_returns_the_top_item_on_queue)
{
	_sut.Enqueue(1);

	int actualTopItem = _sut.Peak();

	EXPECT_EQ(actualTopItem, 1);
}

TYPED_TEST(QueueTests, Enqueue_adds_item_at_the_bottom_of_queue)
{
	_sut.Enqueue(1);
	_sut.Enqueue(2);

	int actualTopItem = _sut.Peak();

	EXPECT_EQ(actualTopItem, 1);

	_sut.Enqueue(3);

	actualTopItem = _sut.Peak();

	EXPECT_EQ(actualTopItem, 1);
}

TYPED_TEST(QueueTests, Dequeue_removes_the_top_item_and_returns_it)
{
	_sut.Enqueue(1);
	_sut.Enqueue(2);
	_sut.Enqueue(3);
	_sut.Enqueue(4);

	int actualTopItemBeforeDequeue = _sut.Peak();
	int actualDequeueItem = _sut.Dequeue();
	int actualTopItemAfterDequeue = _sut.Peak();

	EXPECT_EQ(actualTopItemBeforeDequeue, 1);
	EXPECT_EQ(actualDequeueItem, 1);
	EXPECT_EQ(actualTopItemAfterDequeue, 2);
}

TYPED_TEST(QueueTests, Clear_removes_all_items)
{
	_sut.Enqueue(1);
	_sut.Enqueue(2);
	_sut.Enqueue(3);

	int actualCountBeforeClear = _sut.Count();
	_sut.Clear();
	int actualCountAfterClear = _sut.Count();

	EXPECT_EQ(actualCountBeforeClear, 3);
	EXPECT_EQ(actualCountAfterClear, 0);
	EXPECT_TRUE(_sut.IsEmpty());
	EXPECT_THROW(_sut.Peak(), out_of_range);
}
