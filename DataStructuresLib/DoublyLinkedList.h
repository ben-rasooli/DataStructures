#pragma once
#include <stdexcept>
#include "pch.h"
#include "LinkedListNode.h"

template <typename T>
class DoublyLinkedList
{
public:
	DoublyLinkedList()
	{
		_count = 0;

		_head = new LinkedListNode();
		_tail = new LinkedListNode();

		_head->prevItem = nullptr;
		_head->nextItem = _tail;

		_tail->prevItem = _head;
		_tail->nextItem = nullptr;
	}

	~DoublyLinkedList()
	{

	}

	int Count()
	{
		return _count;
	}

	bool IsEmpty()
	{
		return _count == 0;
	}

	void PushBack(int item)
	{
		insert(_tail->prevItem, _tail, item);

		_count++;
	}

	void PushFront(int item)
	{
		insert(_head, _head->nextItem, item);

		_count++;
	}

	void PushAfter(LinkedListNode node, T item)
	{

	}

	void PushBefore(LinkedListNode node, T item)
	{

	}

	int First()
	{
		if (_count == 0)
			throw std::out_of_range("index out of range");

		return _head->nextItem->Value;
	}

	int Last()
	{
		if (_count == 0)
			throw std::out_of_range("index out of range");

		return _tail->prevItem->Value;
	}

	LinkedListNode* Find(int item)
	{
		if (_count == 0)
			throw std::out_of_range("Can't find on empty collection");

		LinkedListNode* currentNode = _head->nextItem;
		while (currentNode->nextItem != _tail)
		{
			if (currentNode->Value == item)
				return currentNode;

			currentNode = currentNode->nextItem;
		}

		return nullptr;
	}

private:
	int _count;
	LinkedListNode* _head;
	LinkedListNode* _tail;
	
	void insert(LinkedListNode *leftNode, LinkedListNode *rightNode, int item)
	{
		auto pushedItem = new LinkedListNode();
		pushedItem->Value = item;
		pushedItem->prevItem = leftNode;
		pushedItem->nextItem = rightNode;

		leftNode->nextItem = pushedItem;
		rightNode->prevItem = pushedItem;
	}
};
