#include<iostream>
#include<vector>
#include<memory>
#include<tuple>
#include<initializer_list>
using namespace std;
template <class T> class Matrix;
template <class T> Matrix<T> operator +(const Matrix<T> &A, const Matrix<T> &B);
template <class T> Matrix<T> operator -(const Matrix<T> &A, const Matrix<T> &B);
template <class T> Matrix<T> operator *(const Matrix<T> &A, const Matrix<T> &B);
template <class T> void matrix_replace(Matrix<T> &A, Matrix<T> &B);
template <class T> Matrix<T> strassen_multiply(Matrix<T> &A, Matrix<T> &B);
template <class T>
class Matrix
{
	friend  Matrix<T> operator +<T>(const Matrix<T> &A, const Matrix<T> &B);
	friend  Matrix<T> operator -<T>(const Matrix<T> &A, const Matrix<T> &B);
	friend  Matrix<T> operator *<T>(const Matrix<T> &A, const Matrix<T> &B);
	friend  void matrix_replace<T>(Matrix<T> &A, Matrix<T> &B);
	friend Matrix<T> strassen_multiply<T>(Matrix<T> &A, Matrix<T> &B);
private:
	shared_ptr<vector<vector<T>>> matrix_content;
	tuple<size_t, size_t> start_position;
	tuple<size_t, size_t> end_position;
	vector<T>& operator[](size_t index) { return (*matrix_content)[index]; }
public:
	Matrix() :matrix_content(nullptr) {}
	Matrix(const Matrix<T> &matrix, size_t start_x, size_t start_y, size_t end_x, size_t end_y) :matrix_content(matrix.get_matrixcontent()), start_position{ start_x,start_y }, end_position{ end_x,end_y } {}
	Matrix(const vector<vector<T>> &vector_content) :matrix_content(new vector<vector<T>>(vector_content)), start_position{ 0,0 }, end_position{ vector_content.size(), vector_content[0].size() } {}
	Matrix(initializer_list<vector<T>> content) :matrix_content(new vector<vector<T>>(content)), start_position{ 0,0 }, end_position{ content.size(), (*content.begin()).size() } {}
	void print() const
	{
		if (matrix_content == nullptr)
			return;
		for (size_t i = get_start_x(); i < get_end_x(); i++)
		{
			for (size_t j = get_start_y(); j < get_end_y(); j++)
				cout << (*matrix_content)[i][j] << " ";
			cout << endl;
		}
	}
	size_t get_start_x() const { return  get<0>(start_position); }
	size_t get_start_y() const { return  get<1>(start_position); }
	size_t get_end_x() const { return  get<0>(end_position); }
	size_t get_end_y() const { return  get<1>(end_position); }
	shared_ptr<vector<vector<T>>> get_matrixcontent() const { return matrix_content; }
	Matrix<T> get_new_matrix() const
	{
		vector<vector<T>> vector_content;
		for (size_t i = 0; i < get_end_x() - get_start_x(); i++)
		{
			vector_content.push_back(vector<T>());
			for (size_t j = 0; j < get_end_y() - get_start_y(); j++)
				vector_content[i].push_back((*matrix_content)[get_start_x()+i][get_start_y()+j]);
		}
		return Matrix(vector_content);
	}
	Matrix<T> get_partition_matrix(size_t row_index, size_t column_index) const
	{
		size_t start_x = row_index == 1 ? get_start_x() : get_start_x() + (get_end_x() - get_start_x()) / 2;
		size_t start_y = column_index == 1 ? get_start_y() : get_start_y() + (get_end_y() - get_start_y()) / 2;
		size_t end_x = row_index == 1 ? get_start_x() + (get_end_x() - get_start_x()) / 2 : get_end_x();
		size_t end_y = column_index == 1 ? get_start_y() + (get_end_y() - get_start_y()) / 2 : get_end_y();
		return Matrix<T>(*this, start_x, start_y, end_x, end_y);
	}
	void set_first_to_0() { (*matrix_content)[0][0] = 0; }
};

