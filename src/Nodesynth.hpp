#ifndef NODESYNTH_HPP_
#define NODESYNTH_HPP_

#include "lv2/core/lv2.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define NODESYNTH_URI "TODO"

/**
 * Port definitions
 * 
 * NODESYNTH_CONTROL (0): Controls whether or not NodeSynth is enabled
 * NODESYNTH_MIDI_IN (1): Midi buffer input from DAW host.
 * NODESYNTH_AUDIO_OUT_LEFT (2): Left channel of stereo audio output.
 * */
typedef enum {
	NODESYNTH_CONTROL = 0
	, NODESYNTH_MIDI_IN = 1
	, NODESYNTH_AUDIO_OUT_LEFT = 2
	, NODESYNTH_AUDIO_OUT_RIGHT = 3
} PortIndex;
/**
 * Main nodesynth class.
 * */
class NodeSynth {
public:
	// Port buffers
	const LV2_Atom_Sequence * control;
	const float * midi_in;
	float * audio_out_left;
	float * audio_out_right;
	
	// Features
	LV2_URID_Map*        map;
	LV2_Worker_Schedule* schedule;
	LV2_Log_Logger       logger;
	
protected:
	
private:
};

#endif /* NODESYNTH_HPP_ */
