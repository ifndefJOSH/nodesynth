
/**
 * Header file for SamplerNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in SamplerNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/
		

#ifndef SAMPLERNODE_H_INCLUDED
#define SAMPLERNODE_H_INCLUDED

#include "OscillatorNode.h"

namespace nodesynth {
	 class SamplerNode : OscillatorNode {
	public:
		SamplerNode();
	protected:
	private:
	};
} // namespace nodesynth
#endif // SAMPLERNODE_H_INCLUDED
