NVCC=/Developer/NVIDIA/CUDA-5.0/bin/nvcc 
NVCC_FLAGS=-m64 -cuda 
#NVCC_ARCH_FLAGS=-gencode arch=compute_10,code=sm_10 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35
NVCC_ARCH_FLAGS=-gencode arch=compute_30,code=sm_30
CUDA_ROOT=/Developer/NVIDIA/CUDA-5.0
NVCC_IFLAGS=-I$(CUDA_ROOT)/include -I$(CUDA_ROOT)/samples/common/inc

CXX_11_FLAGS=-std=c++11 -stdlib=libc++ -g
CLANG_CFLAGS=$(NVCC_IFLAGS) $(CXX_11_FLAGS)
CLANG_LFLAGS=-Xlinker -rpath $(CUDA_ROOT)/lib -L/Developer/NVIDIA/CUDA-5.0/lib $(CXX_11_FLAGS) -lcudart 
CLANG=clang++
#CLANG=g++

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

