
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
#include "../core/Options.h"

namespace nodesynth {
	class Node {
	public:
		Node(const std::string name);
		~Node();
		virtual void initializePorts() = 0;
		virtual void update() = 0;
		const std::string getName();
		/**
		 * Connects a Node's output to our certain Node's input at port number port
		 *
		 * @param ds The datastream to connect to
		 * @param port The port to connect it to
		 * */
		virtual void connect(DataStream * ds, uint8_t port) = 0;
		/**
		 * Disconnects a port
		 *
		 * @param port The port to disconnect
		 * */
		virtual void disconnect(uint8_t port) = 0;
	protected:
		void addDataStreamToPorts(std::shared_ptr<DataStream> ds);
	private:
		std::map<std::string, std::shared_ptr<DataStream>> ports;
		const std::string name;
	};
} // namespace nodesynth

#endif // NODE_H_INCLUDED
