
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

// According to https://fftw.org/fftw3_doc/Complex-numbers.html, including
// <complex.h> BEFORE <fftw3.h> allows us to use the builtin C/++ complex
// type and overloaded operators
#include <complex>
#include <fftw3.h>

namespace nodesynth {
	typedef unsigned char waveform_t;
	enum WAVEFORMS {
		SAWTOOTH	= 0
		, SQUARE	= 1
		, SINE		= 2
		, TRIANGLE	= 3
	};
	 class PrimitiveOscillatorNode : OscillatorNode {
	public:
		PrimitiveOscillatorNode(std::string name);
		~PrimitiveOscillatorNode();
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

		virtual void update();
	private:
		waveform_t waveformType;
		fftw_complex ** temporaryBuffers;
		fftw_plan p;
	};
} // namespace nodesynth
#endif // PRIMITIVEOSCILLATORNODE_H_INCLUDED
