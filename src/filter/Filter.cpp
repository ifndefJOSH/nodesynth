#include "Filter.h"
#include "../core/Options.h"

using namespace nodesynth;

Filter::Filter()
	: filter1(0.0)
	, filter2(0.0)
{
	this->filter = new double[Options::getBufferSize()];
	this->createFilter();
}

Filter::~Filter() {
	if (filter) {
		delete filter;
	}
}

void
Filter::applyFilter(AudioDataStream & source, AudioDataStream & dest) {
	for (uint64_t i = 0; i < Options::getBufferSize(); i++) {
		dest.audio[i] source.audio[i] * this->filter[i];
	}
}

filter_type_t
Filter::getFilterType() {
	return filterType;
}

void
Filter::setFilterType(filter_type_t type) {
	filterType = type;
}


uint64_t
Filter::frequencyToSampleLocation(double frequency) {
	uint64_t sampleRate = Options::getSampleRate();
	uint64_t bufferSize = Options::getBufferSize();
	/*
	 * According to the Nyquist-Shannon sampling theorem, the buffer in frequency domain contains
	 * 0Hz to sampleRate / 2 Hz. Therefore, each buffer has a bandwidth of (sampleRate / 2) / bufferSize
	 * Hz, and the buffer we are looking for is (int) frequency / bandwidthPerBuffer
	 */
	double bandwidthPerBuffer = ((double) sampleRate / 2.0) / (double) bufferSize;
	return (uint64_t) frequency / bandwidthPerBuffer;
}

