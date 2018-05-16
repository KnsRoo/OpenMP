#!/bin/bash
#SBATCH --job-name=mulMatrix
#SBATCH --output=result.csv
#SBATCH --ntasks=1
#
#SBATCH --cpus-per-task=20
#
#SBATCH --time=15:00
#SBATCH --mem-per-cpu=100


num_for_repeat=5

echo "Threads,Dimension,InitTime,MultTime,RunTime"

for omp_threads in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do

export OMP_NUM_THREADS=$omp_threads

for dim in 400 800 1200 1600 2000 2400 2800 
do
	for ((i=0; i < $num_for_repeat; i++))
	do
		./../main $dim
	done
done

done