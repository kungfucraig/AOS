CUDA_ROOT=/Developer/NVIDIA/CUDA-5.0

NVCC=$(CUDA_ROOT)/bin/nvcc 
NVCC_FLAGS=-m64 -cuda 
NVCC_ARCH_FLAGS=-gencode arch=compute_30,code=sm_30
NVCC_IFLAGS=-I$(CUDA_ROOT)/include 

CXX_11_FLAGS=-std=c++11 -stdlib=libc++ -g
CLANG_CFLAGS=$(NVCC_IFLAGS) $(CXX_11_FLAGS)
CLANG_LFLAGS=-Xlinker -rpath $(CUDA_ROOT)/lib -L$(CUDA_ROOT)/lib $(CXX_11_FLAGS) -lcudart 
CLANG=clang++

GCC_CFLAGS=$(NVCC_IFLAGS) -g
GCC=g++


all: main Makefile

square.cu.cxx: square.cu Makefile
	$(NVCC) $(NVCC_FLAGS) $(NVCC_ARCH_FLAGS) $(NVCC_IFLAGS) square.cu -o square.cu.cxx

square.o: square.cu.cxx Makefile
	$(GCC) $(GCC_CFLAGS) -c square.cu.cxx -o square.o

main.o: main.cxx Makefile
	$(CLANG) $(CLANG_CFLAGS) -c main.cxx -o main.o

main: square.o  main.o
	$(CLANG) $(CLANG_LFLAGS) square.o main.o -o main


clean:
	rm -f *.o main square.cu.cxx

