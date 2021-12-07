#include "AudioDechanneler.h"
#include "../core/cli/messages.h"

using namespace nodesynth;

AudioDechanneler::AudioDechanneler(std::string name) :
	: Node(name)
{
	initializePorts();
	this->output = nullptr;
}

AudioDechanneler::~AudioDechanneler() {
	if (output) {
		delete output;
	}
}

void
AudioDechanneler::initializePorts() {
	if (output) {
		delete output;
	}
	output = new AudioDataStream("output");
}

void
AudioDechanneler::update() {
	if (!output) {
		error("Output is null! Cannot connect!");
		return;
	}
	// Average the values of the input and place in output
	for (uint64_t i = 0; i < Options::getBufferSize(); i++) {
		output[i] = 0;
		for (uint8_t j = 0; j < Options::getMidiChannelCount(); j++) {
			output[i] += input[j][i];
		}
		output[i] /= Options::getBufferSize();
	}
}

void
AudioDechanneler::connectInput(ChanneledAudioDataStream * input) {
	this->input = input;
}

