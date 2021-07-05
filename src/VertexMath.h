#ifndef VERTEX_MATRIX
#define VERTEX_MATRIX

#include <iostream>
#include <cmath>

#define PI 3.14159265

template <class T2, int var2>
class Vector;

template <class T, int var>
class Matrix
{
	T m_matrix[var][var] {};
public:
	Matrix(T arg = 0)
	{
		for(int i = 0; i < var; ++i)
		{
			m_matrix[i][i] = arg;
			if(i == (var-1))
				m_matrix[i][i] = 1;
		}
	}

	Matrix<T, var> operator*(Matrix& matrix);
	T* operator[](const int index);
	template<class T2, int var2>
	Vector<T2, var2> operator*(Vector<T2, var2>& vector);
};

template<class T, int var>
Matrix<T, var> Matrix<T, var>::operator*(Matrix& matrix)
{
	Matrix<T, var> tempMatrix;
	for(int i = 0; i < var; ++i)
		for(int j = 0; j < var; ++j)
			for(int n = 0; n < var; ++n)
			{
				tempMatrix.m_matrix[i][j] += m_matrix[i][n] * matrix.m_matrix[n][j];
			}
	return tempMatrix;
}

template <class T, int var>
T* Matrix<T, var>::operator[](const int index)
{
	return m_matrix[index];
}

template <class T, int var>
template <class T2, int var2>
Vector<T2, var2> Matrix<T, var>::operator*(Vector<T2, var2>& vector)
{
	static_assert(var == var2, "Size error");
	Vector<T2, var2> tempVector;
	for(int i = 0; i < var2; ++i)
		for(int j = 0; j < var; ++j)
		{
			tempVector[i] += m_matrix[i][j] * vector[j];
		}
	return tempVector;
}

template <class T2, int var2>
class Vector
{
	public: T2 m_vector[var2] {};
public:
	Vector(T2 arg1 = 0, T2 arg2 = 0, T2 arg3 = 0, T2 arg4 = 0)
	{
		T2 array[4] = {arg1, arg2, arg3, arg4};
		for(int i = 0; i < var2; ++i)
		{
			m_vector[i] = array[i];
		}
	}

	T2& operator[](const int index);
	template<class T, int var>
	Vector<T2, var2> operator*(Matrix<T, var>& matrix);
};

template<class T2, int var2>
T2& Vector<T2, var2>::operator[](const int index)
{
	return m_vector[index];
}

template <class T2, int var2>
template <class T, int var>
Vector<T2, var2> Vector<T2, var2>::operator*(Matrix<T, var>& matrix)
{
	static_assert(var == var2, "Size error");
	Vector<T2, var2> tempVector;
	for(int i = 0; i < var2; ++i)
		for(int j = 0; j < var; ++j)
		{
			tempVector[i] += m_vector[j] * matrix[j][i];
		}
	return tempVector;
}

template <class T, class T2,int var, int var2>
Matrix<T, var> LookAt(Matrix<T, var> matrix, Vector<T2, var2> vector)
{
	Matrix<T, var> tempMatrix(1.0f);
	tempMatrix = matrix;

	unsigned const int variable = 3;
	for(int i = 0; i < var2; ++i)
		tempMatrix[i][variable] = -vector[i];

	return tempMatrix;
}

template <class T, class T2, int var, int var2>
Matrix<T, var> Translate(Matrix<T, var> matrix, Vector<T2, var2> vector)
{
	Matrix<T, var> tempMatrix;
	tempMatrix = matrix;

	for(int i = 0; i < var; ++i)
		tempMatrix[i][var-1] = vector[i];

	return tempMatrix;
}

template <class T, class T2, int var, int var2>
Matrix<T, var> Scale(Matrix<T, var> matrix, Vector<T2, var2> vector)
{
	Matrix<T, var> tempMatrix;
	tempMatrix = matrix;

	for(int i = 0; i < var; ++i)
		for(int j = 0; j < var; ++j)
		{
			tempMatrix[j][i] *= vector[i];
		}
	return tempMatrix;
}

template <class T, int var>
Matrix<T, var> RotateZ(Matrix<T, var> matrix, float angle)
{
	Matrix<T, var> tempMatrix(1.0f);
	tempMatrix[0][0] = std::cos(angle*PI/180);
	tempMatrix[0][1] = -std::sin(angle*PI/180);
	tempMatrix[1][0] = std::sin(angle*PI/180);
	tempMatrix[1][1] = std::cos(angle*PI/180);

	Matrix<T, var> tempMatrix2;
	tempMatrix2 = matrix * tempMatrix;

	return tempMatrix2;
}

template <class T, int var>
Matrix<T, var> Rotate(Matrix<T, var> matrix, Vector<T, var> vector, float angle)
{
	float range = std::sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
	for(int l = 0; l < var; ++l)
		vector[l] = vector[l]/range;

	angle *= PI/180;
	Matrix<T, var> tempMatrix(1.0f);

	tempMatrix[0][0] = std::cos(angle) + (vector[0] * vector[0]) * (1 - std::cos(angle));
	tempMatrix[1][0] = vector[0] * vector[1] * (1 - std::cos(angle)) - vector[2] * std::sin(angle);
	tempMatrix[2][0] = vector[0] * vector[2] * (1 - std::cos(angle)) + vector[1] * std::sin(angle);
	tempMatrix[3][0] = 0;
	tempMatrix[0][1] = vector[1] * vector[0] * (1 - std::cos(angle)) + vector[2] * std::sin(angle);
	tempMatrix[1][1] = std::cos(angle) + (vector[1] * vector[1]) * (1 - std::cos(angle));
	tempMatrix[2][1] = vector[1] * vector[2] * (1 - std::cos(angle)) - vector[0] * std::sin(angle);
	tempMatrix[3][1] = 0;
	tempMatrix[0][2] = vector[2] * vector[0] * (1 - std::cos(angle)) - vector[1] * std::sin(angle);
	tempMatrix[1][2] = vector[2] * vector[1] * (1 - std::cos(angle)) + vector[0] * std::sin(angle);
	tempMatrix[2][2] = std::cos(angle) + (vector[2] * vector[2]) * (1 - std::cos(angle));
	tempMatrix[3][2] = 0;
	tempMatrix[0][3] = 0;
	tempMatrix[1][3] = 0;
	tempMatrix[2][3] = 0;
	tempMatrix[3][3] = 1;

	Matrix<T, var> tempMatrix2;
	tempMatrix2 = matrix * tempMatrix;

	return tempMatrix2;
}

template <class T, int var>
Matrix<T, var> Ortho(float w, float h, float zn, float zf)
{
	Matrix<T, var> tempMatrix(1.0f);
	tempMatrix[0][0] = 2/w;
	tempMatrix[1][1] = 2/h;
	tempMatrix[2][2] = 1/(zf-zn);

	return tempMatrix;
}

template <class T, int var>
Matrix<T, var> Perspective(float fov, float n, float f)
{
	float S = std::tan((fov/2)*(PI/360));
	Matrix<float, var> tempMatrix;
	tempMatrix[0][0] = 1/((1280.0f/1280.0f)*S);
	tempMatrix[1][1] = 1/S;
	tempMatrix[2][2] = -((f+n)/(f-n));
	tempMatrix[2][3] = -((2*f*n)/(f-n));
	tempMatrix[3][2] = -1;

	return tempMatrix;
}

#endif
