
/**
 * Header file for PoleFilter class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in PoleFilter.cpp for the filtersynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef ONEPOLEFILTER_H_INCLUDED
#define ONEPOLEFILTER_H_INCLUDED

#include "Filter.h"

namespace nodesynth {
	 class PoleFilter {
	public:
		PoleFilter();
		virtual void createFilter();
		void setNumPoles(uint8_t numPoles);
		uint8_t getNumPoles();
	protected:
		void createLowpass();
		void createHighpass();
		void createBandpass();
		void createBandreject();
		uint8_t numberPoles;
	private:
	};
} // namespace nodesynth
#endif // ONEPOLEFILTER_H_INCLUDED
