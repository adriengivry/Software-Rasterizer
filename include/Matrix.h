#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

template<typename T, uint16_t i>
class Matrix

{
public:
	explicit Matrix(T p_defaultValue = 0);
	~Matrix();

	T GetElement(const uint16_t p_row, const uint16_t p_col);
	T**& GetData();

	void SetElement(const uint16_t p_row, const uint16_t p_col, T p_element);
	void SetData(T p_data[i][i]);

	bool IsIdentity();

	void DisplayData() const;

	Matrix operator+(Matrix& p_otherMatrix);
	Matrix operator*(Matrix& p_otherMatrix);

private:
	T** __DATA;
};

typedef Matrix<float, 4> Mat4;


template <typename T, uint16_t i>
Matrix<T, i>::Matrix(T p_defaultValue)
{
	__DATA = new T*[i];
	for (uint16_t row = 0; row < i; ++row)
		__DATA[row] = new T[i];

	for (uint16_t row = 0; row < i; ++row)
		for (uint16_t col = 0; col < i; ++col)
			__DATA[row][col] = p_defaultValue;
}

template <typename T, uint16_t i>
Matrix<T, i>::~Matrix()
{
}

template <typename T, uint16_t i>
T Matrix<T, i>::GetElement(const uint16_t p_row, const uint16_t p_col)
{
	return __DATA[p_row][p_col];
}

template <typename T, uint16_t i>
T**& Matrix<T, i>::GetData()
{
	return __DATA;
}

template <typename T, uint16_t i>
void Matrix<T, i>::SetElement(const uint16_t p_row, const uint16_t p_col, T p_element)
{
	__DATA[p_row][p_col] = p_element;
}

template <typename T, uint16_t i>
void Matrix<T, i>::SetData(T p_data[i][i])
{
	for (uint16_t row = 0; row < i; ++row)
	{
		for (uint16_t col = 0; col < i; ++col)
		{
			__DATA[row][col] = p_data[row][col];
		}
	}
}

template <typename T, uint16_t i>
bool Matrix<T, i>::IsIdentity()
{
	for (uint16_t row = 0; row < i; ++row)
	{
		for (uint16_t col = 0; col < i; ++col)
		{
			if (row == col)
				if (__DATA[row][col] != 1) 
					return false;
				
			if (row != col)
				if (__DATA[row][col] != 0) 
					return false;
		}
	}

	return true;
}

template <typename T, uint16_t i>
void Matrix<T, i>::DisplayData() const
{
	for (uint16_t row = 0; row < i; ++row)
	{
		for (uint16_t col = 0; col < i; ++col)
		{
			std::cout << __DATA[row][col] << " ";
		}
		std::cout << std::endl;
	}
}

template <typename T, uint16_t i>
Matrix<T, i> Matrix<T, i>::operator+(Matrix& p_otherMatrix)
{
	Matrix<T, i> toReturn(0);

	for (uint16_t row = 0; row < i; ++row)
		for (uint16_t col = 0; col < i; ++col)
			toReturn.SetElement(row, col, __DATA[row][col] + p_otherMatrix.GetElement(row, col));

	return toReturn;
}

template <typename T, uint16_t i>
Matrix<T, i> Matrix<T, i>::operator*(Matrix& p_otherMatrix)
{
	Matrix<T, i> toReturn(0);

	for (uint16_t row = 0; row < i; ++row)
	{
		for (uint16_t col = 0; col < i; ++col)
		{
			T value = 0;
			for (uint16_t u = 0; u < i; ++u)
			{
				value += __DATA[row][u] * p_otherMatrix.GetData()[u][col];
			}
			toReturn.SetElement(row, col, value);
		}
	}

	return toReturn;
}

