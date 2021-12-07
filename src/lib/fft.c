#include "fft.h"

#include <stdlib.h>

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

}

complex *
ifft_complex(complex * buffer, uint64_t size) {

}

