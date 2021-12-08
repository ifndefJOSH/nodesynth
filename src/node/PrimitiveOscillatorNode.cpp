#include "PrimitiveOscillatorNode.h"

#include "../core/cli/messages.h"

using namespace nodesynth;

#define MAX_AMPLITUDE 1.0

// Overloads for fftw_complex operators
fftw_complex operator=(fftw_complex a, double b) {
	fftw_complex c = a;
	c[0] += b;
	return c;
}

fftw_complex operator+(fftw_complex a, fftw_complex b) {
	fftw_complex sol;
	sol[0] = a[0] + b[0];
	sol[1] = a[1] + b[1];
	return sol;
}

fftw_complex operator-(fftw_complex a, fftw_complex b) {
	fftw_complex sol;
	sol[0] = a[0] - b[0];
	sol[1] = a[1] - b[1];
	return sol;
}

PrimitiveOscillatorNode::PrimitiveOscillatorNode() {
	// temporaryBuffers = new double[
	// Default type for our waveforms
	waveformType = WAVEFORMS::SAWTOOTH;
	p = fftw_create_plan(Options::getBufferSize(), FFTW_FORWARD, FFTW_ESTIMATE);
}

PrimitiveOscillatorNode::~PrimitiveOscillatorNode() {

}

void
PrimitiveOscillatorNode::createSawToothWave(
	double frequency
	, double velocity
	, uint8_t channel
) {
	// Creates a sawtooth wave of a certain frequency in a certain channel
	fftw_complex * buffer = out.channeledAudio[channel];
	fftw_complex * y = new fftw_complex[Options::getBufferSize()];
	double incrementRate = 2 * frequency * Options::getSampleRate();
	y[0] = -1;
	// Build in the time domain
	for (int i = 1; i < Options::getBufferSize(); i++) {
		y[i] = y[i - 1] + incrementRate;
		if (y[i] > 1) {
			y[i] = -1;
		}
	}
	// Create fourier transform and perform using fftw
	fftw_one(p, y, buffer);
	// Scale the output so that we don't get a ton of clipping
	for (int i = 0; i < Options::getBufferSize(); i++) {
		buffer[i][0] /= (double) Options::getBufferSize();
		buffer[i][0] *= MAX_AMPLITUDE * velocity;
		buffer[i][1] /= (double) Options::getBufferSize();
		buffer[i][1] *= MAX_AMPLITUDE * velocity;

	}
	// Free resources
	delete[] y;
}

void
PrimitiveOscillatorNode::createSquareWave(
	double frequency
	, double velocity
	, uint8_t channel
) {
	fftw_complex * buffer = out.channeledAudio[channel];
	uint32_t samplesPerPeriod = Options::getSampleRate() / frequency;
	fftw_complex * y = new fftw_complex[Options::getBufferSize()];
	// Create our wave in the time domain
	for (int i = 0; i < Options::getBufferSize(); i++) {
		if (i % samplesPerPeriod > samplesPerPeriod / 2) {
			y[i] = MAX_AMPLITUDE * velocity;
		}
		else {
			y[i] = - MAX_AMPLITUDE * velocity;
		}
	}
	// Perform FFT using FFTW
	fftw_one(p, y, buffer);
	// Normalize the output so that it's not crazy overamplified.
	for (int i = 0; i < Options::getBufferSize(); i++) {
		buffer[i][0] /= (double) Options::getBufferSize();
		buffer[i][1] /= (double) Options::getBufferSize();

	}
	// Free resources
	delete[] y;

}
void
PrimitiveOscillatorNode::createSineWave(
	double frequency
	, double velocity
	, uint8_t channel
) {
	/*
		TODO: Currently gets at specific frequency in a box, but if we sampled, we'd get some
		skewing/blurring in the frequency domain. So, we SHOULD develop the wave in time domain
		and then convert into frequency domain using the fft
	*/
	// Get the output buffer we are trying to write to
	fftw_complex * buffer = out.channeledAudio[channel];
	double nyquistFrequency = Options::getSampleRate() / 2;
	for (int i = 0; i < Options::getBufferSize(); i++) {
		buffer[i][0] = 0;
		buffer[i][1] = 0;
	}
	int freqIndex = frequency * (Options::getBufferSize() / nyquistFrequency);
	buffer[freqIndex][0] = MAX_AMPLITUDE * velocity;
	buffer[freqIndex][1] = MAX_AMPLITUDE * velocity;
}
void
PrimitiveOscillatorNode::createTriangleWave(
	double frequency
	, double velocity
	, uint8_t channel
) {
	fftw_complex * buffer = out.channeledAudio[channel];
	uint32_t samplesPerPeriod = Options::getSampleRate() / frequency;
	// In the time domain, we only need to create a "double"
	fftw_complex * y = new fftw_complex[Options::getBufferSize()];
	// Create our wave in the time domain
	uint16_t quarterBuf = Options::getBufferSize() / 4;
	double incrementRate = MAX_AMPLITUDE * velocity / (Options::getBufferSize() / 2);
	// Start the quarter points
	y[0] = 0.0;
	y[quarterBuf] = MAX_AMPLITUDE * velocity;
	y[quarterBuf * 2] = - MAX_AMPLITUDE * velocity;
	y[quarterBuf * 3] = - MAX_AMPLITUDE * velocity;
	for (int i = 1; i < quarterBuf; i++) {
		y[i] = y[i - 1] + incrementRate;
		y[quarterBuf + i] = y[quarterBuf + i - 1] - incrementRate;
		y[2 * quarterBuf + i] = y[2 * quarterBuf + i - 1] - incrementRate;
		y[3 * quarterBuf + i] = y[3 * quarterBuf + i - 1] + incrementRate;
	}
	// Perform FFT using FFTW
	fftw_one(p, y, buffer);
	// Normalize the output so that it's not crazy overamplified.
	for (int i = 0; i < Options::getBufferSize(); i++) {
		buffer[i][0] /= (double) Options::getBufferSize();
		buffer[i][1] /= (double) Options::getBufferSize();
	}
	// Free resources
	delete[] y;
}

void
PrimitiveOscillatorNode::update() {
	// For each MIDI channel in notesIn
	for (uint8_t i = 0; i < Options::getMidiChannelCount(); i++) {
		// Read the MIDI note and update the appropriate channel
		switch (waveformType) {
			case WAVEFORMS::SAWTOOTH:
				createSawToothWave(
					frequencyFromMidiNote(notesIn->notes[i].note)
					, notesIn->notes[i].velocity
					, i
				);
				break;
			case WAVEFORMS::SQUARE:
				createSquareWave(
					frequencyFromMidiNote(notesIn->notes[i].note)
					, notesIn->notes[i].velocity
					, i
				);
				break;
			case WAVEFORMS::SINE:
				createSineWave(
					frequencyFromMidiNote(notesIn->notes[i].note)
					, notesIn->notes[i].velocity
					, i
				);
				break;
			case WAVEFORMS::TRIANGLE:
				createTriangleWave(
					frequencyFromMidiNote(notesIn->notes[i].note)
					, notesIn->notes[i].velocity
					, i
				);
				break;
			default:
			// TODO: handle error
			error("The waveform type given is undefined! Type: " + std::to_string(waveformType));
		}
	}
}
