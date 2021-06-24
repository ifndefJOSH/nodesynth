/**********************************************************************************
 * File name: OscillatorNode.hpp
 * 
 * @author Josh Jeppson
 * 
 * Description: Header for the `OscillatorNode` class.
 * 
 * This file is licensed under the TODO license. It may be copied and modified, as 
 * well as redistributed, so long as a copy of that license is provided along with
 * this software. This is part of the NODESYTH project, which is also under that license.
 **********************************************************************************/
#ifndef OSCILLATORNODE_HPP_
#define OSCILLATORNODE_HPP_

#include <iostream>
#include <fftw3.h>

#include "Node.hpp"
#include "Oscillator.hpp"

class OscillatorNode : public Node, public Oscillator {
public:
    OscillatorNode(std::string name);
    ~OscillatorNode();
    void setUpIO();
protected:

private:

};

#endif /* OSCILLATORNODE_HPP_ */