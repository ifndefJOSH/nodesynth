
/**
 * Header file for Node class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in Node.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <map>
#include <string>
#include <memory>

#include "../datastream/DataStream.h"

namespace nodesynth {
	class Node {
	public:
		Node();
		~Node();
		virtual void initializePorts() = 0;
	protected:
		void addDataStreamToPorts(std::shared_ptr<DataStream> ds);
	private:
		std::map<std::string, std::shared_ptr<DataStream>> ports;
	};
} // namespace nodesynth

#endif // NODE_H_INCLUDED
