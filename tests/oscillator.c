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

// #define FREQUENCYDOMAINMAX


/**
 * Attempt 1
 * */

uint32_t buildSawtooth(double * buffer, uint32_t bufsize, uint32_t sampleRate, double f) {
	clock_t start, end;
	start = clock();
	double nyquistFrequency = sampleRate / 2;
	double * y = calloc(bufsize, sizeof(double));
	double T = bufsize / sampleRate;
	double t;
	int i = 1;
	y[0] = -1;
	double incrementRate = 2 * f / sampleRate; 
	for (; i < bufsize; i++) {
		t = ((double) i) / ((double) sampleRate); 
		y[i] = y[i - 1] + incrementRate;
		if (y[i] > 1) {
			y[i] = -1;
		}
	}
	fftw_plan p = fftw_plan_r2r_1d(bufsize, y, buffer, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	/* Do some filtering */
	for (i = 0; i < bufsize; i++) {
// 		if (i < bufsize / 2)
			buffer[i] /= (double) bufsize;
			buffer[i] *= 0.5;
// 		else
// 			buffer[i] = 0.0;
	}
	free(y);
	end = clock();
	double timeUsed = (double) end - start;
	timeUsed /= CLOCKS_PER_SEC;
	uint32_t returnVal = 0;
	uint16_t samplesPerPeriod = sampleRate / f + 1;
	while (returnVal < bufsize) {
		returnVal += samplesPerPeriod;
	}
	if (returnVal > bufsize) {
		printf("You need to debug this part more josh");
		returnVal -= samplesPerPeriod;
	}
	printf("[INFO]: buildSawtooth() elapsed with a time of %f s\n", timeUsed);
	return returnVal;
}

uint32_t buildSquare(double * buffer, uint32_t bufsize, uint32_t sampleRate, double f) {
	clock_t start, end;
	start = clock();
	uint32_t samplesPerPeriod = sampleRate / f;
	double * y = calloc(bufsize, sizeof(double));
	double T = bufsize / sampleRate;
	double t;
	int i = 0;
// 	y[0] = -1;
	double incrementRate = 2 * f / sampleRate; 
	for (; i < bufsize; i++) {
// 		t = ((double) i) / ((double) sampleRate); 
		if (i % samplesPerPeriod > samplesPerPeriod / 2) {
			y[i] = 0.5;
		}
		else {
			y[i] = -0.5;
		}
	}
	fftw_plan p = fftw_plan_r2r_1d(bufsize, y, buffer, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	/* Do some filtering */
	for (i = 0; i < bufsize; i++) {
// 		if (i < bufsize / 2)
			buffer[i] /= (double) bufsize;
// 			buffer[i] *= 0.5;
// 		else
// 			buffer[i] = 0.0;
	}
	free(y);
	end = clock();
	double timeUsed = (double) end - start;
	timeUsed /= CLOCKS_PER_SEC;
	uint32_t returnVal = 0;
// 	uint16_t samplesPerPeriod = sampleRate / f + 1;
	while (returnVal < bufsize) {
		returnVal += samplesPerPeriod;
	}
	if (returnVal > bufsize) {
		printf("You need to debug this part more josh");
		returnVal -= samplesPerPeriod;
	}
	printf("[INFO]: buildSawtooth() elapsed with a time of %f s\n", timeUsed);
	return returnVal;
}


int test1(char ** argv) {
	clock_t start, end;
	start = clock();
	uint32_t bufsize = 2048; // ?? I guess
	double * buffer = malloc(sizeof(double) * bufsize);
	double * tBuffer = malloc(sizeof(double) * bufsize);
	double * audioBuffer = malloc(sizeof(double) * 4 * 44100); // The audio file
	
	double * nextFreeSample = audioBuffer;
	int i, fi;
	/* An Am arpeggio */
	double frequencies[] = { 
		440.00,
		329.63,
		261.63,
		220.00
	};
	double f;
	float bufPerSecond = 44100 / bufsize;
	int64_t remainingSamples = 44100 * 4;
	uint16_t fullBufPerSecond = (uint16_t) bufPerSecond;
	uint64_t samplesToCopy;
	uint32_t samplesToCopyPerCycle;
	fftw_plan p;
	/* Write one second of each frequency */
	for (fi = 0; fi < 4; fi++) {
		f = frequencies[fi];
// 		samplesToCopyPerCycle = buildSawtooth(buffer, bufsize, 44100, f);
		samplesToCopyPerCycle = buildSquare(buffer, bufsize, 44100, f);
		/* Get ifft of buffer and write to buffer */
		p = fftw_plan_r2r_1d(bufsize, buffer, tBuffer, FFTW_BACKWARD, FFTW_ESTIMATE);
		fftw_execute(p);
		fftw_destroy_plan(p);
		/* Write 1s of buffer out */
		for (i = 0; i < fullBufPerSecond; i++) {
			memcpy(nextFreeSample, tBuffer, (size_t) samplesToCopyPerCycle * sizeof(double));
			remainingSamples -= samplesToCopyPerCycle;
			nextFreeSample += samplesToCopyPerCycle;
		}
		if (remainingSamples < 0) {
			fprintf(stderr, "[ERROR]: remaining samples less than 0\n");
			return -1;
		}
		else if (remainingSamples > 0) {
			samplesToCopy = (((double) fullBufPerSecond) - bufPerSecond) * 44100;
			if (samplesToCopy > remainingSamples) {
				fprintf(stderr, "[INFO]: samples to copy is being truncated to remainingSamples: STC: %d\nRemaining: %d\n", samplesToCopy, remainingSamples);
				samplesToCopy = remainingSamples;
			}
			memcpy(nextFreeSample, tBuffer, (size_t) samplesToCopy * sizeof(double));
			remainingSamples -= samplesToCopy;
			nextFreeSample += samplesToCopy;
		}
	}
	
	printf("[INFO] Finished building buffer\n");
	SF_INFO info;
	info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	info.channels = 1;
	info.samplerate = 44100;
	
	SNDFILE * outFile = sf_open(argv[1], SFM_WRITE, &info);
	if (outFile == NULL) {
		fprintf(stderr, "[INFO] Could not open file '%s': '%s'\n", argv[1], sf_strerror(outFile));
		return -1;
	}
	
	long writtenFrames = sf_writef_double(outFile, audioBuffer, 4 * 44100);
	if (writtenFrames != 4 * 44100) {
		fprintf(stderr, "[ERROR]: Audio output failed\n");
	}
	else {
		fprintf(stdout, "[INFO]: Finished writing audio file.\n");
	}
	sf_write_sync(outFile);
	sf_close(outFile);
	
	end = clock();
	double timeUsed = (double) end - start;
	timeUsed /= CLOCKS_PER_SEC;
	printf("[INFO]: entire program elapsed with a time of %f s\n", timeUsed);
	return 0;
}


int main(int argc, char ** argv) {
	return test1(argv);
}
