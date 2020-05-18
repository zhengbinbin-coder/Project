#pragma once
#include<malloc.h>

template<class T, size_t initNum = 100>
class ObjectPool
{
public:
	ObjectPool()
	{
		_start = _end = (char*)malloc(initNum*sizeof(T));
	}

	//T* Alloc()
	T* New()
	{
		if (_start == _end)
		{
			_start = _end = (char*)malloc(initNum*sizeof(T));
		}
		T* obj = (T*)_start;
		_start += sizeof(T);

		//new的定位表达式
		new(obj)T;
		
		return obj;
	}

	void Delete(T* ptr)
	{
		ptr->~T();
		*(int*)ptr = _freeList;
		_freeList = ptr;
	}

	~ObjectPool();

private:
	char* _start;
	char* _end;		//管理内存池指针

	T* _freeList;
};