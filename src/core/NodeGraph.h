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
#include "../datastream/MidiStream.h"
#include "../datastream/AudioDataStream.h"
#include "../datastream/TimeDomainAudioStream.h"

#include "PresetParser.cpp"

#include <unordered_map>	// Used for graphMap
#include <memory>			// Used for std::shared_ptr
#include <string>			// Used for map keys
#include <vector>			// Used for clearWithoutDeleting
#include <thread>			// Used for worker thread

namespace nodesynth {
	class NodeGraph {
		public:
			NodeGraph();
			~NodeGraph();
			/**
			 * Gets a pointer to a node, given the node's name. Returns null if
			 * node with that name does not exist.
			 *
			 * @param name Name of the node to get.
			 * @return Pointer to node with that name or nullptr if not.
			 * */
			std::shared_ptr<Node> getNodeByName(std::string name);
			/**
			 * Inserts a node into the node graph
			 *
			 * @param node The node to insert
			 * */
			void insertNode(std::shared_ptr<Node> node);
			/**
			 * Clears all nodes in the graph
			 * */
			void clearGraph();
			/**
			 * Clears all nodes in the graph without deleting them.
			 *
			 * @return a linked list (in no particular order) of all nodes in the graph
			 * */
			std::vector<std::shared_ptr<Node>> clearWithoutDeleting();
			/**
			 * Connects ports from two nodes in the graph.
			 *
			 * @param fromNodeId Id of the "from" node
			 * @param fromNodePortId The Id of the output port within the from node to connect
			 * @param toNodeId Id of the "to" node
			 * @param toNodePortId The id of the input port within the node to connect to
			 * */
			bool connectPorts(
				std::string fromNodeId
				, std::string fromNodePortId
				, std::string toNodeId
				, std::string toNodePortId
			);
			/**
			 * Creates the worker thread.
			 * */
			void createWorkerThread();
			/**
			 * Destroys the worker thread
			 * */
			void destroyWorkerThread();
			// Data streams
			MidiStream eventsIn;
			AudioDataStream audioOutLeft;
			AudioDataStream audioOutRight;
		protected:
			/**
			 * Updates all buffers in the node graph
			 * */
			void updateAllBuffers();
		private:
			std::unordered_map<std::string, std::shared_ptr<Node>> graphMap;
			std::shared_ptr<std::thread> workerThread;
			// Output data streams
			TimeDomainAudioStream audioOutLeftTime;
			TimeDomainAudioStream audioOutRightTime;
	};
}

#endif // NODEGRAPH_H_INCLUDED
