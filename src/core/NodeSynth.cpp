#include "NodeSynth.h"
#include "cli/messages.h"

#define DEFAULT_SAMPLE_RATE 441000
#define DEFAULT_BUFFER_SIZE 2048
#define DEFAULT_MIDI_CHANNEL_COUNT 8

using namespace nodesynth;

NodeSynth::NodeSynth(){
#ifdef NODESYNTH_JACK_COMPILE
	// Set client
	client = jack_client_open(
		"Nodesynth Instance"
		, (jack_options_t) JackOpenOptions
		, nullptr
	);
	if (!client) {
		errorExit("JACK client is null!");
	}
#endif // NODESYNTH_JACK_COMPILE
	this->setOptions();
	graph = new NodeGraph();
	parser = new PresetParser(graph);
}

NodeSynth::~NodeSynth(){
	graph->destroyWorkerThread();
	delete parser;
	delete graph;
	if (client) {
		delete client;
	}
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

void
NodeSynth::setOptions() {
	uint64_t sampleRate = DEFAULT_SAMPLE_RATE;
	uint64_t bufferSize = DEFAULT_BUFFER_SIZE;
	uint8_t midiCount = DEFAULT_MIDI_CHANNEL_COUNT;
#ifdef NODESYNTH_JACK_COMPILE
	jack_get_sample_rate( /* JACK CLIENT */ client );
	jack_get_buffer_size( /* JACK CLIENT */ client );
#endif // NODESYNTH_JACK_COMPILE
	Options::initialize(
		/* Sample Rate */
		sampleRate
		/* Buffer Size */
		, bufferSize
		/* Midi Channel Count */
		, DEFAULT_MIDI_CHANNEL_COUNT
	);
}

