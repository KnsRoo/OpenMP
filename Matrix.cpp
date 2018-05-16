#include "Matrix.h"

#include <omp.h>
#include <random>
#include <chrono>
#include <stdexcept>
#include <sstream>

#ifndef MATRTIX_MUL
#define MATRTIX_MUL 1
#endif

std::vector<double> randVector(size_t size) {
	std::vector<double> result(size);
	#pragma omp parallel shared(result)
	{
		std::random_device rd;
		std::mt19937_64 gen(rd());
		std::uniform_real_distribution<double> dis(1.0, 2.0);

		#pragma omp for schedule(static)
		for (size_t i = 0; i < size; i++)
			result[i] = dis(gen);
	}
	return result;
}

std::vector<double> eyeMatrix(size_t rows, size_t cols) {
	size_t size = rows > cols ? rows : cols;
	std::vector<double> result(rows * cols);

	#pragma omp for schedule(static)
	for (size_t i = 0; i < size; i++)
		result[i * cols + i] = 1;

	return result;
}

Matrix mulSerial(const Matrix& first, const Matrix& second) {
	Matrix result(first.rows(), second.cols());

	if (first.cols() == second.rows())
		for (size_t i = 0; i < result.rows(); ++i)
			for (size_t j = 0; j < result.cols(); ++j)
				for (size_t k = 0; k < result.rows(); ++k)
					result(i, j) += first(i, k) * second(k, j);
	else
		throw std::invalid_argument("Wrong dimensions");

	return result;
}

Matrix mulParallel_1(const Matrix& first, const Matrix& second) {
	Matrix result(first.rows(), second.cols());
	if (first.cols() == second.rows())
		#pragma omp parallel for default(shared)
		for (size_t i = 0; i < result.rows(); ++i)
			for (size_t j = 0; j < result.cols(); ++j) {
				result(i, j) = 0;
				for (size_t k = 0; k < result.rows(); ++k)
					result(i, j) += first(i, k) * second(k, j);
			}
	else
		throw std::invalid_argument("Wrong dimensions");

	return result;
}

Matrix mulParallel_2(const Matrix& first, const Matrix& second) {
	Matrix result(first.rows(), second.cols());
	if (first.cols() == second.rows()) {
		Matrix secT = transpose(second);
		#pragma omp parallel for default(shared)
		for (size_t i = 0; i < result.rows(); ++i) 
			for (size_t j = 0; j < result.cols(); ++j) {
				result(i, j) = 0;
				for (size_t k = 0; k < result.rows(); ++k) 
					result(i, j) += first(i, k) * secT(j, k);
			}
	}
	else
		throw std::invalid_argument("Wrong dimensions");

	return result;
}

Matrix transpose(const Matrix& matrix) {
	Matrix result(matrix.cols(), matrix.rows());
	#pragma omp parallel for shared(result)
	for (size_t i = 0; i < matrix.rows(); ++i)
		for (size_t j = 0; j < matrix.cols(); ++j) 
			result(i, j) = matrix(j, i);
		
  	return result;
}

std::string toString(const Matrix& matrix) {
	std::stringstream ss;
	for (size_t i = 0; i < matrix.rows(); ++i) {
		for (size_t j = 0; j < matrix.cols(); ++j) {
			ss << matrix(i, j) << " ";
		}
		ss << std::endl;
	}
	return ss.str();
}

Matrix Matrix::operator*(const Matrix& matrix) {
	#if MATRTIX_MUL==0
		return mulSerial((*this), matrix);
	#elif MATRTIX_MUL==1
		return mulParallel_1((*this), matrix);
	#elif MATRTIX_MUL==2
		return mulParallel_2((*this), matrix);
	#else
		#error Not correct definition MATRTIX_MUL
	#endif
}
