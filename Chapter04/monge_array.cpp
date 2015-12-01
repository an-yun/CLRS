#include<iostream>
using namespace std;

struct matrix_array {
	int m;
	int n;
	int step;
	int *data;
};

int get(matrix_array A, int i, int j) {
	return A.data[((i + 1)*A.step - 1)*A.n + j];
}

matrix_array half(matrix_array a)
{
	matrix_array result = { a.m,a.n,a.step * 2,a.data };
	return result;
}

int height(matrix_array a)
{
	return a.m / a.step;
}
int min_index(matrix_array A, int row, int left, int right)
{
	int min = left;

	for (int i = left; i < right; i++)
		if (get(A, row, i) < get(A, row, min)) min = i;
	return min;
}
void find_minimums(matrix_array A, int *mins)
{
	if (height(A) == 1)
		mins[0] = min_index(A, 0, 0, A.n);
	else
	{
		matrix_array evens = half(A);
		int *even_mininmums = new int[height(evens)];

		find_minimums(evens, even_mininmums);

		int left_most = 0, evens_height = height(evens);
		for (int i = 0; i < evens_height; i++)
		{
			left_most = min_index(A, 2 * i, left_most, even_mininmums[i] + 1);

			mins[2 * i] = left_most;
			mins[2 * i + 1] = even_mininmums[i];
		}
		if (height(A) % 2)
			mins[height(A) - 1] = min_index(A, height(A) - 1, left_most, A.n);
		delete[]even_mininmums;
	}
}
int main4_6()
{
	int monge_array_content[] = {
		10,17,13,28,23,
		17,22,16,29,23,
		24,28,22,34,24,
		11,13,6,17,7,
		45,44,32,37,23,
		36,33,19,21,6,
		75,66,51,53,34
	};
	matrix_array monge_array{7,5,1,monge_array_content};
	int mins[7];
	find_minimums(monge_array, mins);
	for (int num : mins)
		cout << num << " ";
	cout << endl;
	return 0;
}