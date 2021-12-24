
/**
 * Header file for GeneralFilter class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in GeneralFilter.cpp for the filtersynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef GENERALFILTER_H_INCLUDED
#define GENERALFILTER_H_INCLUDED

#include "Filter.h"

namespace nodesynth {
	/*
	 * The General Filter is only low and highpass. Starts at 4 s as not to clash
	 * with the FilterTypes enum in Filter.h
	 * */
	enum GeneralFilterTypes {
		LOWPASS_12 = 4			// 12 dB cutoff lowpass filter
		, LOWPASS_24 = 5		// 24 dB cutoff lowpass filter
		, LOWPASS_48 = 6		// 48 dB cutoff lowpass filter
		, HIGHPASS_12 = 7		// 12 dB cutoff highpass filter
		, HIGHPASS_24 = 8		// 24 dB cutoff highpass filter
		, HIGHPASS_48 = 9		// 48 dB cutoff highpass filter
	};
	enum GeneralFilterDecays {
		TWELVE_DB = 0
		, TWENTYFOUR_DB = 1
		, FOURTYEIGHT_DB = 2
	};
	typedef unsigned char decay_speed_t;
	class GeneralFilter : Filter {
	public:
		GeneralFilter();
		virtual void createFilter();
		void setNumPoles(uint8_t numPoles);
		uint8_t getNumPoles();
	protected:
		void createLowpass(decay_speed_t decaySpeed);
		void createHighpass(decay_speed_t decaySpeed);
	private:
		float resonance;
	};
} // namespace nodesynth
#endif // GENERALFILTER_H_INCLUDED
