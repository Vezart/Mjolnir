//============================================================
//  File:       im_cuda.cu
//  Author:     John Gauch
//  Date:       Summer 2010
//============================================================

#include <stdio.h>
#include <math.h>
#include <cuda.h>

#define PIXEL(x,y) ( (((y)+ydim)%ydim)*xdim + ((x)+xdim)%xdim )

// Global variables for timers
#define CUDA_TIMER
#ifdef CUDA_TIMER
cudaEvent_t cuda_start;
cudaEvent_t cuda_stop;
float cuda_time;
#endif

//============================================================
void query_cuda()
{
    // Get number of CUDA devices
    int devCount;
    cudaGetDeviceCount(&devCount);
    printf("There are %d CUDA devices.\n", devCount);

    // Iterate through CUDA devices
    for (int i = 0; i < devCount; ++i)
    {
        // Get CUDA device properties
        printf("\nCUDA Device #%d\n", i);
        cudaDeviceProp devProp;
        cudaGetDeviceProperties(&devProp, i);

        // Print CUDA device properties
        printf("Major revision number:         %d\n",  (int)devProp.major);
        printf("Minor revision number:         %d\n",  (int)devProp.minor);
        printf("Name:                          %s\n",  devProp.name);
        printf("Total global memory:           %d\n",  (int)devProp.totalGlobalMem);
        printf("Total shared memory per block: %d\n",  (int)devProp.sharedMemPerBlock);
        printf("Total registers per block:     %d\n",  (int)devProp.regsPerBlock);
        printf("Warp size:                     %d\n",  (int)devProp.warpSize);
        printf("Maximum memory pitch:          %d\n",  (int)devProp.memPitch);
        printf("Maximum threads per block:     %d\n",  (int)devProp.maxThreadsPerBlock);
        for (int i = 0; i < 3; ++i)
           printf("Maximum dimension %d of block:  %d\n", i, (int)devProp.maxThreadsDim[i]);
        for (int i = 0; i < 3; ++i)
           printf("Maximum dimension %d of grid:   %d\n", i, (int)devProp.maxGridSize[i]);
        printf("Clock rate:                    %d\n",  (int)devProp.clockRate);
        printf("Total constant memory:         %d\n",  (int)devProp.totalConstMem);
        printf("Texture alignment:             %d\n",  (int)devProp.textureAlignment);
        printf("Concurrent copy and execution: %s\n",  (devProp.deviceOverlap ? "Yes" : "No"));
        printf("Number of multiprocessors:     %d\n",  (int)devProp.multiProcessorCount);
        printf("Kernel execution timeout:      %s\n",  (devProp.kernelExecTimeoutEnabled ? "Yes" : "No"));
    }
}

//============================================================
void create_timer()
{
#ifdef CUDA_TIMER
   cudaEventCreate(&cuda_start);
   cudaEventCreate(&cuda_stop);
#endif
}

//============================================================
void destroy_timer()
{
#ifdef CUDA_TIMER
   cudaEventDestroy(cuda_start);
   cudaEventDestroy(cuda_stop);
#endif
}

//============================================================
void start_timer()
{
#ifdef CUDA_TIMER
   cudaEventRecord(cuda_start,0);
#endif
}

//============================================================
void end_timer(char *str)
{
#ifdef CUDA_TIMER
   cudaEventRecord(cuda_stop,0);
   cudaEventSynchronize(cuda_stop);
   cudaEventElapsedTime(&cuda_time, cuda_start, cuda_stop);
   printf("%s: %f\n", str, cuda_time/1000);
#endif
}

//============================================================
void cuda_config(int length, int &thread_cnt, int &block_cnt)
{
   thread_cnt = 0;
   block_cnt = 0;
   cudaDeviceProp devProp;
   if (cudaGetDeviceProperties(&devProp, 0) != cudaSuccess) return;
   thread_cnt = devProp.maxThreadsPerBlock / 4;
   block_cnt = length / thread_cnt;
   if (block_cnt * thread_cnt < length) block_cnt++;
   // printf("thread_cnt=%d, block_cnt=%d\n", thread_cnt, block_cnt);
}

//============================================================
__global__ void binomial_kernel(float *cu_in, float *cu_out, int xdim, int ydim)
{
   // get (x,y) coordinates
   int pixel = blockIdx.x*blockDim.x + threadIdx.x;
   if (pixel > xdim * ydim) return;
   int x = pixel % xdim;
   int y = pixel / xdim;

   cu_out[PIXEL(x,y)] 
      = (cu_in[PIXEL(x+1,y+1)] 
      + cu_in[PIXEL(x+1,y)] * 2
      + cu_in[PIXEL(x+1,y-1)]
      + cu_in[PIXEL(x,y+1)] * 2
      + cu_in[PIXEL(x,y)] * 4
      + cu_in[PIXEL(x,y-1)] * 2
      + cu_in[PIXEL(x-1,y+1)] 
      + cu_in[PIXEL(x-1,y)] * 2
      + cu_in[PIXEL(x-1,y-1)]) / (float)16.0;
}

