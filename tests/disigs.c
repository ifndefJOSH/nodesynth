/*************************************
 * File name: disigs.c
 * @author Josh Jeppson
 *
 * Description: implementations of functions described in the file digisigs.h
 * 
 * This file is part of an assignment for ECE3640 at USU. It may not be redistributed,
 * modified or shared outside of that which is necessary.
 *************************************/
#include "disigs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define false 0
#define true 1

#define BUFSIZE 100000000

/* Prototypes for functions ONLY USED IN THIS FILE */
float avg(float a, float b);


/**
 * Globals (bad programming)
 * */
uint32_t convResult;

/**
 * Function name: readSignal
 * 
 * Description: Reads in a signal in the binary format specified for ECE3640
 * at USU. This format can be viewed in the file provided by Dr. Gunther
 * 
 * @param filename (char*) the name of the file to be read into fopen()
 * @param ndim (int *) pointer to ndim variable, which specifies the number of dimensions
 * in the signal
 * @param nchan (int *) pointer to the nchan variable, which specifies the number of 
 * channels in the signal
 * @param dim0 (int *) pointer to dim0 variable, which specifies the size of 0th dim 
 * @param dim1 (int *) pointer to dim0 variable, which specifies the size of 1st dim 
 * @param dim2 (int *) pointer to dim0 variable, which specifies the size of 2nd dim 
 * @return dynamically-allocated array full of values
 * */
float * readSignal(char * filename, int * ndim, int * nchan, int * dim0, int * dim1, int * dim2) {
	/* Open file for reading */
	FILE * f = fopen(filename, "rb");
	fread(ndim, sizeof(uint32_t), 1, f);
	fread(nchan, sizeof(uint32_t), 1, f);
	fread(dim0, sizeof(uint32_t), 1, f);
	fread(dim1, sizeof(uint32_t), 1, f);
	fread(dim2, sizeof(uint32_t), 1, f);
	/* Signal memory is allocated in the heap using malloc() */
	float * signal;
	/* Determine size to allocate */
	uint64_t size;
	switch (*ndim) {
		/**
		 * Asterisks (*) immediately next to the variable name are
		 * for pointer dereferencing, whereas asterisks surrounded 
		 * by spaces are for multiplication
		 * */
		case 1:
			size = *dim0;
			break;
		case 2:
			size = *dim0 * *dim1;
			break;
		case 3:
			size = *dim0 * *dim1 * *dim2;
			break;
	}
	size = size * *nchan;
	/* Allocate memory */
	signal = malloc(sizeof(float) * size);
	/* Read into memory */
	fread(signal, sizeof(float), size, f);	
	/* Close file */
	fclose(f);
	
	return signal;
}

/**
 * Function name: writeSignal
 * 
 * Description: writes a signal into the binary format specified for ECE3640
 * at USU. This format can be viewed in the file provided by Dr. Gunther
 *
 * @param filename (char*) the name of the file to be read into fopen()
 * @param ndim (int)specifies the number of dimensions in the signal
 * @param nchan (int) specifies the number of channels in the signal
 * @param dim0 (int) which specifies the size of 0th dim 
 * @param dim1 (int) which specifies the size of 1st dim 
 * @param dim2 (int) which specifies the size of 2nd dim 
 * @return nothing
 * */
void writeSignal(char * filename, float * signal, int ndim, int nchan, int dim0, int dim1, int dim2) {
	FILE * f;
	f = fopen(filename, "wb");
	/* Copy metadata into array to make it easier for fwrite() */
	int metadata[5];
	metadata[0] = ndim;
	metadata[1] = nchan;
	metadata[2] = dim0;
	metadata[3] = dim1;
	metadata[4] = dim2;
	/* Write metadata to file */
	fwrite(metadata, sizeof(uint32_t), 5, f);
	/* Write signal to file */
	uint64_t size;
	switch (ndim) {
		case 1:
			size = dim0;
			break;
		case 2:
			size = dim0 * dim1;
			break;
		case 3:
			size = dim0 * dim1 * dim2;
			break;
		default:
			/* This function cannot handle 4+ dimensions (or obviously any negative
			 number of dimensions */
			fprintf(
				stderr,
				"Error: %d is an invalid number of dimensions for this function\n",
				ndim
			);
			break;
	}
	size = size * nchan;
	fwrite(signal, sizeof(float), size, f);
	fclose(f);
}
/**
 * Function name: getSignalMetadata
 * 
 * Description: reads JUST THE METADATA from a signal .bin file.
 * 
 * @param filename (char*) the name of the file to be read into fopen()
 * @param ndim (int *) pointer to ndim variable, which specifies the number of dimensions
 * in the signal
 * @param nchan (int *) pointer to the nchan variable, which specifies the number of 
 * channels in the signal
 * @param dim0 (int *) pointer to dim0 variable, which specifies the size of 0th dim 
 * @param dim1 (int *) pointer to dim0 variable, which specifies the size of 1st dim 
 * @param dim2 (int *) pointer to dim0 variable, which specifies the size of 2nd dim 
 * @return nothing
 * */
