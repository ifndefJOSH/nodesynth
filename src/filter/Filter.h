
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
	class Filter {
	public:
		Filter();
		~Filter();
		virtual void createFilter() = 0;
		void applyFilter(AudioDataStream & source, AudioDataStream & dest);
	protected:
	private:
	};
} // namespace nodesynth

#endif // FILTER_H_INCLUDED
