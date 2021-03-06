
/**
 * Header file for AudioDataStream class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in AudioDataStream.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef AUDIODATASTREAM_H_INCLUDED
#define AUDIODATASTREAM_H_INCLUDED

#include "DataStream.h"

#include <complex>

namespace nodesynth {
	class AudioDataStream : DataStream{
	public:
		AudioDataStream(const std::string name);
		~AudioDataStream();
		std::complex<double> * audio;
	protected:
	private:
		uint64_t bufSize;
		size_t copySize;
	};
} // namespace nodesynth
#endif // AUDIODATASTREAM_H_INCLUDED
