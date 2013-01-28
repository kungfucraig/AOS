
#include <cuda_runtime.h>
#include <stdio.h>

//! Square the data.
__global__ void
square(float *data)
{
   const unsigned int tid = threadIdx.x;
   float d = data[tid];
   data[tid] = d*d;
}

//! Provide a wrapper for the kernel.
extern "C"
cudaError_t runKernel(int len, float *dataD)
{
   dim3 grid(1, 1, 1);
   dim3 threads(len, 1, 1);
   square<<< grid, threads >>>(dataD);
   return cudaGetLastError();
}


