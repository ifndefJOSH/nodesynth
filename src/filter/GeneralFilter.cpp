#include "GeneralFilter.h"

#include "../core/cli/messages.h"

using namespace nodesynth;

GeneralFilter::GeneralFilter()
	: Filter()
	, resonance(0.0)
{

}

void
GeneralFilter::setNumPoles(uint8_t numPoles) {
	numberPoles = numPoles;
}

uint8_t
GeneralFilter::getNumPoles() {
	return numberPoles;
}

void
GeneralFilter::createFilter() {
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
GeneralFilter::createLowpass() {

}

void
GeneralFilter::createHighpass() {

}

void
GeneralFilter::createBandpass() {

}

void
GeneralFilter::createBandreject() {

}

