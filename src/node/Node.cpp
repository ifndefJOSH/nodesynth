#include "Node.h"

using namespace nodesynth;

Node::Node(const std::string name) :
	name(name)
{
	// Intentionally left empty
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
	this->update();
	for (Node * child : this->children) {
		child->updateForward();
	}
}


