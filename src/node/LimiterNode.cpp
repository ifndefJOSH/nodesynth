#include "LimiterNode.h"

using namespace nodesynth;

LimiterNode::LimiterNode(std::string name)
	: Node(name)
	, limit(0)
	, inputStream(nullptr)
{
	// Intentionally left empty
}

LimiterNode::~LimiterNode() {
	if (outputStream) {
		delete outputStream;
	}
}

void
LimiterNode::initializePorts() {
	outputStream = new AudioDataStream(this->getName() + "Output");
}

void
LimiterNode::update() {
	if (!inputStream) {
		return;
	}
	// Limiting works in frequency domain as well
	for (int i = 0; i < Options::getBufferSize(); i++) {
		if (inputStream.audio[i] < limit) {
			outputStream.audio[i] = inputStream[i];
		}
		else {
			outputStream.audio[i] = limit;
		}
	}
}

double
LimiterNode::getLimit() {
	return limit;
}

void
LimiterNode::setLimit(double lim) {
	limit = lim;
}


void
LimiterNode::setInputStream(AudioDataStream * input) {
	inputStream = input;
}
