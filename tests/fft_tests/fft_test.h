#ifndef FFT_TEST_H_INCLUDED
#define FFT_TEST_H_INCLUDED

#include "../../src/lib/fft.h"

#include <complex.h>

typedef complex<double> cplx;

double * random_array(int len);
cplx * random_cplx_array(int len);

void fft_ifft_test();

#endif // FFT_TEST_H_INCLUDED
