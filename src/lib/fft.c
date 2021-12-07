/**
 * Implementation for FFT and IFFT functions for Nodesynth's built-in FFT lib
 *
 * By Josh Jeppson
 *
 * Note: This took me a grand total of 26 lines in Python
 * */

#include "fft.h"

#include <stdlib.h>
#include <math.h>

double *
fft(double * buffer, uint64_t size) {
	complex * complexBuffer = malloc(sizeof(complex) * size);
	uint64_t i = 0;
	for (; i < size; i++) {
		complexBuffer[i] = CMPLX(buffer[i], 0);
	}
	complex * freqComplex = fft_complex(complexBuffer, size);
	free(complexBuffer);
	double * fDomain = malloc(sizeof(double) * size);
	for (i = 0; i < size; i++) {
		fDomain[i] = cabs(freqComplex[i]);
	}
	free(freqComplex);
	return fDomain;
}

double *
ifft(double * buffer, uint64_t size) {
	complex * complexBuffer = malloc(sizeof(complex) * size);
	uint64_t i = 0;
	for (; i < size; i++) {
		complexBuffer[i] = CMPLX(buffer[i], 0);
	}
	complex * timeComplex = ifft_complex(complexBuffer, size);
	free(complexBuffer);
	double * tDomain = malloc(sizeof(double) * size);
	for (i = 0; i < size; i++) {
		tDomain[i] = cabs(timeComplex[i]);
	}
	free(timeComplex);
	return tDomain;
}

complex *
fft_complex(complex * buffer, uint64_t size) {
	// Create omega array for the first size primitive roots of unity
	complex * omega = malloc(sizeof(complex) * size);
	uint64_t i = 0;
	for (; i < size; i++) {
		omega[i] = CMPLX(
			cos(2 * M_PI * i)
			, sin(2 * M_PI * i)
		);
	}
	complex * freqDomain = fft_helper(buffer, omega, size);
	free(omega);
	return freqDomain;
}

complex *
ifft_complex(complex * buffer, uint64_t size) {
	// For the inverse fft, the angle in the complex plane is inverted
	// from that of the regular fft
	complex * omega = malloc(sizeof(complex) * size);
	for (; i < size; i++) {
		omega[i] = CMPLX(
			cos(2 * M_PI * i)
			, -sin(2 * M_PI * i)
		);
	}
	complex * timeDomain = fft_helper(buffer, omega, size);
	free(omega);
	// The IFFT must be reverse-scaled back down by n (the size)
	for (i = 0; i < size; i++) {
		timeDomain[i] /= size;
	}
	return timeDomain;
}

complex *
fft_helper(complex * buffer, complex * omega, uint64_t size) {
	complex * even = malloc(sizeof(complex) * size / 2);
	complex * odd  = malloc(sizeof(complex) * size / 2);
	complex * omegaHalf = malloc(sizeof(complex) * size / 2);
	uint64_t i = 0;
	for (; i < size / 2; i++) {
		// Get the even and odd elements
		even[i] = buffer[i * 2];
		odd[i]  = buffer[i * 2 + 1];
		// Square the elements in the first half of the omega array
		omegaHalf[i] = omega[i] * omega[i];
	}

	complex * solution_even = fft_helper(even, omegaHalf, size / 2);
	complex * solution_odd  = fft_helper(odd,  omegaHalf, size / 2);
	// Free memory before we forget
	free(even);
	free(odd);
	free(omegaHalf);
	// Re-combine the even and odd solutions of the FFT
	complex * solution = malloc(sizeof(complex) * size);
	for (i = 0; i < size / 2; i++) {
		solution[i] = solution_even[i] + omega[i] * solution_odd[i];
		solution[i + (size / 2)] = solution_even[i] - omega[i] * solution_odd[i];
	}
	free(solution_even);
	free(solution_odd);
	return solution;
}


