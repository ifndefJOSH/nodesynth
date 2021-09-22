/**
 * Header file for AMModulatorNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in AMModulatorNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
**/
#ifndef PRESET_PARSER_H_INCLUDED
#define PRESET_PARSER_H_INCLUDED

#include "NodeGraph.h"
#include <memory>


namespace nodesynth {

	class PresetParser{
	public:
		PresetParser(NodeGraph * graph);
		~PresetParser();
		/**
		 * Parses the file at `filename` and adds it into the parent node graph
		 *
		 * @param filename The file to parse
		 * */
		void parse(std::string filename);
		/**
		 * "Deparses" (aka writes from existing state) from the existing node graph
		 *
		 * @param filename The file to write to
		 * */
		void deparse(std::string filename);
	protected:
		void parseNode();
		void deparseNode();
	private:
		const NodeGraph * graph;
	};
}

#endif // PRESET_PARSER_H_INCLUDED
