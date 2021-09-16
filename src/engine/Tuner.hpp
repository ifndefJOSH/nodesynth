/**********************************************************************************
 * File name: Tuner.hpp
 * 
 * @author Josh Jeppson
 * 
 * Description: Provides a class definition for `Tuner`, global tuning settings all oscillators use
 * 
 * This file is licensed under the TODO license. It may be copied and modified, as 
 * well as redistributed, so long as a copy of that license is provided along with
 * this software. This is part of the NODESYTH project, which is also under that license.
 **********************************************************************************/
#ifndef TUNER_HPP_
#define TUNER_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class Tuner {
public:
	/**
	 * Constructor - creates tuning for this tuner based on A4 frequency
	 * 
	 * @param a4 Frequency of A4
	 * */
	Tuner(double a4) {
		updateTuning(a4);
	}
	~Tuner();
	/**
	 * Gets the frequency associated with a certain MIDI note
	 * 
	 * @param midi Midi note number
	 * @return Frequency of MIDI note at this tuner's tuning
	 * */
	double getFrequency(uint8_t midi) { return this->frequencies[midi]; }
	/**
	 * Updates the tuning with a new A4 frequency
	 * 
	 * @param a4 Frequency of A4
	 * */
	void updateTuning(double a4) {
		for (int i = 0; i < 128; i++) {
			frequencies[i] = a4 * pow(2.0, ((double) i - 69) / 12.0);
		}
	}
private:
	double frequencies[128];
	
};

#endif /* TUNER_HPP_ */
