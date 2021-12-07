#ifndef FFT_TEST_H_INCLUDED
#define FFT_TEST_H_INCLUDED

#include "../../src/lib/fft.h"

#include <complex.h>

double * random_array(int len);
complex * random_complex_array(int len);

void fft_ifft_test();

#endif // FFT_TEST_H_INCLUDED
