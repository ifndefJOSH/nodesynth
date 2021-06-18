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
	Tuner(double a4) {
		for (int i = 0; i < 128; i++) {
			frequencies[i] = a4 * pow(2.0, ((double) i - 69) / 12.0);
		}
	}
	~Tuner();
	double getFrequency(uint8_t midi) { return this->frequencies[i]; }
private:
	double[128] frequencies;
	
};

#endif /* TUNER_HPP_ */
