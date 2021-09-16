/**********************************************
 * File name: disigs.h
 * @author Josh Jeppson
 *
 * Description: This C-library header file contains templates for several functions 
 * related to n-dimensional signal processing.
 * 
 * This file is part of an assignment for ECE3640 at USU. It may not be redistributed,
 * modified or shared outside of that which is necessary.
 **********************************************/
#ifndef DISIGS_H
#define DISIGS_H

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

/* Location of hilbert transform and delay filter files */
#define HILBERTFILE "hilbert_filter.bin"
#define DELAYFILE "delay_filter.bin"

#define GAUSSIAN "gaussian_2_filter.bin"

// #define DEBUG
// #define VERBOSEDEBUG

/**
 * General I/O
 * */
float * readSignal(char * filename, int * ndim, int * nchan, int * dim0, int * dim1, int * dim2);
void writeSignal(char * filename, float * signal, int ndim, int nchan, int dim0, int dim1, int dim2);
void getSignalMetadata(char * filename, int * ndim, int * nchan, int * dim0, int * dim1, int * dim2);
/**
 * Audio-related signals
 * */
float * monoToStereo(float * channel1, uint16_t size1, float * channel2, uint16_t size2);
float * stereoToMono(float * stereoSignal, uint16_t length);
float * monauralConvolution(float * x, float * h, uint32_t N, uint32_t L);
void realtimeFilter(char * xFile, char * hFile, char * outFile, bool * done);
void monauralHilbert(float * input, int inputLength, bool plus, float ** realOutput, float ** imagOutput, int * l);
float * instFrequency(float * input, int inputLength, int * outputLength);
float * smoothInstFrequency(float * input, int inputLength, int * outputLength);
/**
 * Image related signals
 * */
float * rgbToGrayscale(float * image, uint16_t xSize, uint16_t ySize);
float * imageConvolution(float * x, float * h, int M, int N, int hM, int hN);
void sobel(char * input, char * output);

/* Point spread functions */
static float hx[3][3] = {
	{-1.0, 0.0, 1.0},
	{-2.0, 0.0, 2.0},
	{-1.0, 0.0, 1.0}
};

static float hy[3][3] = {
	{-1.0, -2.0, -1.0},
	{ 0.0,  0.0,  0.0},
	{ 1.0,  2.0,  1.0}
};

/**
 * Video related signals
 * */
float * rgbToGrayscaleVideo(float * video, uint16_t xSize, uint16_t ySize, uint16_t numFrames);


/**
 * Supplemental
 * */
bool isAllZeros(float * signal, int L);

#endif // DISIGS_H
