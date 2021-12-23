#include "OnePoleFilter.h"

#include "../core/cli/messages.h"

using namespace nodesynth;

OnePoleFilter::OnePoleFilter()
	: Filter()
{

}

void
OnePoleFilter::createFilter() {
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
OnePoleFilter::createLowpass() {

}

void
OnePoleFilter::createHighpass() {

}

void
OnePoleFilter::createBandpass() {

}

void
OnePoleFilter::createBandreject() {

}

