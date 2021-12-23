
/**
 * Header file for Filter class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in Filter.cpp for the filtersynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/

#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "../core/Options.h"
#include "../datastream/AudioDataStream.h"


namespace nodesynth {
	// Filter types, used for filters that aren't flangers or formant
	enum FilterTypes {
		LOWPASS = 0
		, HIGHPASS = 1
		, BANDPASS = 2
		, BANDREJECT = 3
	};
	typedef unsigned char filter_type_t
	class Filter {
	public:
		Filter();
		~Filter();
		virtual void createFilter() = 0;
		void applyFilter(AudioDataStream & source, AudioDataStream & dest);
		filter_type_t getFilterType();
		void setFilterType(filter_type_t type);
		uint64_t frequencyToSampleLocation(double frequency);
	protected:
		filter_type_t filterType;
		double * filter;
		double cutoff1, cutoff2;
	private:
	};
} // namespace nodesynth

#endif // FILTER_H_INCLUDED
