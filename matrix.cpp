/**
David Gómez Vargas
2015028430
Arquitectura de Computadores II
*/

#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <arm_neon.h>

int calc(int16_t *A, int16_t *B, int16_t *C, int size)
{
	double start_time, run_time;
	omp_set_num_threads(8);
	start_time = omp_get_wtime();
	//Do the operation
	int16_t *tmp = C;
	# pragma omp parallel for
	for(int k = size; k > 0; k -= 4) {
		int16x4_t vecA;
		A += 4;
		vecA = vld1_s16(A);
		for(int j = size; j > 0; j -= 4) {
	    int16x4_t vecB;
	    int16x4_t vecC;
	    vecB = vld1_s16(B);
	    B += 4;
	    vecC = vmla_s16(vecC, vecA, vecB);
	    vst1_s16(C, vecC);
	    C += 4;
		}
		C = tmp;
}

	run_time = omp_get_wtime() - start_time;
	printf("\n Tiempo %f segundos \n", run_time);
}

int main (){
	int N = 10000;
	int16_t *A = (int16_t *)malloc(sizeof(int16_t)*N*N);
	int16_t *B = (int16_t *)malloc(sizeof(int16_t)*N*N);
	int16_t *C = (int16_t *)malloc(sizeof(int16_t)*N*N);

	//Fill the square matrices
  for(int i = 0; i < N * N; i++) {
    A[i] = rand() % 1000;
    B[i] = rand() % 1000;
  }

	calc(A,B,C,N);

}
