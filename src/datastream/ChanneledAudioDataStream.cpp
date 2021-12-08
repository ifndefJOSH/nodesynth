#include "ChanneledAudioDataStream.h"

#include <stdlib.h>
#include <string.h>

using namespace nodesynth;

ChanneledAudioDataStream::ChanneledAudioDataStream(const std::string name) :
	DataStream(name, CHANNELED_AUDIO)
{
	// Set up our MIDI channels
	this->numMidiChannels = Options::getMidiChannelCount();
	this->bufSize = Options::getBufferSize();
	this->channeledAudio = new std::complex<double> *[numMidiChannels];
	for (uint8_t i = 0; i < numMidiChannels; i++) {
		// Allocate new MIDI channel
		this->channeledAudio[i] = new std::complex<double>[bufSize];
	}
	copySize = sizeof(std::complex<double>) * bufSize;
}

ChanneledAudioDataStream::~ChanneledAudioDataStream() {
	// Clear memory used by data streams
	for (uint8_t i = 0; i < numMidiChannels; i++) {
		delete this->channeledAudio[i];
	}
	delete this->channeledAudio;
}
void
ChanneledAudioDataStream::updateNext() {
	// Copy all memory into the next buffer
	// NOTE: the number of MIDI channels CANNOT change once nodesynth has started, so we can assume both have the same.
}