void getSignalMetadata(char * filename, int * ndim, int * nchan, int * dim0, int * dim1, int * dim2) {
	/* Open file for reading */
	FILE * f = fopen(filename, "rb");
	fread(ndim, sizeof(uint32_t), 1, f);
	fread(nchan, sizeof(uint32_t), 1, f);
	fread(dim0, sizeof(uint32_t), 1, f);
	fread(dim1, sizeof(uint32_t), 1, f);
	fread(dim2, sizeof(uint32_t), 1, f);
	fclose(f);
}

/**
 * Function name: monoToStereo
 * 
 * Description: converts two mono channels into a single stereo channel
 * 
 * @param channel1 (float*) Buffer for channel 1
 * @param size1 (uint16_t) Size of (number of samples in) channel 1
 * @param channel2 (float*) Buffer for channel 2
 * @param size2 (uint16_t) Size of (number of samples in) channel 2
 * @return (float*) dynamically allocated array of converted elements.
 * */
float * monoToStereo(float * channel1, uint16_t size1, float * channel2, uint16_t size2) {
	/* Size of output buffer */
	uint16_t outputSize = size1;
	if (size2 < size1) {
		outputSize = size2;
	}
	/* Allocate memory for array */
	float * stereoSignal = malloc(sizeof(float) * 2 * outputSize);
	int i, j, k;
	for (i = 0, j = 1, k = 0; 
		k < outputSize; 
		i += 2, j += 2, k++) {
		stereoSignal[i] = channel1[k];
		stereoSignal[j] = channel2[k];
	}
	/* Return the copied array */
	return stereoSignal;
}
/**
 * Function name: stereoToMono
 * 
 * Description: converts a stereo audio signal into a mono one.
 * 
 * @param stereoSignal (float*) contiguous array of a stereo signal
 * @param length (uint16_t) The number of samples in ONE CHANNEL of the stereo signal
 * @return (float *) contiguous array of converted audio
 * */
float * stereoToMono(float * stereoSignal, uint16_t length) {
	int i;
	uint16_t stereoIndex;
	float * monoSignal = malloc(sizeof(float) * length);
	for (i = 0; i < length; i++) {
		/* Get the index of the second channel in the stereo signal */
		stereoIndex = ((i + 1) << 1) - 1;
		float a, b; /* The values of channels a and b*/
		a = stereoSignal[stereoIndex - 1];
		b = stereoSignal[stereoIndex];
		monoSignal[i] = avg(a, b);
	}
	return monoSignal;
}
/**
 * Function name: monauralConvolution
 * 
 * Description: convolution of two monaural audio signals. Padding occurs within
 * this function
 * 
 * @param x (float *) the signal to be convolved
 * @param h (float *) the impulse response
 * @param N (uint32_t) the length of the input signal
 * @param L (uint32_t) the length of the impulse response
 * @return (float *) the resulting signal
 * */
float * monauralConvolution(float * x, float * h, uint32_t N, uint32_t L) {
	int k, m, ulim_k, llim_m, ulim_m;
	/* Create padded input buffer */
	int N1 = N;
	float * xpad = x;
#ifdef PADDING
	N1 = (N + 2 * (L - 1));
	xpad = calloc(sizeof(float), N1);
	/* Copy original data into padded buffer */
	if (!memcpy((xpad + L), x, sizeof(float) * N)) {
		fprintf(
			stderr, 
			"[ERROR]: Memcpy failed moving monaural signal to padded buffer. Exiting with status code 1\n"
		);
		exit(1);
	}
#endif /* PADDING */
	/* Find limits */
	ulim_k = N1 + L;
	float * y = malloc(sizeof(float) * (ulim_k + 1));
	float sum;
	for (k = 0; k < ulim_k; k++) {
		sum = 0.0;
		/* Set limits of m */
		ulim_m = k + 1;
		if (ulim_m > N1) {
			ulim_m = N1;
		}
		llim_m = k - L + 1;
		if (llim_m < 0) {
			llim_m = 0;
		}
		/* Actually perform convolution */
		for (m = llim_m; m < ulim_m; m++) {
			sum += xpad[m] * h[k - m];
		}
		*(y + k) = sum;
	}
	convResult = ulim_k + 1;
#ifdef PADDING
	free(xpad);
#endif /* PADDING */
	return y;
}
/**
 * Function name: realtimeFilter
 * 
 * Description: uses a circular shift buffer to convolve signals of two input monaural files
 * and writes them to an output file.
 * 
 * @param xFile (char *) name of input file
 * @param hFile (char *) name of impulse response file
 * @param outFile (char *) name of output file to write to
 * @param done (bool *) pointer to "done" bool. Changes to true when done
 * @return nothing
 * */
