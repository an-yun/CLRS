#include<iostream>
using namespace std;
struct SubarrayDemarcation//子数组界线元组结构体
{
	int left = 0;
	int right = 0;
	int sum = 0;
	SubarrayDemarcation(int left, int right, int sum):left(left),right(right),sum(sum){}//构造函数
};

SubarrayDemarcation find_max_crossing_subarray(int A[], int low, int mid, int high)
{
	int left_sum = A[mid-1], sum = left_sum,max_left=mid-1;
	for (int i = mid - 2; i >= low; i--)//可以省略位于mid-1位置上的那个数
	{
		sum += A[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}
	int right_sum = A[mid],  max_right = mid;
	sum = right_sum;
	for (int j = mid + 1; j < high; j++)//可以省略位于mid位置上的那个数
	{
		sum += A[j];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = j;
		}
	}
	return SubarrayDemarcation(max_left, max_right+1, left_sum + right_sum);
}

SubarrayDemarcation find_max_subarray(int A[], int low, int high)
{
	if (low >= high)
		return SubarrayDemarcation(low, low, 0);
	else if (low == high - 1)
		return SubarrayDemarcation(low, high, A[low]);
	else
	{
		int mid = low + (high - low) / 2;
		SubarrayDemarcation left_demarcation = find_max_subarray(A, low, mid);
		SubarrayDemarcation right_demarcation = find_max_subarray(A, mid, high);
		SubarrayDemarcation cross_demarcation = find_max_crossing_subarray(A, low, mid,high);
		if (left_demarcation.sum >= right_demarcation.sum&&left_demarcation.sum >= cross_demarcation.sum)
			return left_demarcation;
		else if (right_demarcation.sum >= left_demarcation.sum&&right_demarcation.sum >= cross_demarcation.sum)
			return right_demarcation;
		else return cross_demarcation;
	}
}

SubarrayDemarcation find_max_subarray_brute_force(int A[], int low, int high)
{
	if (low >= high)
		return SubarrayDemarcation(low, low, 0);
	else if (low == high - 1)
		return SubarrayDemarcation(low, high, A[low]);
	else {
		int sum = A[low];
		SubarrayDemarcation array_demarcation(low, low + 1, sum);
		for (int i = low; i < high; i++)
		{
			sum = A[i];
			if (sum > array_demarcation.sum)
			{
				array_demarcation.left = i;
				array_demarcation.right = i + 1;
				array_demarcation.sum = sum;
			}
			for (int j = i + 1; j < high; j++)
			{
				sum += A[j];
				if (sum > array_demarcation.sum)
				{
					array_demarcation.left = i;
					array_demarcation.right = j + 1;
					array_demarcation.sum = sum;
				}
			}
		}
		return array_demarcation;
	}
}

SubarrayDemarcation find_maximum_subarray_linear(int A[], int low, int high)
{
	if (low >= high)
		return SubarrayDemarcation(low, low, 0);
	else if (low == high - 1)
		return SubarrayDemarcation(low, high, A[low]);
	else 
	{
		SubarrayDemarcation max_subarray(low, low + 1, A[low]), max_subarray_to_end = max_subarray;
		for (int i = low + 1; i < high; i++)
		{
			if (max_subarray_to_end.sum > 0)
			{
				max_subarray_to_end.sum += A[i];
				max_subarray_to_end.right = i+1;
			}
			else
			{
				max_subarray_to_end.sum = A[i];
				max_subarray_to_end.left = i;
				max_subarray_to_end.right = i + 1;
			}
			if (max_subarray_to_end.sum > max_subarray.sum)
				max_subarray = max_subarray_to_end;
		}
		return max_subarray;
	}
}
int main4_1()
{
	int all_array[] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	cout << "分治法" << endl;
	SubarrayDemarcation result1 = find_max_subarray(all_array, 0, 16);
	cout << "左边: " << result1.left << " 右边: " << result1.right << endl;
	cout << "总和: " << result1.sum<<endl;
	cout << "暴力法" << endl;
	SubarrayDemarcation result2 = find_max_subarray_brute_force(all_array, 0, 16);
	cout << "左边: " << result2.left << " 右边: " << result2.right << endl;
	cout << "总和: " << result2.sum<<endl;
	cout << "动态规划法" << endl;
	SubarrayDemarcation result3 = find_maximum_subarray_linear(all_array, 0, 16);
	cout << "左边: " << result3.left << " 右边: " << result3.right << endl;
	cout << "总和: " << result3.sum << endl;
	return 0;
}