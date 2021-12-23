#include "TwoPoleFilter.h"
#include "../core/cli/messages.h"

using namespace nodesynth;

TwoPoleFilter::TwoPoleFilter()
	: Filter()
{

}

void
TwoPoleFilter::createFilter() {
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
TwoPoleFilter::createLowpass() {

}

void
TwoPoleFilter::createHighpass() {

}

void
TwoPoleFilter::createBandpass() {

}

void
TwoPoleFilter::createBandreject() {

}

