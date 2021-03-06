
/**
 * Header file for ModulatorNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in ModulatorNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef MODULATORNODE_H_INCLUDED
#define MODULATORNODE_H_INCLUDED

#include "Node.h"

namespace nodesynth {
	 class ModulatorNode : Node {
	public:
		ModulatorNode(std::string name);
		virtual void initializePorts();
		virtual void update() = 0;
	protected:
	private:
	};
} // namespace nodesynth
#endif // MODULATORNODE_H_INCLUDED
