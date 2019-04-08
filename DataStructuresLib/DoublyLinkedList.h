#pragma once
#include "LinkedListNode.h"

class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();

	int Count();

	bool IsEmpty();
	void PushBack(int item);
	void PushFront(int item);
	void PushAfter(LinkedListNode node, int item);
	void PushBefore(LinkedListNode node, int item);
	int First();
	int Last();
	LinkedListNode* Find(int item);

private:
	int _count;
	LinkedListNode* _head;
	LinkedListNode* _tail;
	void insert(LinkedListNode *leftNode, LinkedListNode *rightNode, int item);
};

