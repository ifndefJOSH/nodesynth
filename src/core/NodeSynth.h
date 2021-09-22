#ifndef NODESYNTH_H_INCLUDED
#define NODESYNTH_H_INCLUDED

#include "Options.h"

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
	protected:

	private:
	};
} // nodesynth


#endif // NODESYNTH_H_INCLUDED
