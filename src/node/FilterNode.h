
/**
 * Header file for FilterNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in FilterNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef FILTERNODE_H_INCLUDED
#define FILTERNODE_H_INCLUDED

#include "Node.h"
#include "../datastream/AudioDataStream.h"

namespace nodesynth {
	 class FilterNode : Node {
	public:
		FilterNode(std::string name);
		virtual void initializePorts();
		// Filter node is still abstract
		virtual void update() = 0;
		// Sets the input streams
		void setFilterInputStream(AudioDataStream * filterValue);
		void setAudioInputStream(AudioDataStream * audio);
		// Output streams
		AudioDataStream * filteredAudio;
	protected:
	private:
		AudioDataStream * filterValue;
		AudioDataStream * audio;
	};
} // namespace nodesynth
#endif // FILTERNODE_H_INCLUDED
