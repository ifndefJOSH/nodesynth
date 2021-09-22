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

namespace nodesynth {
	class NodeSynth {
	public:
		NodeSynth();
		~NodeSynth();
		void startWorkerThread();
		void readPresetFile(std::string file);
		void writePresetFile(std::string file);
	protected:

	private:
		PresetParser * parser;
		NodeGraph * graph;
	};
} // nodesynth


#endif // NODESYNTH_H_INCLUDED
