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
		/**
		 * Returns the elapsed time since initialization
		 *
		 * @return Elapsed time since initialize() was called (ideally at program start
		 * */
		static std::chrono::duration<double> getElapsedTime();
		/**
		 * Gets the sampling rate that we are operating at.
		 *
		 * @return The sampling rate of our JACK host or DAW.
		 * */
		static uint64_t getSampleRate();
		/**
		 * Gets the buffer size (N) that we're using in our datastreams. In reality 2N
		 * buffer size is allocated since we're using triangular windowing.
		 *
		 * @return Our buffer size.
		 * */
		static uint64_t getBufferSize();
		/**
		 * Gets the number of MIDI channels we are using. Our eviction scheme for MIDI
		 * channels is always LRU (least recently used).
		 *
		 * @return Number of MIDI channels used.
		 * */
		static uint8_t getMidiChannelCount();
		/**
		 * Gets whether or not we are printing verbose error and info messages.
		 * Note that silent takes precedence over verbose.
		 *
		 * @return Whether verbose error messages printed.
		 * */
		static bool getVerbose();
		/**
		 * Sets whether or not to use verbose error and info messages. Note that
		 * silent takes precedence over verbose.
		 *
		 * @param vb Whether or not to be verbose.
		 * */
		static void setVerbose(bool vb);
		/**
		 * Gets wheter or not we are not to print *any* messages. Note that this
		 * takes precedence over verbose.
		 *
		 * @return Whether we do NOT print any messages.
		 * */
		static bool getSilent();
		/**
		 * Sets whether or not we are going to be completely silent with info and
		 * error messages. Note that this takes precedence over verbose.
		 *
		 * @param sl Whether or not this should be silent.
		 * */
		static void setSilent(bool sl);
		/**
		 * Checks the validity of all of the options that we have.
		 * */
		static void checkAllOptions();

		static const uint8_t MAX_MIDI_CHANNELS = 32;
	private:
		static std::chrono::high_resolution_clock::time_point startTime;
		static uint64_t sampleRate;
		static uint64_t bufferSize;
		static uint8_t midiChannelCount;
		static bool verbose;
		static bool silent; // Silent takes priority over verbose
		static bool initialized; // Only allow initialized once
	};
} // namespace nodesynth

#endif // OPTIONS_H_INCLUDED
