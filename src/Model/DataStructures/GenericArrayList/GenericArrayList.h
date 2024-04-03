#pragma once
#ifndef GENERIC_ARRAY_LIST_H
#define GENERIC_ARRAY_LIST_H

#include <cstdint>
#include <vector>

// Cells are NOT deleted until the destructor is called.

template <typename T>
struct GenericArrayList
{
	int maxSize;
	int currSize;

	std::vector<T> m_SHGItems;

	GenericArrayList(int _maxSize) : maxSize(_maxSize)
	{
	}

	~GenericArrayList() = default;

	void Insert(T _item)
	{

	}

	void Remove(T _item)
	{

	}




	std::vector<T> GetItems();
};


#endif