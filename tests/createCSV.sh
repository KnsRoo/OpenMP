#!/bin/bash

num_for_repeat=3

echo "Threads,Dimension,InitTime,MultTime,RunTime" > result_1.csv
echo "Threads,Dimension,InitTime,MultTime,RunTime" > result_2.csv

for omp_threads in 1 2 3 4
do
	export OMP_NUM_THREADS=$omp_threads
	for dim in 100 200 300 400
	do
		for ((i=0; i < $num_for_repeat; i++))
		do
		./../main_1 $dim >> result_1.csv
		./../main_2 $dim >> result_2.csv
		done
	done
done