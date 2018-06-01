#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <stdexcept>
#include <omp.h>

#include "Matrix.h"
#include "functions.h"


int main(int argc, char* argv[]) {

	size_t N = 100;
	double EPS = 0.001;

	if (argc > 1) {
		std::istringstream ss(argv[1]);
		int n;
		if (ss >> n){
			N = n;
		}
	} 

	DirichletResult res = solveDirichletParallel(N - 2, EPS);

	std::cout << res.benchmark();
	std::cout << res.toString();

	// auto startTime = std::chrono::steady_clock::now();

	// size_t rows = 0, cols = 0;
	// if (argc > 1) {
	// 	std::istringstream ss(argv[1]);
	// 	int dim;
	// 	if (ss >> dim){
	// 		rows = dim;
	// 		cols = dim;
	// 	}
	// } 
	// else {
	// 	rows = 100;
	// 	cols = 100;
	// }

	// Matrix A = Matrix::rand(rows, cols);
	// Matrix B = Matrix::eye(rows, cols);
	// Matrix C(rows, cols);

	// auto initTime = std::chrono::steady_clock::now();

	// C = A * B;

	// auto mulTime = std::chrono::steady_clock::now();

	// auto initDuration = std::chrono::duration_cast<std::chrono::duration<double>>(initTime - startTime);
	// auto mulDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - initTime);
	// auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

	// printCSV(omp_get_max_threads(), rows, initDuration.count(), mulDuration.count(), runtimeDuration.count());

	return 0;
}
