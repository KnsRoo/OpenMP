#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <string>

std::vector<double> randVector(size_t size);
std::vector<double> eyeMatrix(size_t rows, size_t cols);

class Matrix {
private:
	size_t m_rows;
	size_t m_cols;
	std::vector<double> m_data;
	Matrix(size_t rows, size_t cols, std::vector<double>&& data)
		: m_rows(rows)
		, m_cols(cols)
		, m_data(std::move(data))
	{}
	
public:
	Matrix(size_t rows, size_t cols)
		: m_rows(rows)
		, m_cols(cols)
		, m_data(rows * cols)
	{}
	Matrix(const Matrix &first)
        : m_rows(first.m_rows)
        , m_cols(first.m_cols)
        , m_data(std::move(first.m_data))
    {}

	inline size_t rows() const { return m_rows; }

	inline size_t cols() const { return m_cols;	}

	inline double& operator()(size_t row, size_t col) { return m_data[row * m_cols + col]; }

	inline const double& operator()(size_t row, size_t col) const { return m_data[row * m_cols + col]; }

	std::string toString();
	Matrix operator*(const Matrix& matrix);

	static Matrix rand(size_t rows, size_t cols) { return Matrix(rows, cols, randVector(rows * cols)); }
	static Matrix eye(size_t rows, size_t cols) { return Matrix(rows, cols, eyeMatrix(rows, cols)); }
};

Matrix mulSerial(const Matrix& first, const Matrix& second);
Matrix mulParallel_1(const Matrix& first, const Matrix& second);
Matrix mulParallel_2(const Matrix& first, const Matrix& second);
Matrix transpose(const Matrix& matrix);
std::string toString(const Matrix& matrix);

#endif // __MATRIX_H__
