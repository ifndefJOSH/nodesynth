/**********************************************************************************
 * File name: Node.hpp
 * 
 * @author Josh Jeppson
 * 
 * Description: Header for the `Node` interface.
 * 
 * This file is licensed under the TODO license. It may be copied and modified, as 
 * well as redistributed, so long as a copy of that license is provided along with
 * this software. This is part of the NODESYNTH project, which is also under that license.
 **********************************************************************************/
#ifndef NODE_HPP_
#define NODE_HPP_
/**
 * Node class for each node in the backend.
 * */

#include <string>
#include <iostream>
#include <stdint.h>

enum IOTypes {
	MIDI = 0
	, AUDIO = 1
	, INTEGER = 2
	, FLOAT = 3 // All "floating points" are double precision
};

std::string IOTypeNames[] = {
	"MIDI"
	, "AUDIO"
	, "INTEGER"
	, "FLOAT"
};

class Node {
public:
	Node(std::string name);
	~Node();

	/**
	 * Sets the name of the Node
	 * 
	 * @param name The name to set
	 * */
	void setName(std::string name) {
		this->name = name;
	}
	/**
	 * Gets the name for the Node
	 * 
	 * @return The name of the node.
	 * */
	std::string getName() {
		return this->name;
	}
	/**
	 * Sets up the IO ports. This function *must* be overridden by subclasses
	 * */
	virtual void setUpIO() = 0;
	virtual void updateBuffer() = 0;
	void updateForward();
	bool connectBuffer(uint8_t index, uint8_t targetIndex, Node * node);
	void disconnectBuffer(uint8_t index);
	bool isBufferConnected(uint8_t index);
	uint8_t getBufferType(uint8_t index);
	uint8_t getInputType(uint8_t index);
	std::string getInputName(uint8_t index);
	void * getInput(uint8_t index);
protected:
	Node ** outputNodes;
	void ** outputBuffers;
	uint8_t * bufferTypes;
	std::string * inputNames;
	std::string * outputNames;
	void ** inputs;
	uint8_t * inputTypes;
	uint8_t numInputs;
	uint8_t numOutputs;
private:
	std::string name;
};


#endif /* NODE_HPP_ */
