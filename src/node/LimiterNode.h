
/**
 * Header file for LimiterNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in LimiterNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef LIMITERNODE_H_INCLUDED
#define LIMITERNODE_H_INCLUDED

#include "Node.h"

#include "../datastream/AudioDataStream.h"

namespace nodesynth {
	class LimiterNode : Node {
	public:
		LimiterNode(std::string name);
		virtual void initializePorts();
		virtual void update();
		double getLimit();
		void setLimit(double lim);
		void setInputStream(AudioDataStream * input);
		AudioDataStream * outputStream;
	protected:

	private:
		double limit;
		AudioDataStream * inputStream;
	};
} // namespace nodesynth
#endif // LIMITERNODE_H_INCLUDED
