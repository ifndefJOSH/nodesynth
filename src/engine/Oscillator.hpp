/**********************************************************************************
 * File name: Oscillator.hpp
 * 
 * @author Josh Jeppson
 * 
 * Description: Provides a class definition for `Oscillator`
 * 
 * This file is licensed under the TODO license. It may be copied and modified, as 
 * well as redistributed, so long as a copy of that license is provided along with
 * this software. This is part of the NODESYTH project, which is also under that license.
 **********************************************************************************/
#ifndef OSCILLATOR_HPP_
#define OSCILLATOR_HPP_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include <fftw3.h>

#include "Tuner.hpp"

#define MAX_AMPLITUDE 0.9
#define FREQ_OFF 0.0

enum osctypes {
	SINE = 0,
	SQUARE = 1,
	TRIANGLE = 2,
	SAWTOOTH = 3,
	PULSE = 4,
	ABSINE = 5
};
class Oscillator {
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
	
	void addMidiNote(uint8_t midiNumber);
	void endMidiNote(uint8_t midiNumber);
	void changeNumChannels(uint8_t numChannels);
	uint8_t getNumChannels() { return this->numChannels; }
	double * output;
protected:
	void buildSine(double freq, uint16_t samplingRate, uint8_t channel);
	void buildSquare(double freq, uint16_t samplingRate, uint8_t channel);
	void buildTriangle(double freq, uint16_t samplingRate, uint8_t channel);
	void buildSawtooth(double freq, uint16_t samplingRate, uint8_t channel);
	void buildPulse(double freq, uint16_t samplingRate, uint8_t channel);
	void buildAbsine(double freq, uint16_t samplingRate, uint8_t channel);
	void fillOutputBuffer();
	uint8_t getNextFreeBuffer();
private:
	uint8_t numChannels;
	uint8_t osctype;
	uint64_t bufSize;
	double ** buffers;
	uint8_t * lru;
	double * channelFrequencies;
	bool portmento;
	Tuner * tuner;
};


#endif /* OSCILLATOR_HPP_ */
