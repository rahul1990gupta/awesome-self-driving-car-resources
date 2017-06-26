#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int nReps = 500;

void time_kernel(char* label, void (*fptr)(int, int, float*, float*),  int rows, int cols, float * in, float * out);
void time_kernel_acc(char* label, void (*fptr)(int, int, float*, float*),  int rows, int cols, float * in, float * out);

void referenceTranspose(int rows, int cols, float * in, float * out)
{
  #pragma omp parallel for collapse(2)
  for(int i=0; i<rows; i++)
  {
   #pragma omp parallel for
   for(int j=0; j<cols; j++)
    {
      out[i*rows + j] = in[j*cols + i];
    }
  }
}

void openACCTranspose(int rows, int cols, float *restrict in, float *restrict out)
{
  int i,j;
  
  #pragma acc parallel loop collapse(2) present(in,out)
  for(i=0; i<rows; i++)
  {
   for(j=0; j<cols; j++)
    {
      out[i*rows + j] = in[j*cols + i];
    }
  }
}

int main(int argc, char** argv)
{
  static int M = 1024;
  static int N = 1024;
  float * A = NULL;
  float * Atrans = NULL;
  A = (float*)malloc(M*N*sizeof(float));
  Atrans = (float*)malloc(M*N*sizeof(float));

  printf("OpenMP Processors: %d\n",omp_get_max_threads());

  // Initialize A to random values and zero Atrans
  for(int i=0; i<M*N; i++)
  {
    A[i] = rand() / (float)RAND_MAX;
  }
  memset(Atrans, 0, M*N*sizeof(float));

  time_kernel((char*)"CPU+OMP", referenceTranspose, M, N, A, Atrans);
  time_kernel_acc((char*)"CPU+OpenACC", openACCTranspose, M, N, A, Atrans);

  free(A);
  free(Atrans);
  return 0;
}

void time_kernel(char* label, void (*fptr)(int, int, float*, float*),  int rows, int cols, float * in, float * out) {
  double start, end;

  start = omp_get_wtime();
  for(int i=0; i<nReps; i++)
  {
    fptr(rows, cols, in, out);
  }
  end = omp_get_wtime();
  
  // Check the answer: return time only if answer is correct. This section part is not timed.
  float * validation = (float*)malloc(rows*cols*sizeof(float));
  referenceTranspose(rows, cols, in, validation);
  for(long i=0; i<rows*cols; i++)
  {
    if(out[i] != validation[i])
    {
      printf("Error: transpose result is incorrect at linear index %ld\n", i);
      return;
    }
  }
  free(validation);

  double kTime = (end - start)/((double) nReps);
  double kBandwidth = 2.0 * (double)(rows*cols*sizeof(float)) / (1000*1000*1000*kTime);
  printf("%s: Kernel bandwidth: %f gb/sec\n", label, kBandwidth);

}
void time_kernel_acc(char* label, void (*fptr)(int, int, float*, float*),  int rows, int cols, float * in, float * out) {
  double start, end;

#pragma acc data copyin(in[0:rows*cols]) copyout(out[0:rows*cols])
  {

  start = omp_get_wtime();
  for(int i=0; i<nReps; i++)
  {
    fptr(rows, cols, in, out);
  }
#pragma acc wait
  end = omp_get_wtime();
  }
  
  // Check the answer: return time only if answer is correct. This section part is not timed.
  float * validation = (float*)malloc(rows*cols*sizeof(float));
  referenceTranspose(rows, cols, in, validation);
  for(long i=0; i<rows*cols; i++)
  {
    if(out[i] != validation[i])
    {
      printf("Error: transpose result is incorrect at linear index %ld\n", i);
      return;
    }
  }
  free(validation);

  double kTime = (end - start)/((double) nReps);
  double kBandwidth = 2.0 * (double)(rows*cols*sizeof(float)) / (1000*1000*1000*kTime);
  printf("%s: Kernel bandwidth: %f gb/sec\n", label, kBandwidth);

}
