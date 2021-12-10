#include "FilterNode.h"

using namespace nodesynth;


FilterNode::FilterNode(std::string name)
	: Node(name)
{

}

void
FilterNode::initializePorts() {

	filteredAudio = new AudioDataStream(getName() + ":out");
}


void
FilterNode::setFilterInputStream(AudioDataStream * filterValue) {
	this->filterValue = filterValue;
}


void
FilterNode::setAudioInputStream(AudioDataStream * audio) {
	this->audio = audio;
}
