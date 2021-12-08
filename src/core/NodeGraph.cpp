#include "NodeGraph.h"
#include "cli/messages.h"

#include <functional>

using namespace nodesynth;

NodeGraph::NodeGraph()
{
	eventsIn = new MidiStream("EventsIn");
	audioOutLeft = new AudioDataStream("AudioOutLeft");
	audioOutRight = new AudioDataStream("AudioOutRight");
	audioOutLeftTime = new TimeDomainAudioStream("AudioOutLeftTime");
	audioOutRightTime = new TimeDomainAudioStream("AudioOutRightTime");


}

NodeGraph::~NodeGraph() {
	destroyWorkerThread();
	delete eventsIn;
	delete audioOutLeft;
	delete audioOutRight;
	delete audioOutLeftTime;
	delete audioOutRightTime;
}

std::shared_ptr<Node>
NodeGraph::getNodeByName(std::string name) {
	return graphMap.at(name);
}

void
NodeGraph::insertNode(std::shared_ptr<Node> node){
	std::string name = node->getName();
}

void
NodeGraph::insertNode(Node * node) {
	// TODO: Figure out how to make_shared for an abstract class
	// std::shared_ptr<Node> n = std::make_shared<Node> (*node);
	// this->insertNode(n);
}

void
NodeGraph::clearGraph(){

}

std::vector<std::shared_ptr<Node>>
NodeGraph::clearWithoutDeleting(){
	std::vector<std::shared_ptr<Node>> undeletedNodes;
	// TODO: Add all nodes in map to this and remove keys from map
	return undeletedNodes;
}

bool
NodeGraph::connectPorts(
	std::string fromNodeId
	, std::string fromNodePortId
	, std::string toNodeId
	, std::string toNodePortId
) {
	std::shared_ptr<Node> fromNode = getNodeByName(fromNodeId);
	std::shared_ptr<Node> toNode = getNodeByName(toNodeId);
	return true; // TODO: fix
}
void
NodeGraph::createWorkerThread(){
	// Bind worker thread to function
	std::function<void(void)> workerProcess = std::bind(&NodeGraph::updateAllBuffers, this);
	workerThread = std::make_shared<std::thread> (workerProcess);

}
void
NodeGraph::destroyWorkerThread(){
	// delete workerThread;
}

void
NodeGraph::updateAllBuffers(){
	// Perform a breadth-first search to find the roots
	for (Node * root : this->roots) {
		this->findLeafs(root);
	}
	while (true) {
		for (Node * root : roots) {
			// Tell that node to update itself and all of its successors
			root->updateForward();
		}
	}
}

void
NodeGraph::findLeafs(Node * root) {
	// Base case that we should never reach but is here to avoid a segfault
	// (just in case we have a nullptr in the vector list)
	if (root == nullptr || root->visited) {
		return;
	}
	root->visited = true;
	// Sees if we are a leaf
	if (root->children.size() == 0) {
		roots.push_back(root);
	}
	else {
		for (Node * child : root->children) {
			findLeafs(child);
		}
	}
}