void realtimeFilter(char * xFile, char * hFile, char * outFile, bool * done) {
	if (done) {
		*done = false;
	}
	int ndim, nchan, dim0, dim1, dim2;
	int xndim, xnchan, xdim0, xdim1, xdim2;
	float * h = readSignal(hFile, &ndim, &nchan, &dim0, &dim1, &dim2);
	fprintf(
		stdout
		, "[INFO]: Finished read-in of impulse response.\n"
	);
	/* Make sure that the impulse we've read in is a valid monaural signal */
	if (ndim != 1) {
		fprintf(
			stderr
			, "[ERROR: IN IMPULSE RESPONSE]: Number of dimensions should be 1. Got %d\n"
			, ndim
		);
		exit(1);
	}
	else if (nchan != 1) {
		fprintf(
			stderr
			, "[ERROR: IN IMPULSE RESPONSE]: Number of channels should be 1. Got %d\n"
			, nchan
		);
		exit(1);
	}
	/* If the tests above pass, we have a valid impulse response */
	FILE * f = fopen(xFile, "rb");
	/* Create an empty buffer for the output file */
	float * yBuf = malloc(sizeof(float) * BUFSIZE);
	/* Read metadata for file */
	fread(&xndim, sizeof(uint32_t), 1, f);
	fread(&xnchan, sizeof(uint32_t), 1, f);
	fread(&xdim0, sizeof(uint32_t), 1, f);
	fread(&xdim1, sizeof(uint32_t), 1, f);
	fread(&xdim2, sizeof(uint32_t), 1, f);
	/* Make sure that the signal we've read in is a valid monaural signal */
	if (xndim != 1) {
		fprintf(
			stderr
			, "[ERROR: IN INPUT SIGNAL]: Number of dimensions should be 1. Got %d\n"
			, xndim
		);
		exit(1);
	}
	else if (xnchan != 1) {
		fprintf(
			stderr
			, "[ERROR: IN INPUT SIGNAL]: Number of channels should be 1. Got %d\n"
			, xnchan
		);
		exit(1);
	}
	/* Buffer and init */
	float x[dim0];
	float y;
	/* Initialize our x buffer to 0 */
	uint32_t i = 0;
	uint32_t k;
	for (; i < dim0; i++) {
		*(x + i) = 0.0;
	}
	/* i should be equal to dim0 - 1 */
	/* Read sample and convolve in circular buffer */
	fread(x + i, sizeof(float), 1, f);
	uint32_t nSamples = 1;
	while (!feof(f)) {
		/* Perform convolution on this sample */
		for (y = 0.0, k = 0; k < dim0; k++) {
			y += h[k] * x[(k + i) % dim0];
		}
		if (nSamples >= BUFSIZE) {
			fprintf(
				stderr
				, "[WARNING] Buffer size was too small. Extra samples are omitted.\n"
			);
		}
		else {
			*(yBuf + nSamples - 1) = y;
		}
		/* Read in next sample */
		i += dim0 - 1; i %= dim0;
		fread(x + i, sizeof(float), 1, f);
		nSamples++;
	}
	fprintf(
		stdout
		, "[INFO]: Finished monaural convolution.\n"
	);
	/* Write to output file */
	writeSignal(outFile, yBuf, 1, 1, nSamples - 1, 44100, 0);
	fprintf(
		stdout
		, "[INFO]: Finished write out.\n"
	);
	/* Clean up resources used */
	if (h) {
		fprintf(stdout, "Freeing \"h\"\n");
		free(h);
	}
	if (yBuf) {
		fprintf(stdout, "Freeing \"yBuf\"\n");
		free(yBuf);
	}
	if (f) {
		fprintf(stdout, "Closing input file.\n");
		fclose(f);
	}
	/* done is a flag that can be checked by concurrent threads.
	 This is within an "if" statement to check if it hits a null 
	 pointer . */
	if (done != NULL) {
		fprintf(stdout, "Setting done flag.\n");
// 		*done = true;
	}
}
/**
 * Function name: monauralHilbert
 * 
 * Description: performs the Hilbert transform on an input signal
 * 
 * @param input (float *) the input signal
 * @param plus (bool) whether or not we're doing the plus hilbert transform
 * @param realOutput (float **) pointer to return signal's real element
 * @param imagOutput (float **) pointer to return signal's imaginary element
 * 
 * */
