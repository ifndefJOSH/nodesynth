/* 
 * Compile with gcc oscillator.c -lfftw3 -lm -lsndfile
 * */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include <fftw3.h>
#include <sndfile.h>

#define SAMPLE_RATE 44100 // Samples / second
#define FALLOFF_AMOUNT 5

typedef uint8_t falloff_t;

// enum falloffTypes {
// 	EXPONENTIAL=1
// };

double * impulseResponseGenerator(double wetAmount, double tailLength, falloff_t falloffType) {
	uint64_t numSamples = (tailLength * SAMPLE_RATE);
	double * iResponse = calloc(numSamples, sizeof(double));
	/* Tail is defined as e^{-5} */
	int i = 0;
	double r = 1.0;
	for (; i < numSamples; i++) {
		r = sin(2 * M_PI * 440.0 * ((double) i / (double) SAMPLE_RATE));
		iResponse[i] = wetAmount * r * exp(-(double) i * (double) FALLOFF_AMOUNT / (double) numSamples);
	}
	return iResponse;
}

int main(int argc, char ** argv) {
	SF_INFO info;
	info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	info.channels = 1;
	info.samplerate = 44100;
	
	SNDFILE * outFile = sf_open(argv[1], SFM_WRITE, &info);
	if (outFile == NULL) {
		fprintf(stderr, "[INFO] Could not open file '%s': '%s'\n", argv[1], sf_strerror(outFile));
		return -1;
	}
	double * iResponse = impulseResponseGenerator(1.0, 3.0, 1);
	uint64_t numSamples = (3.0 * SAMPLE_RATE);
	long writtenFrames = sf_writef_double(outFile, iResponse, numSamples);
	sf_write_sync(outFile);
	sf_close(outFile);
	return 0;
}
