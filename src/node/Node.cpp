#include "Node.h"

using namespace nodesynth;

Node::Node(const std::string name) :
	name(name)
{
	numChildrenSinceLastUpdate = 0;
}

Node::~Node() {

}
const std::string
Node::getName() {
	return this->name;
}

void
Node::addDataStreamToPorts(std::shared_ptr<DataStream> ds) {
	ports.insert(ds.getName(), ds);
}

void
Node::updateForward() {
	// Don't update until all children have been update
	if (numChildrenSinceLastUpdate != this->children.length() - 1) {
		numChildrenSinceLastUpdate++;
		return;
	}
	// Reset the number of children since last update
	numChildrenSinceLastUpdate = 0;
	this->update();
	for (Node * parent : this->parents) {
		parent->updateForward();
	}
}


