#include "MidiStream.h"

using namespace nodesynth;

MidiStream::MidiStream(const std::string name) :
	DataStream(name, MIDI)
{
	this->numMidiChannels = Options::getMidiChannelCount();
	notes = new MidiNote[numMidiChannels];
 	timePerBuffer = Options::getBufferSize() / Options::getSampleRate();
}

MidiStream::~MidiStream() {
	delete notes;
}


void
MidiStream::update() {
	for (uint8_t i = 0; i < numMidiChannels; i++) {
		if (notes[i].on) {
			notes[i].time += timePerBuffer; // Update elapsed time
			if (notes[i].time >= notes[i].duration) {
				notes[i].on = false;
			}
		}
	}
}

