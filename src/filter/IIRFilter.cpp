#include "IIRFilter.h"

#include "../core/cli/messages.h"
#include "../core/Options.h"

using namespace nodesynth;

IIRFilter::IIRFilter()
	: Filter()
{
	// Intentionally left empty
}


void
IIRFilter::createFilter() {
	switch (filterType) {
		case FilterTypes::LOWPASS:
			createLowpass();
			break;
		case FilterTypes::HIGHPASS:
			createHighpass();
			break;
		case FilterTypes::BANDPASS:
			createBandpass();
			break;
		case FilterTypes::BANDREJECT:
			createBandreject();
			break;
		default:
			errorExit("Filter type is not known!");
	}
}

void
IIRFilter::createLowpass() {
	uint64_t cutoffSample = Filter::frequencyToSampleLocation(cutoff1);
	uint64_t i = 0;
	for (; i < cutoffSample; i++) {
		filter[i] = 1;
	}
	for (; i < Options::getBufferSize(); i++) {
		filter[i] = 0;
	}
}

void
IIRFilter::createHighpass() {
	uint64_t cutoffSample = Filter::frequencyToSampleLocation(cutoff1);
	uint64_t i = 0;
	for (; i < cutoffSample; i++) {
		filter[i] = 0;
	}
	for (; i < Options::getBufferSize(); i++) {
		filter[i] = 1;
	}
}

void
IIRFilter::createBandpass() {
	uint64_t cutoffSample1 = Filter::frequencyToSampleLocation(cutoff1);
	uint64_t cutoffSample2 = Filter::frequencyToSampleLocation(cutoff2);
	uint64_t i = 0;
	for (; i < Options::getBufferSize(); i++) {
		if (i > cutoffSample1 && i < cutoffSample2) {
			filter[i] = 1;
		}
		else {
			filter[i] = 0;
		}
	}
}

void
IIRFilter::createBandreject() {
	uint64_t cutoffSample1 = Filter::frequencyToSampleLocation(cutoff1);
	uint64_t cutoffSample2 = Filter::frequencyToSampleLocation(cutoff2);
	uint64_t i = 0;
	for (; i < Options::getBufferSize(); i++) {
		if (i > cutoffSample1 && i < cutoffSample2) {
			filter[i] = 0;
		}
		else {
			filter[i] = 1;
		}
	}
}

