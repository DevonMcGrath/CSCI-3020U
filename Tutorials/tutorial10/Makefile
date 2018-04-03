.PHONY: q2 q3
all:
	mpicc -Wall -Wextra -std=c99 q2.c -o q2 -lm
	mpicc -Wall -Wextra -std=c99 q3.c -o q3 -lm
q2:
	mpiexec -np ${NP} ./q2
q3:
	mpiexec -np ${NP} ./q3
q4:
	mpiexec -mp ${NP} ./q4
