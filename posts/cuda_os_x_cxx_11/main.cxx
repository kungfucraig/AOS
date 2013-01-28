

#include <iostream>
#include <vector>
#include <cuda_runtime.h>

//! This is a simplified error checking function derived 
//! from the helper functions provided with NVIDIA's samples.
static void check(cudaError_t error, const char* file, int line)
{
   if ( error != 0)
   {
      std::cerr << "Error(" << error << ") at " << file << ":" << line << std::endl;
      exit(1);
   }
}
#define CHECK(val)  check((val),  __FILE__, __LINE__)


//! Our kernel that is defined in the other file.
extern "C" cudaError_t runKernel(int len, float* dataDEV);

//! Make sure we use some C++ 11 stuff to emphasize the fact we actually can.
int main()
{
   //! Setup inputs.
   typedef float DataType;
   const int len = 10;
   std::vector<DataType> dataH;
   for ( size_t i = 0; i < len; ++i ) dataH.push_back(i);

   //! Intialize the device.
   cudaSetDevice(0);
   
   //! Allocate device memory and copy from host.
   //! Note: C++-98 does not support call to std::vector::data()
   const unsigned int memSize = sizeof(DataType) * len;
   DataType *dataD;
   CHECK(cudaMalloc((void **) &dataD, memSize));
   CHECK(cudaMemcpy(dataD, dataH.data(), memSize, cudaMemcpyHostToDevice));

   //! Run the device code.
   cudaError_t err = runKernel(len, dataD);
   CHECK(err);
   
   //! Copy back to host and free.
   CHECK(cudaMemcpy(dataH.data(), dataD, memSize, cudaMemcpyDeviceToHost));
   CHECK(cudaFree(dataD));
   
   //! Echo our results using C++-11 style iteration.
   for ( float f : dataH )
   {
      std::cout << f << std::endl;
   }
}
