#include "pch.h"
#include "List.h"
#include <stdexcept>

List::List()
{
	_count = 0;
	_size = 10;
	_items = new int[_size];
}


List::~List()
{
	delete[] _items;
}

int List::Count()
{
	return _count;
}

int List::Size()
{
	return _size;
}

bool List::IsEmpty()
{
	return _count == 0;
}

void List::PushBack(int item)
{
	Insert(_count, item);
}

void List::PushFront(int item)
{
	Insert(0, item);
}

void List::Insert(int index, int item)
{
	if (index < 0 || index > _count)
		throw std::out_of_range("index out of range");

	if (_count == _size)
		expandArray();

	for (auto i = _count - 1; i >= index; i--)
		_items[i + 1] = _items[i];

	_items[index] = item;

	_count++;
}

int List::PopBack()
{
	return Erase(_count - 1);
}

int List::PopFront()
{
	return Erase(0);
}

int List::Erase(int index)
{
	if (index < 0 || index >= _count)
		throw std::out_of_range("index out of range");

	int result = _items[index];

	for (auto i = index; i < _count - 1; i++)
		_items[i] = _items[i + 1];
	
	_count--;

	return result;
}

void List::Remove(int item)
{
	int itemIndex = -1;
	for (auto i = 0; i < _count; i++)
		if (_items[i] == item)
			itemIndex = i;

	if (itemIndex > 0)
		Erase(itemIndex);
}

void List::Clear()
{
	_count = 0;
}

int List::First()
{
	return _items[0];
}

int List::Last()
{
	return _items[_count - 1];
}

int List::operator[] (int index)
{
	if (index < 0 || index >= _count)
		throw std::out_of_range("index out of range");

	return _items[index];
}

void List::expandArray()
{
	_size *= 2;
	int* biggerItems = new int[_size];

	for (auto i = 0; i < _count; i++)
		biggerItems[i] = _items[i];

	delete[] _items;
	_items = biggerItems;
}
