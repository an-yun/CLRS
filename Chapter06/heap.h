#pragma once
#include<iostream>
#include<vector>
#include<initializer_list>
using namespace std;
template<class T, unsigned N> class heap;
template <class T, unsigned N>  ostream& operator<<(ostream& out,heap<T,N> &h);
template<class T, unsigned N> istream& operator>>(istream& in, heap<T,N> &h);
template<class T, unsigned N>
class heap
{
	friend ostream& operator<<<T, N>(ostream& out, heap<T, N>& h);
	friend istream& operator>><T, N>(istream& in, heap<T, N>& h);
public:
	heap() :A(N), size(N), heapSize(0){}
	heap(initializer_list<T> contents) :size(N), heapSize(0), A(contents) {  }
	~heap() {}
	unsigned heap_size() { return heapSize; }
	void bulid_max_heap();
	void bulid_min_heap();
	void heapsort();
	void heapsort_reverse();
	const unsigned size;
	T heap_maxmum();
	T heap_minmum();
	T heap_extract_max();
	T heap_extract_min();
	void heap_increase_key(unsigned i, T key);
	void heap_decrease_key(unsigned i, T key);
	void max_heap_insert(T key);
	void min_heap_insert(T key);
	bool empty() { return heapSize == 0; }
protected:
	vector<T> A;
	T &operator[](unsigned index);
	void max_heapify(unsigned i);
	void min_heapify(unsigned i);
private:
	unsigned heapSize;
	unsigned parent(unsigned index);
	unsigned left(unsigned index);
	unsigned right(unsigned index);
	void swap(unsigned i, unsigned j);
};

template<class T, unsigned N>
inline T & heap<T, N>::operator[](unsigned index)
{
	return A[index];
}

template<class T, unsigned N>
inline unsigned heap<T, N>::parent(unsigned index)
{
	return (index - 1) / 2;
}

template<class T, unsigned N>
inline unsigned heap<T, N>::left(unsigned index)
{
	return index * 2 + 1;
}

template<class T, unsigned N>
inline unsigned heap<T, N>::right(unsigned index)
{
	return index * 2 + 2;
}

template<class T, unsigned N>
inline void heap<T, N>::max_heapify(unsigned i)
{
	unsigned largest = i, l = 0, r = 0;
	while (true)
	{
		l = left(i);
		r = right(i);
		if (l<heap_size() && A[i]<A[l])
			largest = l;
		if (r<heap_size() && A[largest]<A[r])
			largest = r;
		if (largest == i)break;
		else
		{
			swap(i, largest);
			i = largest;
		}
	}
}

template<class T, unsigned N>
inline void heap<T, N>::min_heapify(unsigned i)
{
	unsigned smallest = i, l = 0, r = 0;
	while (true)
	{
		l = left(i);
		r = right(i);
		if (l<heap_size() && A[l]<A[i])
			smallest = l;
		if (r<heap_size() && A[r]<A[smallest])
			smallest = r;
		if (smallest == i)break;
		else
		{
			swap(i, smallest);
			i = smallest;
		}
	}
}

template<class T, unsigned N>
inline void heap<T, N>::swap(unsigned i, unsigned j)
{
	T temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

template<class T, unsigned N>
inline T heap<T, N>::heap_maxmum()
{
	return A[0];
}

template<class T, unsigned N>
inline T heap<T, N>::heap_minmum()
{
	return A[0];
}

template<class T, unsigned N>
inline T heap<T, N>::heap_extract_max()
{
	if (heapSize < 1)
	{
		cout << "heap underflow!" << endl;
		return T();
	}
	T max = A[0];
	A[0] = A[--heapSize];
	max_heapify(0);
	return max;
}

template<class T, unsigned N>
inline T heap<T, N>::heap_extract_min()
{
	if (heapSize < 1)
	{
		cout << "heap underflow!" << endl;
		return T();
	}
	T min = A[0];
	A[0] = A[--heapSize];
	min_heapify(0);
	return min;
}

template<class T, unsigned N>
inline void heap<T, N>::heap_increase_key(unsigned i, T key)
{
	if (key < A[i])
	{
		cout << "new key is smaller that current key" << endl;
		return;
	}
	A[i] = key;
	while (i > 0 && A[parent(i)] < A[i])
	{
		swap(i, parent(i));
		i = parent(i);
	}
}

template<class T, unsigned N>
inline void heap<T, N>::heap_decrease_key(unsigned i, T key)
{
	if (A[i]<key)
	{
		cout << "new key is larger that current key" << endl;
		return;
	}
	A[i] = key;
	while (i > 0 && A[parent(i)] > A[i])
	{
		swap(i, parent(i));
		i = parent(i);
	}
}

template<class T, unsigned N>
inline void heap<T, N>::max_heap_insert(T key)
{
	if (heapSize == size)
	{
		cout << "the heap is full";
		return;
	}
	A[heapSize++] = key;
	heap_increase_key(heapSize - 1, key);
}

template<class T, unsigned N>
inline void heap<T, N>::min_heap_insert(T key)
{
	if (heapSize == size)
	{
		cout << "the heap is full";
		return;
	}
	A[heapSize++] = key;
	heap_decrease_key(heapSize - 1, key);
}

template<class T, unsigned N> ostream& operator<<(ostream& out, heap<T, N>& h)
{
	for (T &t : h.A) out << t << " ";
	return out;
}
template<class T, unsigned N> istream& operator>>(istream& in, heap<T, N>& h)
{
	for (T &t : h.A)in >> t;
	return in;
}

template<class T, unsigned N>
inline void heap<T, N>::bulid_max_heap()
{
	heapSize = heapSize==0?size:heapSize;
	for (int i = (heapSize -1) / 2; i >= 0; i--)
		max_heapify(i);
}

template<class T, unsigned N>
inline void heap<T, N>::bulid_min_heap()
{
	heapSize = heapSize == 0 ? size : heapSize;
	for (int i = (heapSize -1) / 2; i >= 0; i--)
		min_heapify(i);
}

template<class T, unsigned N>
inline void heap<T, N>::heapsort()
{
	bulid_max_heap();
	for (int i = size - 1; i > 0; i--)
	{
		swap(0, i);
		heapSize--;
		max_heapify(0);
	}
	heapSize = 0;
}

template<class T, unsigned N>
inline void heap<T, N>::heapsort_reverse()
{
	bulid_min_heap();
	for (int i = size - 1; i > 0; i--)
	{
		swap(0, i);
		heapSize--;
		min_heapify(0);
	}
	heapSize = 0;
}
