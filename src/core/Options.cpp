#include "Options.h"

using namespace nodesynth;

void
Options::initialize(uint64_t nSampleRate, uint64_t nBufferSize, uint8_t nMidiChannelCount){
	sampleRate = nSampleRate;
	buffferSize = nBufferSize;
	midiChannelCount = nMidiChannelCount;
	initialized = true;
}

std::chrono::duration<double>
Options::getElapsedTime(){
	std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - startTime;
	return dur;
}
uint64_t
Options::getSampleRate(){
	return sampleRate;
}
uint64_t
Options::getBufferSize(){
	return buffferSize;
}


uint8_t
Options::getMidiChannelCount() {
	return midiChannelCount;
}