void monauralHilbert(float * input, int inputLength, bool plus, float ** realOutput, float ** imagOutput, int * l) {
	/* Get filter data */
	int ndim, ndim_2, nchan, nchan_2, dim0, dim1, dim2, dim0_2, dim1_2, dim2_2;
	float * d = readSignal(DELAYFILE, &ndim, &nchan, &dim0, &dim1, &dim2);
	float * h = readSignal(HILBERTFILE, &ndim_2, &nchan_2, &dim0_2, &dim1_2, &dim2_2);
	if (dim0 != dim0_2) {
		fprintf(
			stderr
			, "[ERROR] Dimension mismatch, got %d and %d\n"
			, dim0
			, dim0_2
		);
		return;
	}
	fprintf(
		stdout
		, "[INFO]: Succesfully read in DELAYFILE and HILBERTFILE. Starting convolution with lengths %d and %d.\n"
		, dim0
		, inputLength
	);
	*(realOutput) = monauralConvolution(d, input, dim0, inputLength);
	fprintf(
		stdout
		, "[INFO]: Succesfully found real part of Hilbert output. Starting convolutions with lengths %d and %d.\n"
		, dim0_2
		, inputLength
	);
	*(imagOutput) = monauralConvolution(h, input, dim0_2, inputLength);
	fprintf(
		stdout
		, "[INFO]: Succesfully found imaginary part of Hilbert output\n"
	);
	/* TODO: Find l 
	   UPDATE: Done. This way probably sucks, but okay. */
	*l = convResult; /* Global var in this file */
	if (!plus) {
		int i;
		for (i = 0; i < *l; i++) {
			**(imagOutput + i) =  - **(imagOutput + i);
		}
	}
	free(d);
	free(h);
	fprintf(
		stdout
		, "[INFO]: Finished Hilbert transformation\n"
	);
}
/**
 * Function name instFrequency
 * 
 * Description: Finds the instantaneous frequency of a signal
 * @param input (float *): The signal to be processed
 * @param inputLength (int): length of the input signal
 * @param outputLength (int): length of the output signal
 * @return (float *): processed signal
 * */
float * instFrequency(float * input, int inputLength, int * outputLength) {
	float * realHilbert, * imagHilbert;
	int l;
	monauralHilbert(input, inputLength, 1, &realHilbert, &imagHilbert, &l);
#ifdef DEBUG
	if (isAllZeros(realHilbert, l)) {
		fprintf(
			stderr
			, "[ERROR]: Real part of hilbert is all zeros\n"
		);
	}
	if (isAllZeros(imagHilbert, l)) {
		fprintf(
			stderr
			, "[ERROR]: Imaginary part of hilbert is all zeros\n"
		);
	}
#endif /* DEBUG */
	int i = 0;
	float pz, pzold, yi, yr;
	float * f = malloc(sizeof(float) * l);
	pzold = 0;
	for (; i < l; i++) {
		yi = *(imagHilbert + i);
		yr = *(realHilbert + i);
		pz = atan2(yi, yr);
		*(f + i) = -(pz - pzold);
		if (*(f + i) > M_PI) {
			*(f + i) -= 2.0 * M_PI;
		}
		else if (*(f + i) < -M_PI) {
			*(f + i) += 2.0 * M_PI;
		}
#ifdef DEBUG 
#ifdef VERBOSEDEBUG
		fprintf(
			stdout
			, "fi is %f at i = %d\nAdditionally, yi = %f, yr = %f\n"
			, *(f + i)
			, i
			, yi
			, yr
		);
#endif // VERBOSEDEBUG
#endif // DEBUG
		pzold = pz;
	}
	*outputLength = l;
	/* Prevent memory leak */
	free(realHilbert);
	free(imagHilbert);
	fprintf(
		stdout
		, "[INFO]: Finished noisy instantaneous frequency\n"
	);
	return f;
}
/**
 * Function name: smoothInstFrequency
 * 
 * Description: instantaneous frequency with gaussian smoothing
 * @param input (float *): The signal to be processed
 * @param inputLength (int): length of the input signal
 * @param outputLength (int): length of the output signal
 * @return (float *): processed signal
 * */
