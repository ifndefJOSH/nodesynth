#include "NodeSynth.h"
#include "cli/messages.h"

#include <fftw3.h>

#define DEFAULT_SAMPLE_RATE 441000
#define DEFAULT_BUFFER_SIZE 2048
#define DEFAULT_MIDI_CHANNEL_COUNT 8


using namespace nodesynth;

#ifdef NODESYNTH_JACK_COMPILE
// Non-class functions

int
inprocess(jack_nframes_t nframes, port_pair_t * arg) {
	port_pair_t * pp = arg;
	jack_default_audio_sample_t * out_left =
			(jack_default_audio_sample_t *) jack_port_get_buffer(pp->output_port_left, nframes);
	jack_default_audio_sample_t * out_right =
			(jack_default_audio_sample_t *) jack_port_get_buffer(pp->output_port_right, nframes);
	jack_default_audio_sample_t * in =
			(jack_default_audio_sample_t *) jack_port_get_buffer(pp->input_port, nframes);

	// Get the output from the NodeGraph
	for (int i = 0; i < nframes; ++i) {
		out_left[i] = (jack_default_audio_sample_t) NodeSynth::graph->audioOutLeftTime->audio[i].real();
		out_right[i] = (jack_default_audio_sample_t) NodeSynth::graph->audioOutRightTime->audio[i].real();
	}
	return 0;
}

int
jack_initialize(jack_client_t * client, const char * load_init) {

	// Set data for our NodeSynth
	NodeSynth::init();

	// Set the static client pointer
	NodeSynth::setClient(client);

	// Create ports in our port_pair_t
	port_pair_t * pp = new port_pair_t;

	// Memory error if memory allocate fails
	if (!pp) return 1;

	// Register ports with JACK
	pp->input_port = jack_port_register(
		client
		, "MIDI Input"
		, JACK_DEFAULT_MIDI_TYPE
		, JackPortIsInput
		, 0
	);

	pp->output_port_left = jack_port_register(
		client
		, "Output Left"
		, JACK_DEFAULT_AUDIO_TYPE
		, JackPortIsOutput
		, 0
	);

	pp->output_port_right = jack_port_register(
		client
		, "Output Right"
		, JACK_DEFAULT_AUDIO_TYPE
		, JackPortIsOutput
		, 0
	);

	// Joins our client
	jack_activate(client);

	// Attempt to connect to I/O ports
	if (jack_connect(client, "14:Midi Through:0:Midi Through Port-0", jack_port_name(pp->input_port))) {
		error("Unable to connect to the default MIDI input. Please open QJackCtl and manually connect.");
		return 1;
	}
	if (
		jack_connect(client, jack_port_name(pp->output_port_left), "system:playback_1") ||
		jack_connect(client, jack_port_name(pp->output_port_right), "system:playback_2")
	)
	{
			error(
				"Unable to connect to the system output! Either system:playback_1 or system:playback_2  was undefined! Please open QJackCtl and connect Nodesynth manually."
			);
		return 1;
	}
	return 0;
}

void
jack_finish(port_pair_t * arg) {
	if (arg) {
		delete arg;
	}
	NodeSynth::finish();
}
#endif // NODESYNTH_JACK_COMPILE

// Class-member methods

NodeSynth::NodeSynth(){
	// Intentionally left empty
}

NodeSynth::~NodeSynth(){
	// Intentionally left empty
}

void
NodeSynth::init() {
	NodeSynth::setOptions();
	graph = new NodeGraph();
	parser = new PresetParser(graph);

}

void
NodeSynth::finish() {
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

void
NodeSynth::setOptions() {
	uint64_t sampleRate = DEFAULT_SAMPLE_RATE;
	uint64_t bufferSize = DEFAULT_BUFFER_SIZE;
	uint8_t midiCount = DEFAULT_MIDI_CHANNEL_COUNT;
#ifdef NODESYNTH_JACK_COMPILE
	jack_get_sample_rate( /* JACK CLIENT */ clientCurrent );
	jack_get_buffer_size( /* JACK CLIENT */ clientCurrent );
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

void
NodeSynth::setClient(jack_client_t * clientCurrent_n) {
	clientCurrent = clientCurrent_n;
}
