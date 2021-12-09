
/**
 * Header file for OscillatorNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in OscillatorNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef OSCILLATORNODE_H_INCLUDED
#define OSCILLATORNODE_H_INCLUDED

#include "Node.h"

#include "../datastream/MidiStream.h"
#include "../datastream/ChanneledAudioDataStream.h"

namespace nodesynth {
	class OscillatorNode : Node {
	public:
		OscillatorNode(std::string name);
		static double frequencyFromMidiNote(uint8_t midiNote);
		virtual void connect(DataStream * ds, uint8_t port);
		virtual void disconnect(uint8_t port);
		ChanneledAudioDataStream out;
		// OscillatorNode is still Abstract
		virtual void update() = 0;
	protected:
		MidiStream * notesIn;
	private:
	};
} // namespace nodesynth
#endif // OSCILLATORNODE_H_INCLUDED
