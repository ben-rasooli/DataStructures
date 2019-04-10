#pragma once
#include "BinaryTreeNode.h"

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	int Count();

	bool IsEmpty();
	void Insert(int value);
	BinaryTreeNode* Find(int value);
	void Remove(int value);

private:
	int _count;
	BinaryTreeNode* _rootNode;

	BinaryTreeNode* find(int value, BinaryTreeNode* node);
	void remove(BinaryTreeNode* node);
	void removeLeafNode(BinaryTreeNode* node);
	void removeSingleSubnodedNode(BinaryTreeNode* node);
	void removeDoubleSubnodedNode(BinaryTreeNode* node);
};

