#ifndef _B_ARRAY_H_
#define _B_ARRAY_H_

#include <cstdlib>
#include <cassert>

template<class ArrayType>
class bArray
{
public:
	bArray();
	bArray(size_t _size);
	bArray(const bArray &_array);

	~bArray();

	ArrayType &operator [](size_t _index);

	void Push(const ArrayType &_item);

	void Clear();

	size_t Size();

	void Resize(size_t _size);

private:
	ArrayType *data;
	size_t     size;
	size_t     pos;

	static const int min_alloc = 32;

	void Alloc(size_t _size);
};

template <typename ArrayType>
bArray<ArrayType>::bArray()
{
	data = 0;
	size = 0;
	pos  = 0;
}

template <typename ArrayType>
bArray<ArrayType>::bArray(size_t _size)
{
	data = (ArrayType *)malloc(sizeof(ArrayType) * _size);
	size = _size;
	pos  = 0;
}

template <typename ArrayType>
bArray<ArrayType>::bArray(const bArray &_array)
{
	free(data);

	size = _array.size;
	pos = _array.pos;

	data = (ArrayType *)malloc(sizeof(ArrayType) * size);
	memcpy(data, _array.data, pos);
}

template <typename ArrayType>
bArray<ArrayType>::~bArray()
{
	free(data);
}

template <typename ArrayType>
ArrayType &bArray<ArrayType>::operator [](size_t _index)
{
	assert(_index < pos);

	return data[_index];
}

template <typename ArrayType>
void bArray<ArrayType>::Push(const ArrayType &_item)
{
	if(size == pos)
		Alloc(size + size / 2);

	data[pos] = _item;
	pos++;
}

template <typename ArrayType>
void bArray<ArrayType>::Clear()
{
	pos = 0;
}

template <typename ArrayType>
size_t bArray<ArrayType>::Size()
{
	return pos;
}

template <typename ArrayType>
void bArray<ArrayType>::Resize(size_t _size)
{
	assert(size < _size);

	Alloc(_size);
}

template <typename ArrayType>
void bArray<ArrayType>::Alloc(size_t _size)
{
	if(!_size)
		_size = min_alloc;

	ArrayType *new_data = (ArrayType *)malloc(sizeof(ArrayType) * _size);

	memcpy(new_data, data, sizeof(ArrayType) * size);

	free(data);

	data = new_data;
	size = _size;
}

#endif