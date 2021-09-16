#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include <fftw3.h>
#include <sndfile.h>

#include "disigns.h" // For time-domain convolution

#define SAMPLE_RATE 44100 // Samples / second

// double * fullConvolution(
	
static double * read_file(const char * file, int * num_frames) {
	SF_INFO info;
	info.format = SF_FORMAT_WAV;
	SNDFILE * f = sf_open(file, SFM_READ, &info);
	*num_frames = (int) info.frames;
	double * buf = malloc(sizeof(double) * *num_frames);
}

int main(int argc, char ** argv) {
	int sFrames, iFrames;
	double * signal = read_file(argv[1], &sFrames);
	double * iResponse = read_file(argv[2], &iFrames);
	return 0;
}
