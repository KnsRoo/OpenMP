#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Matrix.h"

#include <sstream>

void benchmarkPrint(size_t dim, double initDuration, double mulDuration, double runtimeDuration);
void printCSV(int threads, size_t dim, double initDuration, double mulDuration, double runtimeDuration);

struct DirichletResult {
	size_t num_threads;
	Matrix surface;
	size_t iterations;
	double runtime;
	double eps;


	DirichletResult(int n, Matrix s, size_t i, double r, double e) : 
		num_threads(n), surface(s), iterations(i), runtime(r), eps(e)
	{}
	
	DirichletResult(const DirichletResult &res) : 
		num_threads(res.num_threads), surface(res.surface), iterations(res.iterations), runtime(res.runtime), eps(res.eps)
	{}

	std::string toString() {
		std::stringstream ss;
		ss << surface.toString() << std::endl;
		return ss.str();
	}

	std::string benchmark() {
		std::stringstream ss;
		ss << num_threads << "," << iterations << "," << runtime << "," << surface.cols() << "," << eps << std::endl;
		return ss.str();
	}
};

Matrix solveDirichletSerial(size_t N=98, double eps=0.0001);
DirichletResult solveDirichletParallel(size_t N=98, double eps=0.0001);

#endif // __FUNCTIONS_H__
