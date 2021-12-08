#include "PresetParser.h"
#include "cli/messages.h"

#include <fstream>

using namespace nodesynth;

PresetParser::PresetParser(NodeGraph * graph)
	: graph(graph)
{
	// Intentionally left empty
}

PresetParser::~PresetParser() {

}


void
PresetParser::parse(std::string filename) {
	std::ifstream inputFile;
	inputFile.open(filename, std::ifstream::in);

	inputFile.close();
}

void
PresetParser::deparse(std::string filename) {

}
