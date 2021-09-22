#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

#include <chrono>	// For elapsed time
#include <cstdint>	// For sampling rate and buffer size

#define NODESYNTH_JACK_COMPILE

namespace nodesynth {
	class Options {
	public:
		/**
		 * Initializes everything in this static class.
		 *
		 * @param nSampleRate The sample rate for nodesynth to use
		 * @param nBufferSize The buffer size it uses
		 * */
		static void initialize(uint64_t nSampleRate, uint64_t nBufferSize, uint8_t nMidiChannelCount);
		static std::chrono::duration<double> getElapsedTime();
		static uint64_t getSampleRate();
		static uint64_t getBufferSize();
		static uint8_t getMidiChannelCount();
		static bool getVerbose();
		static bool setVerbose(bool vb);
		static bool getSilent();
		static bool setSilent(bool sl);
	private:
		static std::chrono::high_resolution_clock::time_point startTime;
		static uint64_t sampleRate;
		static uint64_t buffferSize;
		static uint8_t midiChannelCount;
		static bool verbose;
		static bool silent; // Silent takes priority over verbose
		static bool initialized; // Only allow initialized once
	};
} // namespace nodesynth

#endif // OPTIONS_H_INCLUDED
