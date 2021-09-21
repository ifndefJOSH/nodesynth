
/**
 * Header file for CompressorNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in CompressorNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/
		

#ifndef COMPRESSORNODE_H_INCLUDED
#define COMPRESSORNODE_H_INCLUDED

#include "Node.h"

namespace nodesynth {
	 class CompressorNode : Node {
	public:
		CompressorNode();
	protected:
	private:
	};
} // namespace nodesynth
#endif // COMPRESSORNODE_H_INCLUDED
