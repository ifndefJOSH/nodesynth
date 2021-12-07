#ifndef NODESYNTH_FFT_H_INCLUDED
#define NODESYNTH_FFT_H_INCLUDED

#include <stdint.h>

double * fft(double * buffer, uint64_t size);
double * ifft(double * buffer, uint64_t size);

// Helper functions using the complex type
complex * fft(complex * buffer, uint64_t size);
complex * ifft(complex * buffer, uint64_t size);

#endif // NODESYNTH_FFT_H_INCLUDED
