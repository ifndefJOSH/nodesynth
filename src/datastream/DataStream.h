
/**
 * Header file for DataStream class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in DataStream.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef DATASTREAM_H_INCLUDED
#define DATASTREAM_H_INCLUDED

#include <string>

#include "../core/Options.h"

namespace nodesynth {

	enum streamtype {
		// (Monaural) Audio in frequency domain
		AUDIO
		// (Monaural) Audio in frequency domain separated by MIDI channel
		, CHANNELED_AUDIO
		// (Monaural) Audio in time domain
		, TIME_DOMAIN_AUDIO
		// Midi Events
		, MIDI
		// PrimitiveDataStream<type> is forward declared
		, PRIMITIVE_INTEGER
		, PRIMITIVE_UNSIGNED_INTEGER
		, PRIMITIVE_FLOAT
		, PRIMITIVE_BOOLEAN
		// Base case so g++ doesn't yell at me
		, UNDEFINED_TYPE
	};

	class DataStream {
	public:
		DataStream(const std::string name, streamtype type = UNDEFINED_TYPE);
		void connect(const DataStream & ds);
		const streamtype getStreamType();
		virtual void updateNext() = 0;
		std::string getName();
	protected:
		const streamtype type;
		DataStream & next;
	private:
		const std::string name;
	};
} // namespace nodesynth
#endif // DATASTREAM_H_INCLUDED
