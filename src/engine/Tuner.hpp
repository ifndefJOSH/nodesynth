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

class Tuner {
public:
	Tuner(double a4) {
		for (int i = 
	}
	~Tuner();
	double getFrequency(uint8_t midi) { return this->frequencies[i]; }
private:
	double[128] frequencies;
	
};

#endif /* TUNER_HPP_ */
