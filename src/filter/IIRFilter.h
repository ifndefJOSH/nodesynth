
/**
 * Header file for IIRFilter class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in IIRFilter.cpp for the filtersynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef IIRFILTER_H_INCLUDED
#define IIRFILTER_H_INCLUDED

#include "Filter.h"

namespace nodesynth {
	 class IIRFilter {
	public:
		IIRFilter();
		virtual void createFilter();
	protected:
		void createLowpass();
		void createHighpass();
		void createBandpass();
		void createBandreject();

	private:
	};
} // namespace nodesynth
#endif // IIRFILTER_H_INCLUDED