//============================================================
float* binomial_cuda(float *data, int count, int xdim, int ydim)
{
   // declare variables
   float *cu_in;  
   float *cu_out;
   int length = xdim*ydim;
   size_t size_in = length*sizeof(float);
   size_t size_out = length*sizeof(float);
   int thread_cnt, block_cnt;
   cuda_config(length, thread_cnt, block_cnt);
   dim3 blocks(block_cnt, 1, 1);
   dim3 threads(thread_cnt, 1, 1);

   // allocate array on device
   create_timer();
   cudaMalloc((void **) &cu_in, size_in);
   cudaMalloc((void **) &cu_out, size_out);

   // copy data from host to device
   start_timer();
   cudaMemcpy(cu_in, data,  size_in, cudaMemcpyHostToDevice);
   end_timer("Copy memory to device");

   // run kernel
   start_timer();
   while (count >= 2)
   {
      binomial_kernel <<< blocks, threads >>> (cu_in, cu_out, xdim, ydim);
      binomial_kernel <<< blocks, threads >>> (cu_out, cu_in, xdim, ydim);
      count -= 2;
   }
   if (count == 1)
      binomial_kernel <<< blocks, threads >>> (cu_in, cu_out, xdim, ydim);
   end_timer("Run kernel");

   // copy data from device to host
   start_timer();
   if (count == 1)
      cudaMemcpy(data, cu_out,  size_out, cudaMemcpyDeviceToHost);
   else
      cudaMemcpy(data, cu_in,  size_in, cudaMemcpyDeviceToHost);
   end_timer("Copy memory from device");

   // cleanup
   cudaFree(cu_in);
   cudaFree(cu_out);
   destroy_timer();
   return data;
}

//============================================================
__global__ void binomial_kernel(short *cu_in, short *cu_out, int xdim, int ydim)
{
   // get (x,y) coordinates
   int pixel = blockIdx.x*blockDim.x + threadIdx.x;
   if (pixel > xdim * ydim) return;
   int x = pixel % xdim;
   int y = pixel / xdim;

   cu_out[PIXEL(x,y)] 
      = (cu_in[PIXEL(x+1,y+1)] 
      + cu_in[PIXEL(x+1,y)] * 2
      + cu_in[PIXEL(x+1,y-1)]
      + cu_in[PIXEL(x,y+1)] * 2
      + cu_in[PIXEL(x,y)] * 4
      + cu_in[PIXEL(x,y-1)] * 2
      + cu_in[PIXEL(x-1,y+1)] 
      + cu_in[PIXEL(x-1,y)] * 2
      + cu_in[PIXEL(x-1,y-1)] + 8) / 16;
}

//============================================================
short* binomial_cuda(short *data, int count, int xdim, int ydim)
{
   // declare variables
   short *cu_in;  
   short *cu_out;
   int length = xdim*ydim;
   size_t size_in = length*sizeof(short);
   size_t size_out = length*sizeof(short);
   int thread_cnt, block_cnt;
   cuda_config(length, thread_cnt, block_cnt);
   dim3 blocks(block_cnt, 1, 1);
   dim3 threads(thread_cnt, 1, 1);

   // allocate array on device
   create_timer();
   cudaMalloc((void **) &cu_in, size_in);
   cudaMalloc((void **) &cu_out, size_out);

   // copy data from host to device
   start_timer();
   cudaMemcpy(cu_in, data, size_in, cudaMemcpyHostToDevice);
   end_timer("Copy memory to device");

   // run kernel
   start_timer();
   while (count >= 2)
   {
      binomial_kernel <<< blocks, threads >>> (cu_in, cu_out, xdim, ydim);
      binomial_kernel <<< blocks, threads >>> (cu_out, cu_in, xdim, ydim);
      count -= 2;
   }
   if (count == 1)
      binomial_kernel <<< blocks, threads >>> (cu_in, cu_out, xdim, ydim);
   end_timer("Run kernel");

   // copy data from device to host
   start_timer();
   if (count == 1)
      cudaMemcpy(data, cu_out, size_out, cudaMemcpyDeviceToHost);
   else
      cudaMemcpy(data, cu_in, size_in, cudaMemcpyDeviceToHost);
   end_timer("Copy memory from device");

   // cleanup
   cudaFree(cu_in);
   cudaFree(cu_out);
   destroy_timer();
   return data;
}

