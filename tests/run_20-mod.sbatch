#!/bin/bash
#SBATCH --job-name=mulMatrix
#SBATCH --output=result.txt
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=30:00
#SBATCH --mem-per-cpu=100


num_for_repeat=5

echo "Threads,Dimension,InitTime,MultTime,RunTime" > result_1.csv
echo "Threads,Dimension,InitTime,MultTime,RunTime" > result_2.csv

for omp_threads in 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do

export OMP_NUM_THREADS=$omp_threads

for dim in 300 600 900 1500 2000 2500 2900 
do
	for ((i=0; i < $num_for_repeat; i++))
	do
		./../main_1 $dim >> result_1.csv
		./../main_2 $dim >> result_2.csv
	done
done

done
