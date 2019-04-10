#include "pch.h"
#include "DoublyLinkedList.h"
#include <stdexcept>


DoublyLinkedList::DoublyLinkedList()
{
	_count = 0;

	_head = new LinkedListNode();
	_tail = new LinkedListNode();

	_head->prevItem = nullptr;
	_head->nextItem = _tail;

	_tail->prevItem = _head;
	_tail->nextItem = nullptr;
}


DoublyLinkedList::~DoublyLinkedList()
{
}

int DoublyLinkedList::Count()
{
	return _count;
}

bool DoublyLinkedList::IsEmpty()
{
	return _count == 0;
}

void DoublyLinkedList::PushBack(int item)
{
	insert(_tail->prevItem, _tail, item);

	_count++;
}

void DoublyLinkedList::PushFront(int item)
{
	insert(_head, _head->nextItem, item);

	_count++;
}

void DoublyLinkedList::PushAfter(LinkedListNode node, int item)
{
}

void DoublyLinkedList::PushBefore(LinkedListNode node, int item)
{
}

int DoublyLinkedList::First()
{
	if (_count == 0)
		throw std::out_of_range("index out of range");

	return _head->nextItem->Value;
}

int DoublyLinkedList::Last()
{
	if (_count == 0)
		throw std::out_of_range("index out of range");

	return _tail->prevItem->Value;
}

LinkedListNode* DoublyLinkedList::Find(int item)
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

void DoublyLinkedList::insert(LinkedListNode *leftNode, LinkedListNode *rightNode, int item)
{
	auto pushedItem = new LinkedListNode();
	pushedItem->Value = item;
	pushedItem->prevItem = leftNode;
	pushedItem->nextItem = rightNode;

	leftNode->nextItem = pushedItem;
	rightNode->prevItem = pushedItem;	
}
