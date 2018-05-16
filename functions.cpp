#include "functions.h"

#include <iostream>


void benchmarkPrint(size_t dim, double initDuration, double mulDuration, double runtimeDuration) {
	std::cout.setf(std::ios::fixed);
	std::cout.precision(6);
	std::cout << "║ " << dim << "\t" << initDuration << "\t" << mulDuration << "\t" << runtimeDuration << "\t" << "║" << std::endl;
}

void printCSV(int threads, size_t dim, double initDuration, double mulDuration, double runtimeDuration) {
	std::cout << threads << "," << dim << "," << initDuration << "," << mulDuration << "," << runtimeDuration << std::endl;
}
