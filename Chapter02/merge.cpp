//#include<iostream>
//using namespace std;
//
//void fill(int A[], int start, int end, int des[])
//{
//	for (int i = 0; start < end; ++start, ++i)
//		des[i] = A[start];
//}
//
//void merge(int A[], int p, int q, int r)
//{
//	int length1 = q - p, length2 = r - q;
//	int *L = new int[length1], *R = new int[length2];
//	fill(A, p, q, L);
//	fill(A, q, r, R);
//	int i = 0, j = 0;
//	while (i < length1 || j < length2)
//	{
//		if (i >= length1)
//			for (; j < length2; ++j, ++p) A[p] = R[j];
//		else if (j >= length2)
//			for (; i < length1; ++i, ++p) A[p] = L[i];
//		else if (L[i] <= R[j])
//		{
//			A[p] = L[i];
//			++i;
//			++p;
//		}
//		else
//		{
//			A[p] = R[j];
//			++j;
//			++p;
//		}
//	}
//}
//int merge_inversions(int A[], int p, int q, int r)
//{
//	int length1 = q - p+1, length2 = r - q;
//	int *L = new int[length1 + 1], *R = new int[length2 + 1];
//	fill(A, p, q+1, L);
//	fill(A, q+1, r+1, R);
//	L[length1] = R[length2 - 1] + 1;
//	R[length2] = L[length1 - 1] + 1;
//	int i = 0, j = 0, inversions = 0;
//	for (; p <= r; p++)
//	{
//		if (L[i] <= R[j])
//		{
//			A[p] = L[i];
//			++i;
//		}
//		else
//		{
//			inversions += length1 - i;
//			A[p] = R[j];
//			++j;
//		}
//	}
//	return inversions;
//}
//
//int count_inversions(int A[], int p, int r)
//{
//	int inversions = 0;
//	if (p < r)
//	{
//		int q = p + (r - p) / 2;
//		inversions += count_inversions(A, p, q);
//		inversions += count_inversions(A, q+1, r);
//		inversions += merge_inversions(A, p, q, r);
//	}
//	return inversions;
//}
//size_t binary_search(int A[], size_t low, size_t high, int key)
//{
//	while (low <= high)
//	{
//		int mid = low + (high - low) / 2;
//		if (key == A[mid])
//			return mid;
//		else if (key > A[mid])
//			low = mid + 1;
//		else
//			high = mid - 1;
//	}
//	return low;
//}
//int main2_4()
//{
//	int inversions_array[] = {  9,8, 6, 3,1 };
//	cout << count_inversions(inversions_array, 0, 4) << endl;
//	return 0;
//}