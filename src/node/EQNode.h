
/**
 * Header file for EQNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in EQNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/
		

#ifndef EQNODE_H_INCLUDED
#define EQNODE_H_INCLUDED

#include "FilterNode.h"

namespace nodesynth {
	 class EQNode : FilterNode {
	public:
		EQNode(const std::string name);
		virtual void initializePorts();
		virtual void update();
	protected:
	private:
	};
} // namespace nodesynth
#endif // EQNODE_H_INCLUDED
