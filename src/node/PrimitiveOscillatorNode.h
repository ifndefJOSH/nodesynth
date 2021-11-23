
/**
 * Header file for PrimitiveOscillatorNode class
 *
 * Created by Josh Jeppson on 9/21/2021
 *
 * This file contains method definitions implemented in PrimitiveOscillatorNode.cpp for the nodesynth project.
 * It is licensed under the MIT license, and is provided at NO WARRANTY. Nodesynth is a project
 * which aims to create a declarative Prolog-like language for musical synthesis. Eventually, I
 * also plan to create a GUI, similar to those in Blender, Natron, or Carla.
 **/


#ifndef PRIMITIVEOSCILLATORNODE_H_INCLUDED
#define PRIMITIVEOSCILLATORNODE_H_INCLUDED

#include "OscillatorNode.h"

namespace nodesynth {
	 class PrimitiveOscillatorNode : OscillatorNode {
	public:
		PrimitiveOscillatorNode();
	protected:
		void createSawToothWave(
			double frequency
			, double velocity
			, uint8_t channel
		);
		void createSquareWave(
			double frequency
			, double velocity
			, uint8_t channel
		);
		void createSineWave(
			double frequency
			, double velocity
			, uint8_t channel
		);
		void createTriangleWave(
			double frequency
			, double velocity
			, uint8_t channel
		);
	private:

	};
} // namespace nodesynth
#endif // PRIMITIVEOSCILLATORNODE_H_INCLUDED
