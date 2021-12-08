#include "Options.h"
#include "cli/messages.h"
#include "cli/ANSIColors.h"

#include <iostream>

using namespace nodesynth;

void
Options::initialize(uint64_t nSampleRate, uint64_t nBufferSize, uint8_t nMidiChannelCount){
	sampleRate = nSampleRate;
	bufferSize = nBufferSize;
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
	return bufferSize;
}


uint8_t
Options::getMidiChannelCount() {
	return midiChannelCount;
}

bool
Options::getVerbose() {
	return verbose;
}

void
Options::setVerbose(bool vb) {
	verbose = vb;
}

bool
Options::getSilent() {
	return silent;
}

void
Options::setSilent(bool sl) {
	silent = sl;
}

void
Options::checkAllOptions() {
	// If we have not initialized
	if (!initialized) {
		errorExit("Options not initialized!");
	}
	// Check validity of options
	if (verbose && silent) {
		std::cerr << BOLD(FYEL("[OPTION WARNING]:"));
		std::cerr << "You have indicated you wish for both silent and verbose output." << std::endl;
		std::cerr << "\tSilent takes precedence over verbose, so this will be the only message you see.";
		std::cerr << "Not even option warnings will show now." << std::endl;
	}
	// Check MIDI Channel Count with max value
	if (midiChannelCount > MAX_MIDI_CHANNELS) {
		warning("Number of MIDI channels is greater than MAX_MIDI_CHANNELS!");
	}

}
