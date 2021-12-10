
/**
 * Header file for PanningNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in PanningNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/
		

#ifndef PANNINGNODE_H_INCLUDED
#define PANNINGNODE_H_INCLUDED

#include "Node.h"

namespace nodesynth {
	 class PanningNode : Node {
	public:
		PanningNode(std::string name);
		virtual void initializePorts();
		virtual void update();
	protected:
	private:
	};
} // namespace nodesynth
#endif // PANNINGNODE_H_INCLUDED
