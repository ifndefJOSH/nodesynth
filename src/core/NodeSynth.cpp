#include "NodeSynth.h"
#include "cli/messages.h"

using namespace nodesynth;

NodeSynth::NodeSynth(){
	graph = new NodeGraph();
	parser = new PresetParser(graph);
}

NodeSynth::~NodeSynth(){
	graph->destroyWorkerThread();
	delete parser;
	delete graph;
}

void
NodeSynth::startWorkerThread(){
	graph->createWorkerThread();
}

void
NodeSynth::readPresetFile(std::string file){
	if (!parser) {
		errorExit("Parser is null!");
	}
	parser->parse(file);
}

void
NodeSynth::writePresetFile(std::string file){
	if (!parser) {
		errorExit("Parser is null!");
	}
	parser->deparse(file);
}
