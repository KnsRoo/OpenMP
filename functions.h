#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Matrix.h"


void benchmarkPrint(size_t dim, double initDuration, double mulDuration, double runtimeDuration);
void printCSV(int threads, size_t dim, double initDuration, double mulDuration, double runtimeDuration);


#endif // __FUNCTIONS_H__
