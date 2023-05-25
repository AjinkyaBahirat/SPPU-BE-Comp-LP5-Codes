#include <stdio.h>

// Kernel function to perform vector addition
__global__ void vectorAddition(float* a, float* b, float* c, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (tid < size) {
        c[tid] = a[tid] + b[tid];
    }
}

int main() {
    int size = 1000000;  // Size of the vectors
    int numBytes = size * sizeof(float);

    // Allocate memory for vectors on host
    float* h_a = (float*)malloc(numBytes);
    float* h_b = (float*)malloc(numBytes);
    float* h_c = (float*)malloc(numBytes);

    // Initialize input vectors
    for (int i = 0; i < size; i++) {
        h_a[i] = i;
        h_b[i] = i;
    }

    // Allocate memory for vectors on device
    float* d_a;
    float* d_b;
    float* d_c;
    cudaMalloc((void**)&d_a, numBytes);
    cudaMalloc((void**)&d_b, numBytes);
    cudaMalloc((void**)&d_c, numBytes);

    // Copy input vectors from host to device
    cudaMemcpy(d_a, h_a, numBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, numBytes, cudaMemcpyHostToDevice);

    // Define block size and grid size
    int blockSize = 256;
    int gridSize = (size + blockSize - 1) / blockSize;

    // Launch the kernel
    vectorAddition<<<gridSize, blockSize>>>(d_a, d_b, d_c, size);

    // Copy result vector from device to host
    cudaMemcpy(h_c, d_c, numBytes, cudaMemcpyDeviceToHost);

    // Print the result
    for (int i = 0; i < size; i++) {
        printf("%f + %f = %f\n", h_a[i], h_b[i], h_c[i]);
    }

    // Free memory on device
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    // Free memory on host
    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}