//============================================================
__global__ void gradient_kernel(float *cu_in, float *cu_out, int xdim, int ydim)
{
   // get (x,y) coordinates
   int pixel = blockIdx.x*blockDim.x + threadIdx.x;
   if (pixel > xdim * ydim) return;
   int x = pixel % xdim;
   int y = pixel / xdim;

   float dx 
      = cu_in[PIXEL(x+1,y+1)] 
      + cu_in[PIXEL(x+1,y)] * 2
      + cu_in[PIXEL(x+1,y-1)]
      - cu_in[PIXEL(x-1,y+1)]
      - cu_in[PIXEL(x-1,y)] * 2
      - cu_in[PIXEL(x-1,y-1)];
   float dy 
      = cu_in[PIXEL(x+1,y+1)] 
      + cu_in[PIXEL(x,y+1)] * 2
      + cu_in[PIXEL(x-1,y+1)]
      - cu_in[PIXEL(x+1,y-1)]
      - cu_in[PIXEL(x,y-1)] * 2
      - cu_in[PIXEL(x-1,y-1)];

   if (dx < 0) dx = -dx;
   if (dy < 0) dy = -dy;
   cu_out[PIXEL(x,y)] = (dx+dy) / (float)8.0;
}

//============================================================
float* gradient_cuda(float *data, int xdim, int ydim)
{
   // declare variables
   float *cu_in;  
   float *cu_out;
   int length = xdim*ydim;
   size_t size_in = length*sizeof(float);
   size_t size_out = length*sizeof(float);
   int thread_cnt, block_cnt;
   cuda_config(length, thread_cnt, block_cnt);
   dim3 blocks(block_cnt, 1, 1);
   dim3 threads(thread_cnt, 1, 1);

   // allocate array on device
   create_timer();
   cudaMalloc((void **) &cu_in, size_in);
   cudaMalloc((void **) &cu_out, size_out);

   // copy data from host to device
   start_timer();
   cudaMemcpy(cu_in, data, size_in, cudaMemcpyHostToDevice);
   end_timer("Copy memory to device");

   // run kernel
   start_timer();
   gradient_kernel <<< blocks, threads >>> (cu_in, cu_out, xdim, ydim);
   end_timer("Run kernel");

   // copy data from device to host
   start_timer();
   cudaMemcpy(data, cu_out, size_out, cudaMemcpyDeviceToHost);
   end_timer("Copy memory from device");

   // cleanup
   cudaFree(cu_in);
   cudaFree(cu_out);
   return data;
}

//============================================================
__global__ void gradient_kernel(short *cu_in, short *cu_out, int xdim, int ydim)
{
   // get (x,y) coordinates
   int pixel = blockIdx.x*blockDim.x + threadIdx.x;
   if (pixel > xdim * ydim) return;
   int x = pixel % xdim;
   int y = pixel / xdim;

   int dx 
      = cu_in[PIXEL(x+1,y+1)] 
      + cu_in[PIXEL(x+1,y)] * 2
      + cu_in[PIXEL(x+1,y-1)]
      - cu_in[PIXEL(x-1,y+1)]
      - cu_in[PIXEL(x-1,y)] * 2
      - cu_in[PIXEL(x-1,y-1)];
   int dy 
      = cu_in[PIXEL(x+1,y+1)] 
      + cu_in[PIXEL(x,y+1)] * 2
      + cu_in[PIXEL(x-1,y+1)]
      - cu_in[PIXEL(x+1,y-1)]
      - cu_in[PIXEL(x,y-1)] * 2
      - cu_in[PIXEL(x-1,y-1)];

   if (dx < 0) dx = -dx;
   if (dy < 0) dy = -dy;
   cu_out[PIXEL(x,y)] = (dx+dy) / 8;
}

//============================================================
short* gradient_cuda(short *data, int xdim, int ydim)
{
   // declare variables
   short *cu_in;  
   short *cu_out;
   int length = xdim*ydim;
   size_t size_in = length*sizeof(short);
   size_t size_out = length*sizeof(short);
   int thread_cnt, block_cnt;
   cuda_config(length, thread_cnt, block_cnt);
   dim3 blocks(block_cnt, 1, 1);
   dim3 threads(thread_cnt, 1, 1);

   // allocate array on device
   create_timer();
   cudaMalloc((void **) &cu_in, size_in);
   cudaMalloc((void **) &cu_out, size_out);

   // copy data from host to device
   start_timer();
   cudaMemcpy(cu_in, data, size_in, cudaMemcpyHostToDevice);
   end_timer("Copy memory to device");

   // run kernel
   start_timer();
   gradient_kernel <<< blocks, threads >>> (cu_in, cu_out, xdim, ydim);
   end_timer("Run kernel");

   // copy data from device to host
   start_timer();
   end_timer("Copy memory from device");
   cudaMemcpy(data, cu_out, size_out, cudaMemcpyDeviceToHost);

   // cleanup
   cudaFree(cu_in);
   cudaFree(cu_out);
   return data;
}

