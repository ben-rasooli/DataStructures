#include "pch.h"
#include <stdexcept>
#include "../DataStructuresLib/BinaryTree.h"
#include "../DataStructuresLib/BinaryTreeNode.h"

using namespace std;

class BinaryTreeTests : public testing::Test
{
protected:
	BinaryTree _sut;
	void insertSampleValues()
	{
		_sut.Insert(5);
		_sut.Insert(3);
		_sut.Insert(1);
		_sut.Insert(4);
		_sut.Insert(7);
		_sut.Insert(8);
		//      5
		//	  /   \
		//	 3     7
		//	/ \     \
		// 1   4     8
	}
};

TEST_F(BinaryTreeTests, a_new_binaryTree_has_zero_count_and_is_empty)
{
	int actualCount = _sut.Count();
	bool actualIfEmpty = _sut.IsEmpty();

	EXPECT_EQ(actualCount, 0);
	EXPECT_TRUE(actualIfEmpty);
}

TEST_F(BinaryTreeTests, a_binaryTree_becomes_non_empty_when_inserting_new_value)
{
	_sut.Insert(1);

	bool actualIfEmpty = _sut.IsEmpty();

	EXPECT_FALSE(actualIfEmpty);
}

TEST_F(BinaryTreeTests, Insert_inserts_smaller_values_to_the_left_subnode_and_biggers_to_the_right_one)
{
	insertSampleValues();

	//      5
	//	  /   \
	//	 3     7
	//	/ \     \
	// 1   4     8

	BinaryTreeNode* actualnode_5 = _sut.Find(5);
	BinaryTreeNode* actualnode_3 = _sut.Find(3);
	BinaryTreeNode* actualnode_1 = _sut.Find(1);
	BinaryTreeNode* actualnode_4 = _sut.Find(4);
	BinaryTreeNode* actualnode_7 = _sut.Find(7);
	BinaryTreeNode* actualnode_8 = _sut.Find(8);

	//check rootnode
	EXPECT_TRUE(actualnode_5->supernode == nullptr);

	//check nodes existance
	EXPECT_EQ(actualnode_5->Value, 5);
	EXPECT_EQ(actualnode_3->Value, 3);
	EXPECT_EQ(actualnode_1->Value, 1);
	EXPECT_EQ(actualnode_4->Value, 4);
	EXPECT_EQ(actualnode_7->Value, 7);
	EXPECT_EQ(actualnode_8->Value, 8);

	//check supernodes
	EXPECT_EQ(actualnode_3->supernode, actualnode_5);
	EXPECT_EQ(actualnode_7->supernode, actualnode_5);

	EXPECT_EQ(actualnode_1->supernode, actualnode_3);
	EXPECT_EQ(actualnode_4->supernode, actualnode_3);

	EXPECT_EQ(actualnode_8->supernode, actualnode_7);

	//check subnodes
	EXPECT_EQ(actualnode_5->leftSubnode, actualnode_3);
	EXPECT_EQ(actualnode_5->rightSubnode, actualnode_7);

	EXPECT_EQ(actualnode_3->leftSubnode, actualnode_1);
	EXPECT_EQ(actualnode_3->rightSubnode, actualnode_4);

	EXPECT_EQ(actualnode_7->rightSubnode, actualnode_8);
}

TEST_F(BinaryTreeTests, Find_throws_exception_on_empty_binaryTree)
{
	EXPECT_THROW(_sut.Find(1), out_of_range);
}

TEST_F(BinaryTreeTests, Count_is_incremented_when_inserting_a_value)
{
	_sut.Insert(1);
	_sut.Insert(2);
	_sut.Insert(3);
	int actualCountAfterInserting = _sut.Count();

	EXPECT_EQ(actualCountAfterInserting, 3);
}

TEST_F(BinaryTreeTests, inserting_a_duplicated_value_is_ignored)
{
	_sut.Insert(1);
	_sut.Insert(2);
	_sut.Insert(1);

	BinaryTreeNode* actualnode_1 = _sut.Find(1);
	BinaryTreeNode* actualnode_2 = _sut.Find(2);

	int actualCountAfterInserting = _sut.Count();

	EXPECT_EQ(actualCountAfterInserting, 2);
	EXPECT_TRUE(actualnode_1->leftSubnode == nullptr);
	EXPECT_TRUE(actualnode_2->leftSubnode == nullptr);
	EXPECT_TRUE(actualnode_2->rightSubnode == nullptr);
}

TEST_F(BinaryTreeTests, Count_is_decremented_when_removing_a_value)
{
	insertSampleValues();

	int actualCountBeforeRemoving = _sut.Count();
	_sut.Remove(8);
	int actualCountAfterRemoving = _sut.Count();

	EXPECT_EQ(actualCountBeforeRemoving, 6);
	EXPECT_EQ(actualCountAfterRemoving, actualCountBeforeRemoving - 1);
}

TEST_F(BinaryTreeTests, removing_a_leafNode_does_not_restructure_the_binaryTree)
{
	insertSampleValues();

	//      5
	//	  /   \
	//	 3     7
	//	/ \     \
	// 1   4    (8)

	_sut.Remove(8);

	//      5
	//	  /   \
	//	 3     7
	//	/ \     
	// 1   4     
	BinaryTreeNode* actualNode_7 = _sut.Find(7);

	EXPECT_EQ(actualNode_7->supernode->Value, 5);
	EXPECT_EQ(actualNode_7->supernode->leftSubnode->Value, 3);
	EXPECT_TRUE(actualNode_7->rightSubnode == nullptr);

}

TEST_F(BinaryTreeTests, removing_a_singleSubnodedNode_connects_its_supernode_to_its_subnode)
{
	insertSampleValues();

	//      5
	//	  /   \
	//	 3    (7)
	//	/ \     \
	// 1   4     8

	_sut.Remove(7);

	//      5
	//	  /   \
	//	 3     8
	//	/ \     
	// 1   4     

	BinaryTreeNode* actualNode_5 = _sut.Find(5);
	BinaryTreeNode* actualNode_8 = _sut.Find(8);
	EXPECT_EQ(actualNode_5->rightSubnode, actualNode_8);
	EXPECT_EQ(actualNode_8->supernode, actualNode_5);
}

TEST_F(BinaryTreeTests, removing_a_doubleSubnodedNode_only_reassigns_its_value_with_a_similar_node)
{
	insertSampleValues();

	//     (5)
	//	  /   \
	//	 3     7
	//	/ \     \
	// 1   4     8

	_sut.Remove(5);

	//      7
	//	  /   \
	//	 3     8
	//	/ \     
	// 1   4        

	BinaryTreeNode* actualNode_5 = _sut.Find(5);
	BinaryTreeNode* actualNode_3 = _sut.Find(3);
	BinaryTreeNode* actualNode_7 = _sut.Find(7);
	BinaryTreeNode* actualNode_8 = _sut.Find(8);

	EXPECT_TRUE(actualNode_5 == nullptr);
	EXPECT_TRUE(actualNode_7->supernode == nullptr);

	EXPECT_EQ(actualNode_3->supernode, actualNode_7);
	EXPECT_EQ(actualNode_8->supernode, actualNode_7);

	EXPECT_EQ(actualNode_7->leftSubnode, actualNode_3);
	EXPECT_EQ(actualNode_7->rightSubnode, actualNode_8);

}

TEST_F(BinaryTreeTests, passing_test)
{
	EXPECT_TRUE(true);
}
