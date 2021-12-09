
/**
 * Header file for MidiStream class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in MidiStream.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef MIDISTREAM_H_INCLUDED
#define MIDISTREAM_H_INCLUDED

#include "DataStream.h"

namespace nodesynth {
	struct MidiNote {
		uint8_t note;
		double time; // Time since we have turned on
		double duration;
		bool on;
		double velocity;
	};
	class MidiStream : public DataStream {
	public:
		MidiStream(const std::string name);
		~MidiStream();
		virtual void update();
		MidiNote * notes;
	protected:
	private:
		uint64_t numMidiChannels;
		double timePerBuffer;
	};
} // namespace nodesynth
#endif // MIDISTREAM_H_INCLUDED
