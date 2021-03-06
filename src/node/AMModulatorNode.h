
/**
 * Header file for AMModulatorNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in AMModulatorNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/
		

#ifndef AMMODULATORNODE_H_INCLUDED
#define AMMODULATORNODE_H_INCLUDED

#include "ModulatorNode.h"

namespace nodesynth {
	 class AMModulatorNode : ModulatorNode {
	public:
		AMModulatorNode(const std::string name);
		virtual void update();
	protected:
	private:
	};
} // namespace nodesynth
#endif // AMMODULATORNODE_H_INCLUDED
