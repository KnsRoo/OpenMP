#!/bin/bash
#SBATCH --job-name=dirich
#SBATCH --output=result.txt
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=15:00
#SBATCH --mem-per-cpu=100

max_threads=20
step=1

dim=(100 500 1000 2000)
for ((omp_threads=1;omp_threads<=$max_threads;omp_threads+=step))
do
	export OMP_NUM_THREADS=$omp_threads
	for d in ${dim[@]}
	do
		./main  $d > "result_${omp_threads}_$d.txt"
	done
done