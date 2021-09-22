
/**
 * Header file for PrimitiveFilterNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in PrimitiveFilterNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/
		

#ifndef PRIMITIVEFILTERNODE_H_INCLUDED
#define PRIMITIVEFILTERNODE_H_INCLUDED

#include "FilterNode.h"

namespace nodesynth {
	 class PrimitiveFilterNode : FilterNode {
	public:
		PrimitiveFilterNode();
	protected:
	private:
	};
} // namespace nodesynth
#endif // PRIMITIVEFILTERNODE_H_INCLUDED
