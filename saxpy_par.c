/**
David Gómez Vargas
2015028430
Arquitectura de Computadores II
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <arm_neon.h>

int saxpy(int16_t *x, int16_t *y, int16_t *z, int size)
{
  int16x4_t a = vdup_n_s16(5);
  double start_time, run_time;
  omp_set_num_threads(6);

  //Do the operation for size elements
  start_time = omp_get_wtime();
  #pragma omp parallel for
  for(int tmpSize = size; tmpSize > 0; tmpSize -= 4) {
    int16x4_t vecX;
    int16x4_t vecY;
    int16x4_t vecZ;
    vecX = vld1_s16(x);
    vecY = vld1_s16(y);
    x += 4;
    y += 4;
    vecZ = vmla_s16(vecY, vecX, a);
    vst1_s16(z, vecZ);
    z += 4;
  }

  run_time = omp_get_wtime() - start_time;
	printf("\n Tiempo con %d %f  \n", size, run_time);
}

int main () {
  srand(time(NULL));
  int size = 100000000;
  //Create the arrays
  int16_t *y = (int16_t *)malloc(sizeof(int16_t)*size);
  int16_t *x = (int16_t *)malloc(sizeof(int16_t)*size);
  int16_t *z = (int16_t *)malloc(sizeof(int16_t)*size);

  //Fill the arrays x and y
  for(int i = 0; i < size; i++) {
    y[i] = rand() % 1000;
    x[i] = rand() % 1000;
  }

  saxpy(x, y, z, size);
  size = 50000000;
  saxpy(x, y, z, size);
  size = 10000000;
  saxpy(x, y, z, size);
}
