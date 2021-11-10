#include "MidiStream.h"

using namespace nodesynth;

MidiStream::MidiStream(const std::string name) :
	DataStream(name, MIDI)
{
	this->numMidiChannels = Options::getMidiChannelCount();
	notes = new MidiNote[numMidiChannels];
}

MidiStream::~MidiStream() {
	delete notes;
}
