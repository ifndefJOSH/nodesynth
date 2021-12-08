#include "OscillatorNode.h"
#include <iostream>
#include <cmath>

#define TUNING 440

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

double
frequencyFromMidiNote(uint8_t midiNote) {
	return TUNING * pow(2, ((double) midiNote - 69.0) / 12);
}
