#include "pch.h"

using namespace std;

template<typename T>
class HeapTests : public testing::Test
{
protected:
	Heap<int> _sut;
};

using MyTypes = testing::Types< int >;
TYPED_TEST_CASE(HeapTests, MyTypes);

TYPED_TEST(HeapTests, a_new_heap_has_zero_count_and_is_empty)
{
	int actualCount = _sut.Count();
	bool actualIsEmpty = _sut.IsEmpty();

	EXPECT_EQ(actualCount, 0);
	EXPECT_TRUE(actualIsEmpty);
}

TYPED_TEST(HeapTests, a_new_heap_has_fo_count_and_is_empty)
{
	_sut.Insert(5);
	_sut.Insert(3);

	//EXPECT_EQ(actualCount, 0);
	//EXPECT_TRUE(actualIsEmpty);
}