float * smoothInstFrequency(float * input, int inputLength, int * outputLength) {
	float * noisyInstFrequency = instFrequency(input, inputLength, outputLength);
#ifdef DEBUG
	if (isAllZeros(noisyInstFrequency, outputLength)) {
		fprintf(
			stderr
			, "[ERROR]: Signal became all zeros in noisyInstFrequency\n"
		);
	}
#endif /* DEBUG */
	/* Smooth with gaussian curve */
	int ndim, nchan, dim0, dim1, dim2;
	float * gaussianCurve = readSignal(GAUSSIAN, &ndim, &nchan, &dim0, &dim1, &dim2);
	fprintf(
		stdout
		, "[INFO]: smoothing by convolving with gaussian function: lengths %d and %d\n"
		, *outputLength
		, dim0
	);
	float * smoothInstFreq = monauralConvolution(noisyInstFrequency, gaussianCurve, *outputLength, dim0);
	*outputLength = convResult;
	free(noisyInstFrequency);
	free(gaussianCurve);
	fprintf(
		stdout
		, "[INFO]: Finished smoothing instantaneous frequency\n"
	);
	return smoothInstFreq;
}
/**
 * Function name: avg
 * 
 * Description: average of two floats
 * 
 * @param a (float) the first number
 * @param b (float) the second number
 * @return (float) the average
 * */
float avg(float a, float b) {
	return (a + b) / 2.0;
}
/**
 * Function name: rgbToGrayscale
 * 
 * Description: converts a 3-channel RGB signal to a single grayscale image using the
 * following formula:
 * 
 * gray = (0.2989) * r + (0.5870) * g + (0.1140) * b
 * 
 * @param image (float*) 2D, 3-channel image in memory
 * @param xSize (uint16_t) The width of the input image
 * @param ySize (uint16_t) The height of the input image
 * */
float * rgbToGrayscale(float * image, uint16_t xSize, uint16_t ySize) {
	/* Check to see if image is too small */
	uint64_t expectedSize = 3 * xSize * ySize;
	float * grayscaleImage;
	grayscaleImage = malloc(sizeof(float) * xSize * ySize);
	/* Copy RGB values into grayscaleImage */
	uint32_t i, j;
	float r, g, b;
	for (i = 0, j = 0; i < xSize * ySize; i++, j += 3) {
		r = image[j];
		g = image[j + 1];
		b = image[j + 2];
		grayscaleImage[i] = (0.2989) * r + (0.5870) * g + (0.1140) * b;
	}
	
	return grayscaleImage;
}
/**
 * Function name: imageConvolution
 * 
 * Description: Performs convolution on a 2D image. Padding occurs within
 * this function
 * 
 * @param image1 (float *) the image signal to be convolved
 * @param image2 (float *) the impulse response image
 * @param M (int) x-dimension of input signal
 * @param N (int) y-dimension of input signal
 * @param hM (int) x-dimension of the impulse response
 * @param hN (int) y-dimension of the impulse response
 * @return convolved image
 * */
float * imageConvolution(float * x, float * h, int M, int N, int hM, int hN) {
// 	printf("M=%d\nN=%d\n", M, N);
	/* Pad x with a border */
	int MPad, NPad, yM, yN;
	MPad = M + 2 * (hM - 1);
	NPad = N + 2 * (hN - 1);
	yM = M + (hM - 1);
	yN = N + (hN - 1);
	float * y = malloc(sizeof(float) * yM * yN);
	float * xPadded = calloc(sizeof(float), MPad * NPad);
	float tmp;
	/* Copy x data into xPadded */
	int i, j, k, l;
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			/* Offset incorporated using hN and hM */
			*(xPadded + NPad * (i + (hN - 1)) + j + (hM - 1)) =
							*(x + (i * N) + j);
		}
	}
	/* Perform convolution */
	for (k = 0; k < yM; k++) {
		for (l = 0; l < yN; l++) {
			for (tmp = 0.0, i = 0; i < hM; i++) {
				for (j = 0; j < hN; j++) {
					tmp += *(h + (i * hN) + j) * *(xPadded + ((k + i) * NPad) + l + j);
				}
			}
			*(y + (k * yN) + l) = tmp;
// 			printf("%f\n", tmp);
		}
	}
	
	/* Clean up resources */
	free(xPadded);
	return y;
}
/**
 * Function name: sobel
 * 
 * Description: uses the spread functions defined in disigs.h and 
 * 2D convolution to perform sobel edge detection on an image file
 * and write it to an output file.
 * 
 * @param input (char *) the name of the input file
 * @param output (char *) the name of the output file
 * */
