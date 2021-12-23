
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
	class GeneralFilter {
	public:
		GeneralFilter();
		virtual void createFilter();
		void setNumPoles(uint8_t numPoles);
		uint8_t getNumPoles();
	protected:
		void createLowpass();
		void createHighpass();
		void createBandpass();
		void createBandreject();
	private:
		float resonance;
	};
} // namespace nodesynth
#endif // GENERALFILTER_H_INCLUDED
