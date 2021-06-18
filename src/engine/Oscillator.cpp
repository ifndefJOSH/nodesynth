/**********************************************************************************
 * File name: Oscillator.cpp
 * 
 * @author Josh Jeppson
 * 
 * Description: Implementation of `Oscillator` class.
 * 
 * This file is licensed under the TODO license. It may be copied and modified, as 
 * well as redistributed, so long as a copy of that license is provided along with
 * this software. This is part of the NODESYTH project, which is also under that license.
 **********************************************************************************/
#include "Oscillator.hpp"
/**
 * Constructor for the `Oscillator` class. Takes a default buffer size and the number of desired channels.
 * The default type of oscillator is `SINE`, so this method sets the osctype to `SINE`.
 * 
 * @param bufsize The size of the buffers to use.
 * @param numChannels The number of MIDI channels to use.
 * 
 * @return Instance of `Oscillator` class with 
 * */
Oscillator::Oscillator(uint64_t bufSize, uint8_t numChannels, Tuner * tuner) {
	// Portmeto is disabled by default
	this->portmento = false;
	// Set default oscillator type
	this->osctype = SINE;
	// Set number of channels
	this->numChannels = numChannels;
	// Create LRU array initialized at 0
	this->lru = new uint8_t[numChannels](0);
	// Create output buffers
	this->buffers = new (double *)[numChannels];
	for (int i = 0; i < numChannels; i++) {
		this->buffers[i] = new double[bufSize];
	}
	this->output = new double[bufSize];
	// Create channel frequencies array
	this->channelFrequencies = new double[numChannels];
	// Point this to the global tuner
	this->tuner = tuner;
}
/**
 * Destructor for the `Oscillator` class. Cleans up memory used.
 * */
Oscillator::~Oscillator() {
	for (int i = 0; i < numChannels; i++) {
		delete this->buffers[i];
	}
	delete this->buffers;
	delete this->lru;
	delete this->output;
	delete this->channelFrequencies;
}
/**
 * Adds a MIDI note to the next available channel.
 * */
void addMidiNote(uint8_t midiNumber) {
	uint8_t channel = getNextFreeBuffer();
	if (!this->portmento) {
		double f = this->tuner.getFrequency(midiNumber);
		channelFrequencies[channel] = f;
		this->rebuildBuffer(f, 44100, channel);
	}
	else {
		// TODO: portmento not implemented yet
	}
	
}
void endMidiNote(uint8_t midiNumber) {
	
}
void changeNumChannels(uint8_t numChannels) {
	
}

/**
 * Rebuilds the oscillator buffer at a certain frequency. Everything is done in the frequency domain.
 * 
 * This method takes the frequency in terms of a double precision floating point number and creates a frequency domain 
 * representation of it in our buffer. Every time a new MIDI note is added, this is triggered.
 * 
 * @param freq The frequency of the buffer to build
 * @param samplingRate The sampling rate of the audio. Default is 44100
 * */
void Oscillator::rebuildBuffer(double freq, uint16_t samplingRate, uint8_t channel) {
	if (freq > (double) samplingRate / 2) {
		std::err << "[WARNING]: frequency " << freq << " is greater than Nyquist frequency for sampling rate " << samplingRate << std::endl;
	}
	switch (this->osctype) {
		case SINE:
			buildSine(freq, samplingRate, channel);
			break;
		case SQUARE:
			buildSquare(freq, samplingRate, channel);
			break;
		case TRIANGLE:
			buildTriangle(freq, samplingRate, channel);
			break;
		case SAWTOOTH:
			buildSawtooth(freq, samplingRate, channel);
			break;
		case PULSE:
			buildPulse(freq, samplingRate, channel);
			break;
		case ABSINE:
			buildAbsine(freq, samplingRate, channel);
			break;
		default:
			std::err << "[ERROR]: oscillator type " << this->osctype << " is not defined. Please reference the osctype enum in the source code\n";
	}
	// Get samples per period
	uint16_t samplesPerPeriod = samplingRate / freq + 1;
	// Closest number of samples with full period to buffer size
	uint32_t clFull = 0;
	while (clFull < bufSize) {
		clFull += samplesPerPeriod;
	}
	// TODO: Store it in the class instance
	
	// Now that the buffers have changed, the output buffer must change as well
	fillOutputBuffer();
}
/**
 * Builds a sine wave in the frequency domain for the specific frequency and specific channel.
 * 
 * This method takes a frequency and a sampling rate (generally 44100), and recreates a sine wave
 * of that frequency in the buffer at a specific channel.
 * 
 * @param freq The frequency to build the oscillator at
 * @param samplingRate The global sampling rate
 * @param channel The channel to add the sine wave to
 * */
