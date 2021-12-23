#include "FilterHostNode.h"

using namespace nodesynth;

FilterHostNode::FilterHostNode()
	: Node(name)

{

}

void
FilterHostNode::initializePorts() {

}

void
FilterHostNode::update() {
	// Do nothing if the filter is not live
	if (!live) {
		return;
	}
}

bool
FilterHostNode::getLive() {
	return live;
}

void
FilterHostNode::makeLive(bool lv = true) {
	live = lv;
}
