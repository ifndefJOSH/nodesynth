
/**
 * Header file for FilterHostNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in FilterHostNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef FILTERHOSTNODE_H_INCLUDED
#define FILTERHOSTNODE_H_INCLUDED

#include "Node.h"
#include "../datastream/AudioDataStream.h"
#include "../filter/Filter.h"

namespace nodesynth {
	 class FilterHostNode : Node {
	public:
		FilterHostNode(std::string name);
		virtual void initializePorts();
		// Does nothing if parameters of filter have not changed.
		virtual void update();
		/**
		 *	Gets whether or not this is a "live" filter, AKA, has parameters
		 *	that are updated in realtime.
		 *
		 *	@return Whether or not this is live
		 * */
		bool getLive();
		/**
		 *  Sets whether or not this is a live filter, AKA has parameter
		 *  that are updated in realtime.
		 *
		 *  @param lv Whether or not this filter host is to be live
		 * */
		void makeLive(bool lv = true);
		/**
		 * Allows you to set a filter
		 *
		 * @param f Filter to set
		 * */
		void setFilter(Filter * f);
		/**
		 * Gets this node's current filter
		 *
		 * @return current filter
		 * */
		Filter * getFilter();
		// Output streams
		AudioDataStream * filterValue;
	protected:
	private:
		Filter * filter;
		bool live;
	};
} // namespace nodesynth
#endif // FILTERHOSTNODE_H_INCLUDED
