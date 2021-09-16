/**********************************************************************************
 * File name: Oscillator.hpp
 * 
 * @author Josh Jeppson
 * 
 * Description: Provides a class definition for `Oscillator`
 * 
 * This file is licensed under the TODO license. It may be copied and modified, as 
 * well as redistributed, so long as a copy of that license is provided along with
 * this software. This is part of the NODESYNTH project, which is also under that license.
 **********************************************************************************/
#ifndef OSCILLATOR_HPP_
#define OSCILLATOR_HPP_

#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string>

#include <fftw3.h>

#include "Tuner.hpp"
#include "Node.hpp"

#define MAX_AMPLITUDE 0.9
#define FREQ_OFF 0.0
#define NOT_IN_CHANNELS 127

enum osctypes {
	SINE = 0,
	SQUARE = 1,
	TRIANGLE = 2,
	SAWTOOTH = 3,
	PULSE = 4,
	ABSINE = 5
};
class Oscillator : Node {
public:
	Oscillator(uint64_t bufSize, uint8_t numChannels, Tuner * tuner);
	~Oscillator();
	
	void rebuildBuffer(double freq, uint16_t samplingRate, uint8_t channel);
	void setOsctype(uint8_t osctype) {
		this->osctype = osctype;
	}
	uint8_t getOsctype() {
		return this->osctype;
	}
	void setUpIO();
	void addMidiNote(uint8_t midiNumber);
	void endMidiNote(uint8_t midiNumber);
	uint8_t searchNote(uint8_t midiNumber);
	void changeNumChannels(uint8_t numChannels);
	uint8_t getNumChannels() { return this->numChannels; }
	// double * output;
protected:
	void buildSine(double freq, uint16_t samplingRate, uint8_t channel);
	void buildSquare(double freq, uint16_t samplingRate, uint8_t channel);
	void buildTriangle(double freq, uint16_t samplingRate, uint8_t channel);
	void buildSawtooth(double freq, uint16_t samplingRate, uint8_t channel);
	void buildPulse(double freq, uint16_t samplingRate, uint8_t channel);
	void buildAbsine(double freq, uint16_t samplingRate, uint8_t channel);
	uint8_t getNextFreeBuffer();
	// void fillOutputBuffer();
private:
	uint8_t numChannels;
	uint8_t osctype;
	uint64_t bufSize;
	double ** buffers;
	uint8_t * lru;
	bool * channelOn;
	uint8_t * channelNotes; // Needed for end of MIDI note signal
	bool portmento;
	Tuner * tuner;
};


#endif /* OSCILLATOR_HPP_ */
