#pragma once
#include "pch.h"
#include <stdexcept>
#include <sstream>

using namespace std;

template <typename T>
class List
{
public:
	List()
	{
		_count = 0;
		_size = 10;
		_items = new int[_size];
	}

	~List()
	{
		delete[] _items;
	}

	
	int Count()
	{
		return _count;
	}

	
	int Size()
	{
		return _size;
	}

	
	bool IsEmpty()
	{
		return _count == 0;
	}

	
	void PushBack(T item)
	{
		Insert(_count, item);
	}

	
	void PushFront(T item)
	{
		Insert(0, item);
	}

	
	void Insert(int index, T item)
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

	
	T PopBack()
	{
		return Erase(_count - 1);
	}

	
	T PopFront()
	{
		return Erase(0);
	}

	
	T Erase(int index)
	{
		if (index < 0 || index >= _count)
			throw std::out_of_range("index out of range");

		int result = _items[index];

		for (auto i = index; i < _count - 1; i++)
			_items[i] = _items[i + 1];

		_count--;

		return result;
	}

	
	void Remove(T item)
	{
		int itemIndex = -1;
		for (auto i = 0; i < _count; i++)
			if (_items[i] == item)
				itemIndex = i;

		if (itemIndex > 0)
			Erase(itemIndex);
	}

	
	void Clear()
	{
		_count = 0;
	}

	
	T First()
	{
		return _items[0];
	}

	
	T Last()
	{
		return _items[_count - 1];
	}

	
	T operator[] (int index)
	{
		if (index < 0 || index >= _count)
			throw std::out_of_range("index out of range");

		return _items[index];
	}

	string ToString()
	{
		stringstream result;
		for (int i = 0; i < _count - 1; i++)
		{
			string item = to_string(_items[i]) + ",";
			result << item;
		}

		result << _items[_count - 1];

		return result.str();
	}

private:
	int _count;
	int _size;
	T* _items;

	void expandArray()
	{
		_size *= 2;
		int* biggerItems = new int[_size];

		for (auto i = 0; i < _count; i++)
			biggerItems[i] = _items[i];

		delete[] _items;
		_items = biggerItems;
	}
};