template <class T>
Matrix<T> operator+(const Matrix<T> &A, const Matrix<T> &B)
{
	Matrix<T> matrixA = A.get_new_matrix(), matrixB = B.get_new_matrix();
	for (size_t i = 0; i < matrixA.get_end_x() - matrixA.get_start_x(); i++)
		for (size_t j = 0; j < matrixA.get_end_y() - matrixA.get_start_y(); j++)
			matrixA[i][j] += matrixB[i][j];
	return matrixA;
}
template <class T>
Matrix<T> operator-(const Matrix<T> &A, const Matrix<T> &B)
{
	Matrix<T> matrixA = A.get_new_matrix(), matrixB = B.get_new_matrix();
	for (size_t i = 0; i < matrixA.get_end_x() - matrixA.get_start_x(); i++)
		for (size_t j = 0; j < matrixA.get_end_y() - matrixA.get_start_y(); j++)
			matrixA[i][j] -= matrixB[i][j];
	return matrixA;
}
template <class T>
Matrix<T> get_new_matrix(size_t row, size_t column)
{
	vector<vector<T>> vector_content(row);
	for (auto &row_vector : vector_content)
		row_vector = vector<T>(column);
	return Matrix<T>(vector_content);
}
template <class T>
Matrix<T> operator*(const Matrix<T> &A, const Matrix<T> &B)
{
	size_t row = A.get_end_x() - A.get_start_x(), colum = B.get_end_y() - B.get_start_y();
	Matrix<T> C = get_new_matrix<T>(row, colum);
	Matrix<T> matrixA = A.get_new_matrix(), matrixB = B.get_new_matrix();
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < colum; j++)
		{
			C[i][j] = 0;
			for (size_t k = 0; k < matrixA.get_end_y() - matrixA.get_start_y(); k++)
			{
				C[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	return C;
}
template <class T>
void matrix_replace (Matrix<T> &A, Matrix<T> &B)
{
	size_t row = A.get_end_x() - A.get_start_x(), colum = A.get_end_y() - A.get_start_y();
	for (size_t i = 0; i < row; i++)
		for (size_t j = 0; j < colum; j++)
		{
			B[B.get_start_x()+i][B.get_start_y()+j] = A[A.get_start_x() + i][A.get_start_y() + j];
		}
}

template <class T>
Matrix<T> strassen_multiply(Matrix<T> &A, Matrix<T> &B)
{
	size_t row = A.get_end_x() - A.get_start_x(), colum = B.get_end_y() - B.get_start_y();
	if (row == 1 && colum == 1)
		return Matrix<T>{ {A[A.get_start_x()][A.get_start_y()] * B[B.get_start_x()][B.get_start_y()]}};
	else
	{
		Matrix<T> C = get_new_matrix<T>(row, colum);
		Matrix<T> A11 = A.get_partition_matrix(1, 1), A12 = A.get_partition_matrix(1, 2), A21 = A.get_partition_matrix(2, 1), A22 = A.get_partition_matrix(2, 2);
		Matrix<T> B11 = B.get_partition_matrix(1, 1), B12 = B.get_partition_matrix(1, 2), B21 = B.get_partition_matrix(2, 1), B22 = B.get_partition_matrix(2, 2);
		Matrix<T> C11 = C.get_partition_matrix(1, 1), C12 = C.get_partition_matrix(1, 2), C21 = C.get_partition_matrix(2, 1), C22 = C.get_partition_matrix(2, 2);
		Matrix<T> S1 = B12 - B22;
		Matrix<T> S2 = A11 + A12;
		Matrix<T> S3 = A21 + A22;
		Matrix<T> S4 = B21 - B11;
		Matrix<T> S5 = A11 + A22;
		Matrix<T> S6 = B11 + B22;
		Matrix<T> S7 = A12 - A22;
		Matrix<T> S8 = B21 + B22;
		Matrix<T> S9 = A11 - A21;
		Matrix<T> S10 = B11 + B12;
		Matrix<T> P1 = strassen_multiply(A11, S1);
		Matrix<T> P2 = strassen_multiply(S2, B22);
		Matrix<T> P3 = strassen_multiply(S3, B11);
		Matrix<T> P4 = strassen_multiply(A22, S4);
		Matrix<T> P5 = strassen_multiply(S5, S6);
		Matrix<T> P6 = strassen_multiply(S7, S8);
		Matrix<T> P7 = strassen_multiply(S9, S10);
		matrix_replace(P5 + P4 - P2 + P6, C11);
		matrix_replace(P1+P2, C12);
		matrix_replace(P3+P4, C21);
		matrix_replace(P5+P1-P3-P7, C22);
		return C;
	}
}

int main4_22()
{
	Matrix<int> D = {
		{1,3,4,5},
		{7,5,8,9},
		{ 6,5,8,9 },
		{ 10,5,8,9 }
	};
	Matrix<int> E = {
		{ 2,3,4,5 },
		{ 7,5,8,9 },
		{ 6,7,8,9 },
		{ 10,5,8,9 }
	};
	auto F = D*E;
	cout << "Matrix D:" << endl;
	D.print();
	cout << "Matrix E:" << endl;
	E.print();
	cout << "Matrix F(D*F):" << endl;
	F.print();
	auto G = strassen_multiply(D, E);
	G.print();
	return 0;
}