#include "fft_test.h"

#include "../../src/lib/fft.h"

// #include <random.h>
#include <stdlib.h>
#include <time.h> // For timing to see how we are going to contribute to latency
#include <stdio.h>
#include <complex.h>

#define TEST_ITERATIONS 200
#define UPPER_BOUND 10

double *
random_array(int len) {
	double * arr = malloc(sizeof(double) * len);
	for (int i = 0; i < len; i++) {
		arr[i] = rand() / (RAND_MAX / UPPER_BOUND);
	}
	return arr;
}

cplx *
random_cplx_array(int len) {
	cplx * arr = malloc(sizeof(cplx) * len);
	for (int i = 0; i < len; i++) {
		arr[i] = CMPLX(
			rand() / (RAND_MAX / UPPER_BOUND)
			, rand() / (RAND_MAX / UPPER_BOUND)
		);
	}
	return arr;
}

void
fft_ifft_test() {
	for (int i = 0; i < TEST_ITERATIONS; i++) {
		for (int size = 0b100000; size < 0b1000000000000; size *= 2) {
			// Measure time taken by fft
			double * time_domain = random_array(size);
			clock_t fft_start = clock();
			double * freq_domain = fft(time_domain, size);
			clock_t fft_end = clock();
			fprintf(
				stderr
				, "Time taken to compute the FFT for a double array of size %d was %f s"
				, size
				, (float) (fft_end - fft_start) / CLOCKS_PER_SEC
			);
			// Measure time taken by the ifft
			clock_t ifft_start = clock();
			double * time_domain_two = ifft(freq_domain, size);
			clock_t ifft_end = clock();
			fprintf(
				stderr
				, "Time taken to compute the IFFT for a double array of size %d was %f s"
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
