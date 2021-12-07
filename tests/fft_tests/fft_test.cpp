#include "fft_test.h"

#include "../../src/lib/fft.h"
#include "../jtest/jtest.h"

// #include <random.h>
#include <stdlib.h>
#include <time.h> // For timing to see how we are going to contribute to latency
#include <stdio.h>
#include <complex.h>

#define TEST_ITERATIONS 1 // 200
#define UPPER_BOUND 10

void
print_array(double * arr, int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		printf("%f, ", arr[i]);
	}
	printf("\b\b]\n");
}

double *
random_array(int len) {
	double * arr = new double[len]; // malloc(sizeof(double) * len);
	// printf("Generating random array of type double and length %d", len);
	for (int i = 0; i < len; i++) {
		arr[i] = rand() / (RAND_MAX / UPPER_BOUND);
	}
	// printf("...done\n.");
	return arr;
}

cplx *
random_cplx_array(int len) {
	cplx * arr = new cplx[len]; // malloc(sizeof(cplx) * len);
	// printf("Generating a random array of type std::complex<double> and length %d", len);
	for (int i = 0; i < len; i++) {
		arr[i] = cplx(
			rand() / (RAND_MAX / UPPER_BOUND)
			, rand() / (RAND_MAX / UPPER_BOUND)
		);
	}
	// printf("...done.\n");
	return arr;
}

void
fft_ifft_test() {
	printf("Starting fft_ifft_test()\n");
	for (int i = 0; i < TEST_ITERATIONS; i++) {
		// printf("Starting test for iteration %d\n", i);
		for (uint64_t size = 0b100; size < 0b1000; size *= 2) {
			// Measure time taken by fft
			double * time_domain = random_array(size);
			printf("Time domain:\n\t");
			print_array(time_domain, size);
			clock_t fft_start = clock();
			// printf("Starting fft for randomly generated array.\n");
			double * freq_domain = fft(time_domain, size);
			printf("Frequency domain:\n\t");
			print_array(freq_domain, size);
			clock_t fft_end = clock();
			fprintf(
				stderr
				, "Time taken to compute the FFT for a double array of size %d was %f s\n"
				, size
				, (float) (fft_end - fft_start) / CLOCKS_PER_SEC
			);
			// Measure time taken by the ifft
			clock_t ifft_start = clock();
			double * time_domain_two = ifft(freq_domain, size);
			clock_t ifft_end = clock();
			fprintf(
				stderr
				, "Time taken to compute the IFFT for a double array of size %d was %f s\n"
				, size
				, (float) (ifft_end - ifft_start) / CLOCKS_PER_SEC
			);
			// Assert the equality of the two arrays
			JTest<double>::assert_array_equal(time_domain, size, time_domain_two, size);
			// Free memory
			free(freq_domain);
			free(time_domain);
			free(time_domain_two);
		}
	}
}

int main(int argc, char ** argv) {
	fft_ifft_test();
	return 0;
}
