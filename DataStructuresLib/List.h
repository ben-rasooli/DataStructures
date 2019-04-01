#pragma once

class List
{
public:
	List();
	~List();

	int Count();
	int Size();

	bool IsEmpty();
	void PushBack(int item);
	void PushFront(int item);
	void Insert(int index, int item);
	int PopBack();
	int PopFront();
	int Erase(int index);
	void Remove(int item);
	void Clear();
	int First();
	int Last();

	int operator[](int index);

private:
	int _count;
	int _size;
	int* _items;

	void expandArray();
};

