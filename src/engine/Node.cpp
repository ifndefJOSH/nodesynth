/**********************************************************************************
 * File name: Node.cpp
 * 
 * @author Josh Jeppson
 * 
 * Description: Implementation of methods for the `Node` interface.
 * 
 * This file is licensed under the TODO license. It may be copied and modified, as 
 * well as redistributed, so long as a copy of that license is provided along with
 * this software. This is part of the NODESYNTH project, which is also under that license.
 **********************************************************************************/
#include "Node.hpp"

/**
 * Constructor for Node class. For all subclasses, please call `super()`
 * 
 * @param name Name of the node
 * */
Node::Node(std::string name) {
	this->name = name;
	this->setUpIO();
}
/**
 * Destructor for `Node` class. Cleans up used memory
 * */
Node::~Node() {
	delete outputNodes;
	delete outputBuffers;
	for (int i = 0; i < numInputs; i++) {
		delete inputs[i];
	}
	delete inputs;
	delete inputTypes;
	delete bufferTypes;
}

/**
 * Sets all updates forward
 * */
void Node::updateForward() {
	updateBuffer();
	Node * n;
	for (int i = 0; i < numOutputs; i++) {
		n = outputNodes[i];
		n->updateForward();
	}
}
// /**
//  * Updates the next node's output buffers.
//  * */
// void Node::updateBuffer() {
	
// }
/**
 * Connects buffer at index `index` to `node->buffers[targetIndex]`
 * 
 * @param index Index of output to connect
 * @param targetIndex Index in `node` to get buffer
 * @param node Pointer to the node to connect
 * */
bool Node::connectBuffer(uint8_t index, uint8_t targetIndex, Node * node) {
	if (node == nullptr ) {
		std::cerr << "[ERROR] Cannot connect node to null pointer." << std::endl;
		return;
	}
	if (this->bufferTypes[index] != node->getBufferType(index)) {
		std::cerr << "[INFO] Cannot connect node \"" << this->name
			<< "\" output \"" << this->outputNames[index] << "\" to input buffer at node name \""
			<< node->getName() << "\" input \"" << node->getInputName(index) << "\" so not connecting." 
			<< std::endl;
		std::cerr << "Reason: I/O types are different: " << IOTypeNames[bufferTypes[index]] << " and "
			<< IOTypeNames[node->getBufferType(index)] << std::endl;
		return false;
	}
	/* Connect buffer */
	outputBuffers[index] = node->getInput(targetIndex);
	outputNodes[index] = node;
	return true;
}
/**
 * Disconnets an output buffer node
 * 
 * @param index Index of the output node to disconnect
 * */
void Node::disconnectBuffer(uint8_t index) {
	std::cout << "Disconnecting node \"" << name << "\" from node \"" << outputNodes[index] << "\"." << std::endl;
	outputBuffers[index] = nullptr;
	outputNodes[index] = nullptr;
}
/**
 * Tells if buffer is connected
 * 
 * @param index Index of buffer
 * */
bool Node::isBufferConnected(uint8_t index) {
	return outputNodes[index] != nullptr;
}
/**
 * Gets the output type ad index `index`
 * 
 * @param index Index of buffer
 * */
uint8_t Node::getBufferType(uint8_t index) {
	return bufferTypes[index];
}
/**
 * Gets the input type at index `index`
 * 
 * @param index Index of buffer
 * */
uint8_t Node::getInputType(uint8_t index) {
	return inputTypes[index];
}
/**
 * Gets the name of the input at index `index`
 * 
 * @param index Index of buffer
 * */
std::string Node::getInputName(uint8_t index) {
	return inputNames[index];
}
/**
 * Gets a pointer to the input buffer at index `index`
 * 
 * @param index Index of buffer
 * */
void * Node::getInput(uint8_t index) {
	return inputs[index];
}