void sobel(char * input, char * output) {
	/* Read input file */
	int ndim, nchan, dim0, dim1, dim2;
	float * x = readSignal(input, &ndim, &nchan, &dim0, &dim1, &dim2);
	/* Verify correct number of dimensions and channels for x */
	if (ndim != 2) {
		fprintf(
			stderr
			, "[ERROR]: Number of dimensions should be 2. Got %d\n"
			, ndim
		);
		exit(1);
	}
	else if (nchan == 3) {
		fprintf(
			stderr
			, "[WARNING] Expected single channel. Got RGB image. Converting to BW..."
		);
		/* Convert image to black and white prior to sobel filter */
		float * xtmp = rgbToGrayscale(x, dim0, dim1);
		fprintf(
			stderr
			, "finished.\n"
		);
		free(x);
		x = xtmp;
	}
	else if (nchan != 1) {
		fprintf(
			stderr
			, "[ERROR]: Number of channels should be 1 or 3. Got %d\n"
			, nchan
		);
		exit(1);
	}
	float * yx = imageConvolution(x, hx, dim0, dim1, 3, 3);
	float * yy = imageConvolution(x, hy, dim0, dim1, 3, 3);
	/* Allocate memory for output image */
	float * sobelImage = malloc(sizeof(float) * dim0 * dim1);
	/* Sobel combine the two processed images */
	int i, j;
	printf("dim0=%d\ndim1=%d\n", dim0, dim1);
	for (i = 0; i < dim0; i++) {
		for (j = 0; j < dim1; j++) {
			/* Get the pythagorean magnitude of the 
			 two signals */
			*(sobelImage + i * dim1 + j) = sqrt(
				  *(yx + i * dim1 + j) * *(yx + i * dim1 + j) +
				  *(yy + i * dim1 + j) * *(yy + i * dim1 + j)
			);
		}
	}
	/* Write the file back to output */
	writeSignal(output, sobelImage, ndim, 1, dim0 + 2, dim1 + 2, dim2);
	/* Clean up */
	free(yx);
	free(yy);
	free(sobelImage);
	free(x);
}
/**
 * Function name: rgbToGrayscaleVideo
 * 
 * Description: Converts a 3-channel RGB video signal into a single-channel BW video.
 * 
 * @param video (float *) video data, stored in contiguous memory
 * @param xSize (uint16_t) size of the horizontal dimension in the video
 * @param ySize (uint16_t) size of the vertical dimension in the video
 * @return grayscale video in contiguous memory
 * */
float * rgbToGrayscaleVideo(float * video, uint16_t xSize, uint16_t ySize, uint16_t numFrames) {
	float * grayscaleVideo = malloc(sizeof(float) * xSize * ySize * numFrames);
	uint32_t numPixelsPerFrame = xSize * ySize;
	uint16_t i;
	float * currentFrame = video;
	float * currentBWFrame;
	size_t frameSize = sizeof(float) * xSize * ySize;
	/* Convert individual frames and memcpy them back into the main buffer */
	for (i = 0; i < numFrames; i++) {
		currentBWFrame = rgbToGrayscale(currentFrame, xSize, ySize);
		/* If memcpy fails */
		if (!memcpy(grayscaleVideo + (i * numPixelsPerFrame), currentBWFrame, frameSize)) {
			fprintf(
				stderr 
				, "[ERROR]: Memcpy failed on frame %d. Exiting with status code 1\n"
				, i
			);
			exit(1);
		}
		/* Prevent memory leaks */
		free(currentBWFrame);
	}
	return grayscaleVideo;
}
/**
 * Function name: isAllZeros
 * 
 * Description: tells if signal is all zeros
 * 
 * @param signal (float*) signal to test
 * @param L (int) length of signal
 * @return yes or no
 * */
bool isAllZeros(float * signal, int L) {
	int i = 0;
	for (; i < L; i++) {
		if (*(signal + i) != 0.0) {
			return 0;
		}
	}
	return 1;
}
