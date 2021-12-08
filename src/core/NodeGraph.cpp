#include "NodeGraph.h"
#include "cli/messages.h"

#include <functional>

using namespace nodesynth;

NodeGraph::NodeGraph()
	: eventsIn("EventsIn")
	, audioOutLeft("AudioOutLeft")
	, audioOutRight("AudioOutRight")
	, audioOutLeftTime("AudioOutLeftTime")
	, audioOutRightTime("AudioOutRightTime")
{

}

NodeGraph::~NodeGraph() {
	destroyWorkerThread();
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
	std::shared_ptr<Node> n = std::make_shared<Node> (*node);
	this->insertNode(n);
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
}
void
NodeGraph::createWorkerThread(){
	// Bind worker thread to function
	std::function<void(void)> workerProcess = std::bind(&NodeGraph::updateAllBuffers, this);
	workerThread = std::make_shared<std::thread> (workerProcess)

}
void
NodeGraph::destroyWorkerThread(){
	delete workerThread;
}

void
NodeGraph::updateAllBuffers(){
	// Perform a depth first search to find the roots
	std::vector<Node *> roots;
	// TODO: Depth first search

	while (true) {
		for (Node * root : roots) {
			// Tell that node to update itself and all of its successors
			root->updateForward();
		}
	}
}
