
/**
 * Header file for Node class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in Node.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/

#ifndef AUDIO_DECHANNELER_H_INCLUDED
#define AUDIO_DECHANNELER_H_INCLUDED


#include "Node.h"
#include "../datastream/ChanneledAudioDataStream.h"
#include "../datastream/AudioDataStream.h"

namespace nodesynth {
	class AudioDechanneler : Node {
	public:
		AudioDechanneler(std::string name);
		~AudioDechanneler();
		virtual void initializePorts();
		/**
		 * Updates our ports
		 * */
		virtual void update();
		void connectInput(ChanneledAudioDataStream * input);
		AudioDataStream * output;
	protected:

	private:
		ChannelAudioDataStream * input;
	};
} // namespace nodesynth
#endif // AUDIO_DECHANNELER_H_INCLUDED

