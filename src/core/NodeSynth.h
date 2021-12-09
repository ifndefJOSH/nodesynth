#ifndef NODESYNTH_H_INCLUDED
#define NODESYNTH_H_INCLUDED

#include "Options.h"
#include "PresetParser.h"
#include "NodeGraph.h"

#include <string>

#ifdef NODESYNTH_JACK_COMPILE
// Include headers necessary for JACK compilation
#include <jack/jack.h>
#include <jack/control.h>
#include <jack/session.h>

#endif // NODESYNTH_JACK_COMPILE

#ifdef NODESYNTH_LV2_COMPILE
#include "lv2/core/lv2.h"
#endif // NODESYNTH_LV2_COMPILE

#ifdef NODESYNTH_VST3_COMPILE
// TODO: Add headers for VST3 compile
#endif

#ifdef NODESYNTH_STANDALONE_COMPILE
// TODO: Add jeaders for standalone compile
#endif // NODESYNTH_STANDALONE_COMPILE

namespace nodesynth {
#ifdef NODESYNTH_JACK_COMPILE
	typedef struct {
		jack_port_t * input_port;
		jack_port_t * output_port_left;
		jack_port_t * output_port_right;
	} port_pair_t;
	/**
	 * This function is called every processing cycle
	 * */
	int inprocess(jack_nframes_t nframes, port_pair_t * arg);
	/**
	 * Called when Nodesynth is set up within JACK
	 * */
	int jack_initialize(jack_client_t * client, const char * load_init);
	/**
	 * Called when Nodesynth is finished within JACK
	 * */
	void jack_finish(port_pair_t * arg);
#endif // NODESYNTH_JACK_COMPILE
	class NodeSynth {
	public:
		NodeSynth();
		~NodeSynth();
		void startWorkerThread();
		void readPresetFile(std::string file);
		void writePresetFile(std::string file);
		void setOptions();
#ifdef NODESYNTH_JACK_COMPILE
		static void setClient(jack_client_t * clientCurrent_n);
#endif // NODESYNTH_JACK_COMPILE
	protected:
#ifdef NODESYNTH_JACK_COMPILE
		inline static jack_client_t * clientCurrent;
#endif // NODESYNTH_JACK_COMPILE
	private:
		PresetParser * parser;
		NodeGraph * graph;
	};
} // nodesynth


#endif // NODESYNTH_H_INCLUDED
