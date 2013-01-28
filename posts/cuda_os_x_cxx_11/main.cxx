// Copyright (c) 2013 Craig Wright (kungfucraig@gmail.com)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
// Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
   //! std::vector::data() is new in C++-11
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
