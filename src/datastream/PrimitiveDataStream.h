
/**
 * Header file for PrimitiveDataStream class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in PrimitiveDataStream.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/

#ifndef PRIMITIVE_DATA_STREAM_H_INCLUDED
#define PRIMITIVE_DATA_STREAM_H_INCLUDED

#include "DataStream.h"

namespace nodesynth {
	template <typename T>
	class PrimitiveDataStream : DataStream {
	public:
		PrimitiveDataStream(const std::string name);
		virtual void updateNext();
		bool wasUpdated();
		T getValueThisCycle();
		void setValueThisCycle(T value);
	protected:
	private:
		T valueThisCycle;
		bool updated;
	};
} // namespace nodesynth


#endif // PRIMITIVE_DATA_STREAM_H_INCLUDED
