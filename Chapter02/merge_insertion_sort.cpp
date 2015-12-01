#include<iostream>
#include<algorithm>
#include <windows.h>
using namespace std;
inline void fill(int A[], int start, int end, int des[])
{
	for (int i = 0; start < end; start++, i++)
		des[i] = A[start];
}
inline void merge(int A[], int p, int q, int r)
{
	int l_length = q - p, r_length = r - q;
	int *L = new int[l_length + 1], *R = new int[r_length + 1];
	fill(A, p, q, L);
	fill(A, q, r, R);
	L[l_length] = R[r_length - 1] + 1;
	R[r_length] = L[l_length - 1] + 1;
	for (int i = 0, j = 0; p < r; p++)
	{
		if (L[i] <= R[j])
		{
			A[p] = L[i];
			i++;
		}
		else
		{
			A[p] = R[j];
			j++;
		}
	}
	delete[]L;
	delete[]R;
}
inline void insertion_sort(int A[], int p, int r)
{
	for (int i = p + 1; i < r; i++)
	{
		int key = A[i], j = i - 1;
		for (; j >= p && A[j]>key; j--)
			A[j + 1] = A[j];
		A[j + 1] = key;
	}
}
void merge_sort(int A[], int p, int r)
{
	if (p < r - 1)
	{
		int length = (r - p) / 2;
		if (length < 80)
			insertion_sort(A, p, r);
		else {
			int q = p + length;
			merge_sort(A, p, q);
			merge_sort(A, q, r);
			merge(A, p, q, r);
		}
	}
}
void print_array(int A[], int p, int r)
{
	for (; p < r; p++)
		cout << A[p] << " ";
	cout << endl;
}
int main2_1()
{
	LARGE_INTEGER start, afterSort;
	const int array_size = 1000000;
	int *insertion_sort_array1=new int[array_size];
	for (int i = array_size; i > 0; i--)
		insertion_sort_array1[array_size - i] = i;
	random_shuffle(insertion_sort_array1, insertion_sort_array1 + array_size);
	cout << "test sort begin" << endl;
	QueryPerformanceCounter(&start);
	sort(insertion_sort_array1, insertion_sort_array1 + array_size);
	QueryPerformanceCounter(&afterSort);
	cout << "sort took     " << afterSort.QuadPart -
		start.QuadPart << " ticks." << endl;
	int *insertion_sort_array = new int[array_size];
	for (int i = array_size; i > 0; i--)
		insertion_sort_array[array_size - i] = i;
	random_shuffle(insertion_sort_array, insertion_sort_array + array_size);
	cout << "test my_merge_sort begin" << endl;
	QueryPerformanceCounter(&start);
	merge_sort(insertion_sort_array, 0, array_size);
	QueryPerformanceCounter(&afterSort);
	cout << "my merge_sort took     " << afterSort.QuadPart -
		start.QuadPart << " ticks." << endl;
	cout << endl;
	return 0;
}