#include "NodeGraph.h"

using namespace nodesynth;

NodeGraph::NodeGraph() {

}
NodeGraph::~NodeGraph() {

}
std::shared_ptr<Node>
NodeGraph::getNodeByName(std::string name) {

}
void
NodeGraph::insertNode(std::shared_ptr<Node> node){

}
void
NodeGraph::clearGraph(){

}
std::vector<std::shared_ptr<Node>>
NodeGraph::clearWithoutDeleting(){

}
void
NodeGraph::createWorkerThread(){
	// Bind worker thread to function
	std::function<void(void)> workerProcess = std::bind(&NodeGraph::updateAllBuffers, &this);
// 	workerThread = std::allocate_shared
}
void
NodeGraph::destroyWorkerThread(){

}

void
NodeGraph::updateAllBuffers(){
	while (true) {

	}
}
