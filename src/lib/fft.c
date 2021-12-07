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
	cplx * cplxBuffer = malloc(sizeof(cplx) * size);
	uint64_t i = 0;
	for (; i < size; i++) {
		cplxBuffer[i] = CMPLX(buffer[i], 0);
	}
	cplx * freqcplx = fft_cplx(cplxBuffer, size);
	free(cplxBuffer);
	double * fDomain = malloc(sizeof(double) * size);
	for (i = 0; i < size; i++) {
		fDomain[i] = cabs(freqcplx[i]);
	}
	free(freqcplx);
	return fDomain;
}

double *
ifft(double * buffer, uint64_t size) {
	cplx * cplxBuffer = malloc(sizeof(cplx) * size);
	uint64_t i = 0;
	for (; i < size; i++) {
		cplxBuffer[i] = CMPLX(buffer[i], 0);
	}
	cplx * timecplx = ifft_cplx(cplxBuffer, size);
	free(cplxBuffer);
	double * tDomain = malloc(sizeof(double) * size);
	for (i = 0; i < size; i++) {
		tDomain[i] = cabs(timecplx[i]);
	}
	free(timecplx);
	return tDomain;
}

cplx *
fft_cplx(cplx * buffer, uint64_t size) {
	// Create omega array for the first size primitive roots of unity
	cplx * omega = malloc(sizeof(cplx) * size);
	uint64_t i = 0;
	for (; i < size; i++) {
		omega[i] = CMPLX(
			cos(2 * M_PI * i)
			, sin(2 * M_PI * i)
		);
	}
	cplx * freqDomain = fft_helper(buffer, omega, size);
	free(omega);
	return freqDomain;
}

cplx *
ifft_cplx(cplx * buffer, uint64_t size) {
	// For the inverse fft, the angle in the cplx plane is inverted
	// from that of the regular fft
	cplx * omega = malloc(sizeof(cplx) * size);
	for (; i < size; i++) {
		omega[i] = CMPLX(
			cos(2 * M_PI * i)
			, -sin(2 * M_PI * i)
		);
	}
	cplx * timeDomain = fft_helper(buffer, omega, size);
	free(omega);
	// The IFFT must be reverse-scaled back down by n (the size)
	for (i = 0; i < size; i++) {
		timeDomain[i] /= size;
	}
	return timeDomain;
}

cplx *
fft_helper(cplx * buffer, cplx * omega, uint64_t size) {
	cplx * even = malloc(sizeof(cplx) * size / 2);
	cplx * odd  = malloc(sizeof(cplx) * size / 2);
	cplx * omegaHalf = malloc(sizeof(cplx) * size / 2);
	uint64_t i = 0;
	for (; i < size / 2; i++) {
		// Get the even and odd elements
		even[i] = buffer[i * 2];
		odd[i]  = buffer[i * 2 + 1];
		// Square the elements in the first half of the omega array
		omegaHalf[i] = omega[i] * omega[i];
	}

	cplx * solution_even = fft_helper(even, omegaHalf, size / 2);
	cplx * solution_odd  = fft_helper(odd,  omegaHalf, size / 2);
	// Free memory before we forget
	free(even);
	free(odd);
	free(omegaHalf);
	// Re-combine the even and odd solutions of the FFT
	cplx * solution = malloc(sizeof(cplx) * size);
	for (i = 0; i < size / 2; i++) {
		solution[i] = solution_even[i] + omega[i] * solution_odd[i];
		solution[i + (size / 2)] = solution_even[i] - omega[i] * solution_odd[i];
	}
	free(solution_even);
	free(solution_odd);
	return solution;
}


