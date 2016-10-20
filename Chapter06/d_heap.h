#pragma once
#include<iostream>
#include<vector>
#include<initializer_list>
using namespace std;
template<class T, unsigned K, unsigned N> class d_heap;
template<class T, unsigned K, unsigned N> ostream& operator<<(ostream& out, d_heap<T, K, N> &h);
template<class T, unsigned K, unsigned N> istream& operator>>(istream& in, d_heap<T, K, N> &h);
template<class T, unsigned K, unsigned N>
class d_heap
{
	friend ostream& operator<<<T, K, N>(ostream& out, d_heap<T,K, N>& h);
	friend istream& operator>><T, K, N>(istream& in, d_heap<T,K, N>& h);
public:
	d_heap() :A(N), size(N), d_heapSize(0) {}
	d_heap(initializer_list<T> contents) :size(N),d(K), d_heapSize(0), A(contents) {  }
	~d_heap() {}
	unsigned d_heap_size() { return d_heapSize; }
	void bulid_max_d_heap();
	void bulid_min_d_heap();
	void d_heapsort();
	void d_heapsort_reverse();
	const unsigned size;
	const unsigned d;
	T d_heap_maxmum();
	T d_heap_minmum();
	T d_heap_extract_max();
	T d_heap_extract_min();
	void d_heap_increase_key(unsigned i, T key);
	void d_heap_decrease_key(unsigned i, T key);
	void max_d_heap_insert(T key);
	void min_d_heap_insert(T key);
	bool empty() { return d_heapSize == 0; }
protected:
	vector<T> A;
	T &operator[](unsigned index);
	void max_d_heapify(unsigned i);
	void min_d_heapify(unsigned i);
private:
	unsigned d_heapSize;
	unsigned parent(unsigned index);
	unsigned child(unsigned index, unsigned j);
	void swap(unsigned i, unsigned j);
};

template<class T, unsigned K, unsigned N>
inline T & d_heap<T, K, N>::operator[](unsigned index)
{
	return A[index];
}

template<class T, unsigned K, unsigned N>
inline unsigned d_heap<T, K, N>::parent(unsigned index)
{
	return (index - 1) / K;
}

template<class T, unsigned K, unsigned N>
inline unsigned d_heap<T, K, N>::child(unsigned index, unsigned j)
{
	return K*index + j;
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::max_d_heapify(unsigned i)
{
	unsigned largest = i;
	while (true)
	{
		for (int j = 1; j <= K; j++)
			if (child(i, j) < d_heap_size() && A[largest] < A[child(i, j)])
				largest = child(i, j);
		if (largest == i)break;
		else
		{
			swap(i, largest);
			i = largest;
		}
	}
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::min_d_heapify(unsigned i)
{
	unsigned smallest = i;
	while (true)
	{
		for (int j = 1; j <= K; j++)
			if (child(i, j) < d_heap_size() && A[child(i, j)] < A[smallest])
				smallest = child(i, j);
		if (smallest == i)break;
		else
		{
			swap(i, smallest);
			i = smallest;
		}
	}
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::swap(unsigned i, unsigned j)
{
	T temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

template<class T, unsigned K, unsigned N>
inline T d_heap<T, K, N>::d_heap_maxmum()
{
	return A[0];
}

template<class T, unsigned K, unsigned N>
inline T d_heap<T, K, N>::d_heap_minmum()
{
	return A[0];
}

template<class T, unsigned K, unsigned N>
inline T d_heap<T, K, N>::d_heap_extract_max()
{
	if (d_heapSize < 1)
	{
		cout << "d_heap underflow!" << endl;
		return T();
	}
	T max = A[0];
	A[0] = A[--d_heapSize];
	max_d_heapify(0);
	return max;
}

template<class T, unsigned K, unsigned N>
inline T d_heap<T, K, N>::d_heap_extract_min()
{
	if (d_heapSize < 1)
	{
		cout << "d_heap underflow!" << endl;
		return T();
	}
	T min = A[0];
	A[0] = A[--d_heapSize];
	min_d_heapify(0);
	return min;
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::d_heap_increase_key(unsigned i, T key)
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

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::d_heap_decrease_key(unsigned i, T key)
{
	if (A[i] < key)
	{
		cout << "new key is larger that current key" << endl;
		return;
	}
	A[i] = key;
	while (i > 0 && A[i]<A[parent(i)] )
	{
		swap(i, parent(i));
		i = parent(i);
	}
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::max_d_heap_insert(T key)
{
	if (d_heapSize == size)
	{
		cout << "the d_heap is full";
		return;
	}
	A[d_heapSize++] = key;
	d_heap_increase_key(d_heapSize - 1, key);
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::min_d_heap_insert(T key)
{
	if (d_heapSize == size)
	{
		cout << "the d_heap is full";
		return;
	}
	A[d_heapSize++] = key;
	d_heap_decrease_key(d_heapSize - 1, key);
}

template <class T, unsigned K, unsigned N> ostream& operator<<(ostream& out, d_heap<T, K, N>& h)
{
	for (T t : h.A) out << t << " ";
	return out;
}
template <class T, unsigned K, unsigned N> istream& operator>>(istream& in, d_heap<T, K, N>& h)
{
	for (T &t : h.A)in >> t;
	return in;
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::bulid_max_d_heap()
{
	d_heapSize = d_heapSize == 0 ? size : d_heapSize;
	for (int i = (d_heapSize - 1) / K; i >= 0; i--)
		max_d_heapify(i);
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::bulid_min_d_heap()
{
	d_heapSize = d_heapSize == 0 ? size : d_heapSize;
	for (int i = (d_heapSize - 1) / K; i >= 0; i--)
		min_d_heapify(i);
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::d_heapsort()
{
	bulid_max_d_heap();
	for (int i = size - 1; i > 0; i--)
	{
		swap(0, i);
		d_heapSize--;
		max_d_heapify(0);
	}
	d_heapSize = 0;
}

template<class T, unsigned K, unsigned N>
inline void d_heap<T, K, N>::d_heapsort_reverse()
{
	bulid_min_d_heap();
	for (int i = size - 1; i > 0; i--)
	{
		swap(0, i);
		d_heapSize--;
		min_d_heapify(0);
	}
	d_heapSize = 0;
}
