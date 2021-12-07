/**
 * Tiny Fourier transform library for use in Nodesynth
 *
 * By Josh Jeppson
 * */

#ifndef NODESYNTH_FFT_H_INCLUDED
#define NODESYNTH_FFT_H_INCLUDED

#include <stdint.h>

/**
 * Computes the DFT (Discrete Fourier Transform) using the FFT (Fast Fourier Transform) algorithm,
 * which is a divide and conquer algorithm of O(n) = n log(n). This wrapper takes a buffer in
 * double precision floating point. Converts to complex type and calls fft_complex. Requires
 * the buffer size to be a power of 2.
 *
 * @param buffer the buffer to transform into the frequency domain
 * @param size the number of elements in the buffer
 * @return the buffer transformed into frequency domain
 * */
double * fft(double * buffer, uint64_t size);

/**
 * Given the DFT (Discrete Fourier Transform), computes the inverse FFT, which is also an O(n) = n log(n)
 * algorithm. This wrapper takes a buffer in double precision floating point. Converts into complex
 * type and calls ifft_complex. Requires the buffer size to be a power of 2.
 *
 * @param buffer the buffer (in frequency domain) to transform into the time domain
 * @param size the number of elements in the buffer
 * @return the buffer transformed into time domain
 * */
double * ifft(double * buffer, uint64_t size);

// Helper functions using the complex type

/**
 * Computes the DFT (Discrete Fourier Transform) using the FFT (Fast Fourier Transform) algorithm,
 * which is a divide and conquer algorithm of O(n) = n log(n). This takes elements of type complex
 * and returns elements of type complex. Requires the buffer size to be a power of 2.
 *
 * @param buffer the buffer to transform into the frequency domain
 * @param size the number of elements in the buffer
 * @return the buffer transformed into frequency domain
 * */
complex * fft_complex(complex * buffer, uint64_t size);

/**
 * Given the DFT (Discrete Fourier Transform), computes the inverse FFT, which is also an O(n) = n log(n)
 * algorithm. This takes elements of type complex and returns elements of type complex. Requires the
 * buffer size to be a power of 2.
 *
 * @param buffer the buffer (in frequency domain) to transform into the time domain
 * @param size the number of elements in the buffer
 * @return the buffer transformed into time domain
 * */
complex * ifft_complex(complex * buffer, uint64_t size);

/**
 * Helper function that creates the actual FFT/IFFT. This function should probably not be used by
 * the end user, as it should only be called by fft_complex and ifft_complex. Assumes that the
 * buffer size is a power of 2. This function takes an omega array, which should contain
 * the primitive roots of unity.
 *
 * @param buffer Buffer to convert either in or out of the frequency domain
 * @param omega Omega array--contains primitive roots of unity
 * @param size The size of both the buffer and omega array
 * */
complex * fft_helper(complex * buffer, complex * omega, uint64_t size);

#endif // NODESYNTH_FFT_H_INCLUDED
