#ifndef FILTERNODE_HPP_
#define FILTERNODE_HPP_

#include "Filter.hpp"
#include "Node.hpp"

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

class FilterNode : Node {
public:
	virtual FilterNode(uint64_t globalBufferSize, std::string name) : out(_outbuf) {
		this->super(name)
		this->f = new Filter(globalBufferSize);
	}
	virtual ~FilterNode();
	
	void changeBufferSize(uint64_t bufSize);
	uint64_t getBufferSize();
	
protected:
	// Impulse response in time domain
	double * iResponse;
	// Filter (stores impulse response in frequency domain)
	Filter * f;
private:
	// Pointer to some other  node's output (as input data for us)
	double * inputBuffer;
	// Our output buffer--may have to change this to public
	double * _outbuf
};
#endif /* FILTERNODE_HPP_ */
