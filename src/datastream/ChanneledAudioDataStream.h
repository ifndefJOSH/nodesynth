
/**
 * Header file for ChanneledAudioDataStream class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in ChanneledAudioDataStream.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef CHANNELED_AUDIO_DATA_STREAM_INCLUDED
#define CHANNELED_AUDIO_DATA_STREAM_INCLUDED

#include "DataStream.h"

#include <complex>

namespace nodesynth {
	 class ChanneledAudioDataStream : DataStream {
	public:
		ChanneledAudioDataStream(const std::string name);
		~ChanneledAudioDataStream();
		virtual void updateNext();
		std::complex<double> ** channeledAudio;
	protected:
	private:
		uint8_t numMidiChannels;
		uint64_t bufSize;
		size_t copySize;
	};
} // namespace nodesynth

#endif