void Oscillator::buildSine(double freq, uint16_t samplingRate, uint8_t channel) {
	// Get the output buffer we are trying to write to
	double * buffer = this->buffers[channel];
	double nyquistFrequency = samplingRate / 2;
	for (int i = 0; i < bufSize; i++) {
		buffer[i] = 0;
	}
	int freqIndex = freq * (bufSize / nyquistFrequency);
	buffer[freqIndex] = MAX_AMPLITUDE;
}
/**
 * Builds a square wave in the frequency domain for the specific frequency and specific channel.
 * 
 * This method takes a frequency and a sampling rate (generally 44100), and recreates a square wave
 * of that frequency in the buffer at a specific channel.
 * 
 * @param freq The frequency to build the oscillator at
 * @param samplingRate The global sampling rate
 * @param channel The channel to add the square wave to
 * */
void Oscillator::buildSquare(double freq, uint16_t samplingRate, uint8_t channel) {
	double * buffer = this->buffers[channel];
	uint32_t samplesPerPeriod = samplingRate / f;
	double * y = new double[bufSize];
	// Create our wave in the time domain
	for (int i = 0; i < bufSize; i++) {
		if (i % samplesPerPeriod > samplesPerPeriod / 2) {
			y[i] = MAX_AMPLITUDE; 
		}
		else {
			y[i] = - MAX_AMPLITUDE;
		}
	}
	// Perform FFT using FFTW
	fftw_plan p = fftw_plan_r2r_id(bufSize, y, buffer, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	// Normalize the output so that it's not crazy overamplified.
	for (int i = 0; i < bufSize; i++) {
		buffer[i] /= (double) bufSize;
	}
	// Free resources
	delete y;
}
/**
 * Builds a triangle wave in the frequency domain for the specific frequency and specific channel.
 * 
 * This method takes a frequency and a sampling rate (generally 44100), and recreates a triangle wave
 * of that frequency in the buffer at a specific channel.
 * 
 * @param freq The frequency to build the oscillator at
 * @param samplingRate The global sampling rate
 * @param channel The channel to add the triangle wave to
 * */
void Oscillator::buildTriangle(double freq, uint16_t samplingRate, uint8_t channel) {
	double * buffer = this->buffers[channel];
	uint32_t samplesPerPeriod = samplingRate / f;
	double * y = new double[bufSize];
	// Create our wave in the time domain
	uint16_t quarterBuf = bufsize / 4;
	double incrementRate = MAX_AMPLITUDE / (bufSize / 2);
	// Start the quarter points
	y[0] = 0.0;
	y[quarterBuf] = MAX_AMPLITUDE;
	y[quarterBuf * 2] = - MAX_AMPLITUDE;
	y[quarterBuf * 3] = - MAX_AMPLITUDE;
	for (int i = 1; i < quarterBuf; i++) {
		y[i] = y[i - 1] + incrementRate;
		y[quarterBuf + i] = y[quarterBuf + i - 1] - incrementRate;
		y[2 * quarterBuf + i] = y[2 * quarterBuf + i - 1] - incrementRate;
		y[3 * quarterBuf + i] = y[3 * quarterBuf + i - 1] + incrementRate;
	}
	// Perform FFT using FFTW
	fftw_plan p = fftw_plan_r2r_id(bufSize, y, buffer, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	// Normalize the output so that it's not crazy overamplified.
	for (int i = 0; i < bufSize; i++) {
		buffer[i] /= (double) bufSize;
	}
	// Free resources
	delete y;
}
/**
 * Builds a sawtooth wave in the frequency domain for the specific frequency and specific channel.
 * 
 * This method takes a frequency and a sampling rate (generally 44100), and recreates a sawtooth wave
 * of that frequency in the buffer at a specific channel.
 * 
 * @param freq The frequency to build the oscillator at
 * @param samplingRate The global sampling rate
 * @param channel The channel to add the sawtooth wave to
 * */
void Oscillator::buildSawtooth(double freq, uint16_t samplingRate, uint8_t channel) {
	double * y = new double[bufSize];
	double incrementRate = 2 * freq * samplingRate;
	y[0] = -1;
	// Build in the time domain
	for (int i = 1; i < bufSize; i++) { 
		y[i] = y[i - 1] + incrementRate;
		if (y[i] > 1) {
			y[i] = -1;
		}
	}
	// Create fourier transform and perform using fftw
	fftw_plan p = fftw_plan_r2r_id(bufSize, y, buffer, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	// Scale the output so that we don't get a ton of clipping
	for (int i = 0; i < bufSize; i++) {
		buffer[i] /= (double) bufSize;
		buffer[i] *= MAX_AMPLITUDE;
	}
	// Free resources
	delete y;
}
/**
 * Builds a pulse wave in the frequency domain for the specific frequency and specific channel.
 * 
 * This method takes a frequency and a sampling rate (generally 44100), and recreates a pulse wave
 * of that frequency in the buffer at a specific channel.
 * 
 * @param freq The frequency to build the oscillator at
 * @param samplingRate The global sampling rate
 * @param channel The channel to add the pulse wave to
 * */
void Oscillator::buildPulse(double freq, uint16_t samplingRate, uint8_t channel) {
	double * y = new double[bufSize];
	y[0] = 0;
	// Build in the time domain
	for (int i = 1; i < bufSize; i++) { 
		// TODO: Create pulse signal
	}
	// Create fourier transform and perform using fftw
	fftw_plan p = fftw_plan_r2r_id(bufSize, y, buffer, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	// Scale the output so that we don't get a ton of clipping
	for (int i = 0; i < bufSize; i++) {
		buffer[i] /= (double) bufSize;
		buffer[i] *= MAX_AMPLITUDE;
	}
	// Free resources
	delete y;
}
/**
 * Builds an absolute value sine wave in the frequency domain for the specific frequency and specific channel.
 * 
 * This method takes a frequency and a sampling rate (generally 44100), and recreates an absolute value sine wave
 * of that frequency in the buffer at a specific channel.
 * 
 * @param freq The frequency to build the oscillator at
 * @param samplingRate The global sampling rate
 * @param channel The channel to add the absolute value sine wave to
 * */
void Oscillator::buildAbsine(double freq, uint16_t samplingRate, uint8_t channel) {
	double * y = new double[bufSize];
	double t;
	y[0] = 0;
	// Build in the time domain
	for (int i = 1; i < bufSize; i++) {
		t = ((double) i) / ((double) samplingRate);
		y[i] = abs(sin(2 * M_PI * freq * t));
	}
	// Create fourier transform and perform using fftw
	fftw_plan p = fftw_plan_r2r_id(bufSize, y, buffer, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	// Scale the output so that we don't get a ton of clipping
	for (int i = 0; i < bufSize; i++) {
		buffer[i] /= (double) bufSize;
		buffer[i] *= MAX_AMPLITUDE;
	}
	// Free resources
	delete y;
}
/**
 * Fills the output buffer. Should be triggered whenever a buffer is changed.
 * 
 * Takes each of the buffers and elementwise adds them and places those in the output buffer. 
 * This method is called every time a buffer update is triggered (by either a new MIDI note 
 * or a change in the portmento frequency). No parameters, no return value.
 * */
void Oscillator::fillOutputBuffer() {
	// For each sample in the buffer
	for (int i = 0; i < bufSize; i++) {
		output[i] = 0;
		// Loop through each channel and add its value to the output buffer
		for (int j = 0; j < numChannels; j++) {
			// Does not check for clipping
			output += buffers[j][i];
		}
	}
}
/**
 * Gets the next free (available) buffer to use. If no buffer is available, selects the LRU (least recently used)
 * 
 * Iterates through the list of buffers and finds the first available one. This method
 * changes the status of that buffer. That is not up to other methods to do, so
 * we could have what I call a "channel leak" (channels increasingly become unavailable as
 * next free buffer is polled without use). LRU prevents there never from being a channel
 * available however.
 * */
uint8_t Oscillator::getNextFreeBuffer() {
	int index = 0;
	for (int i = 0; i < numChannels; i++) {
		if (lru[i] > lru[index]) {
			index = i;
		}
		lru[i]++;
	}
	lru[index] = 0;
	return index;
}
