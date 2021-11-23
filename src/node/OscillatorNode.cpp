#include "OscillatorNode.h"
#include <iostream>

using namespace nodesynth;

void
OscillatorNode::connect(DataStream * ds, uint8_t port) {
	switch (port) {
		case 1:
			notesIn = (MidiStream *) ds;
			break;
		default:
			std::cerr << "[ERROR]: Port number " << port << " is unknown.\n";
	}
}

void
OscillatorNode::disconnect(uint8_t port) {
	switch (port) {
		case 1:
			notesIn = NULL;
			break;
		default:
			std::cerr << "[ERROR]: Port number " << port << " is unknown.\n";
	}
}
