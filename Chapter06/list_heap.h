#pragma once
#include<list>
#include "heap.h"
template <class T,unsigned N>
class list_heap:public heap<list<T>,N>
{
private:
	unsigned length;
public:
	list_heap() :heap() {}
	list_heap(initializer_list<list<T>> contents) :heap(contents)
	{
		length = 0;
		for (auto &l : A)length += l.size();
	}
	T increase_top()
	{
		T result = *A[0].begin();
		A[0].pop_front();
		length--;
		return result;
	}
	void min_heapify() { heap<list<T>, N>::min_heapify(0); }
	bool empty() { return length == 0; }
};
template<class T>
bool operator<(const list<T> &l1, const list<T> &l2)
{
	if (l1.empty())return false;
	else if (l2.empty())return true;
	else return (*l1.cbegin()) < (*l2.cbegin());
}