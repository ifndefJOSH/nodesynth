#include "PoleFilter.h"

#include "../core/cli/messages.h"

using namespace nodesynth;

PoleFilter::PoleFilter()
	: Filter()
	, numberPoles(1)
{

}

void
PoleFilter::setNumPoles(uint8_t numPoles) {
	numberPoles = numPoles;
}

uint8_t
PoleFilter::getNumPoles() {
	return numberPoles;
}

void
PoleFilter::createFilter() {
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
PoleFilter::createLowpass() {
	for (int p = 0; p < numberPoles; p++) {
		// TODO: Create lowpass filter using the Parks-McClellan filter design algorithm
	}
}

void
PoleFilter::createHighpass() {
	for (int p = 0; p < numberPoles; p++) {
		// TODO: Create highpass filter using the Parks-McClellan filter design algorithm
	}

}

void
PoleFilter::createBandpass() {
	for (int p = 0; p < numberPoles; p++) {

		// TODO: Create bandpass filter using the Parks-McClellan filter design algorithm
	}
}

void
PoleFilter::createBandreject() {
	for (int p = 0; p < numberPoles; p++) {

		// TODO: Create bandreject filter using the Parks-McClellan filter design algorithm
	}

}

