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

#ifndef NODEGRAPH_H_INCLUDED
#define NODEGRAPH_H_INCLUDED

#include "../node/Node.h"
#include "PresetParser.cpp"

#include <map>		// Used for graphMap
#include <memory>	// Used for std::shared_ptr
#include <string>	// Used for map keys
#include <vector>	// Used for clearWithoutDeleting
#include <thread>	// Used for worker thread

namespace nodesynth {
	class NodeGraph {
		public:
			NodeGraph();
			~NodeGraph();
			std::shared_ptr<Node> getNodeByName(std::string name);
			void insertNode(std::shared_ptr<Node> node);
			void clearGraph();
			std::vector<std::shared_ptr<Node>> clearWithoutDeleting();
			void createWorkerThread();
			void destroyWorkerThread();
		protected:
			void updateAllBuffers();
		private:
			std::map<std::string, std::shared_ptr<Node>> graphMap;
			std::shared_ptr<std::thread> workerThread;
	};
}

#endif // NODEGRAPH_H_INCLUDED
