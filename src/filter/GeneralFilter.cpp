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
			info("Filter type is FilterTypes::LOWPASS");
			warning("This filter type \"FilterTypes::LOWPASS\" is not supported by GeneralFilter. Defaulting to 12 dB lowpass");
			// TODO: Create default filter
			break;
		case FilterTypes::HIGHPASS:
			info("Filter type is FilterTypes::HIGHPASS");
			warning("This filter type \"FilterTypes::HIGHPASS\" is not supported by GeneralFilter. Defaulting to 12 dB highpass");
			// TODO: Create default filter
			break;
		case FilterTypes::BANDPASS:
			info("Filter type is FilterTypes::BANDPASS");
		case FilterTypes::BANDREJECT:
			info("Filter type is FilterTypes::BANDREJECT");
			errorExit("The filter type given is not a GeneralFilterType, but is an (unsupported FilterType).");
			break;
		case GeneralFilterTypes::LOWPASS_12:
			info("Filter type is GeneralFilterTypes::LOWPASS_12");
			createLowpass(TWELVE_DB);
			break;
		case GeneralFilterTypes::LOWPASS_24:
			info("Filter type is GeneralFilterTypes::LOWPASS_24");
			createLowpass(TWENTYFOUR_DB);
			break;
		case GeneralFilterTypes::LOWPASS_48:
			info("Filter type is GeneralFilterTypes::LOWPASS_48");
			createLowpass(FOURTYEIGHT_DB);
			break;
		case GeneralFilterTypes::HIGHPASS_12:
			info("Filter type is GeneralFilterTypes::HIGHPASS_12");
			createHighpass(TWELVE_DB);
			break;
		case GeneralFilterTypes::HIGHPASS_24:
			info("Filter type is GeneralFilterTypes::HIGHPASS_24");
			createHighpass(TWENTYFOUR_DB);
			break;
		case GeneralFilterTypes::HIGHPASS_48:
			info("Filter type is GeneralFilterTypes::HIGHPASS_48");
			createHighpass(FOURTYEIGHT_DB);
			break;
		default:
			errorExit("Filter type is not known!");
	}
}

void
GeneralFilter::createLowpass(decay_speed_t decaySpeed) {
	if (decaySpeed == TWELVE_DB) {

	}
	else if (decaySpeed == TWENTYFOUR_DB) {

	}
	else if (decaySpeed == FOURTYEIGHT_DB) {

	}
	else {
		errorExit("Decay speed is not known!");
	}
}

void
GeneralFilter::createHighpass(decay_speed_t decaySpeed) {
	if (decaySpeed == TWELVE_DB) {

	}
	else if (decaySpeed == TWENTYFOUR_DB) {

	}
	else if (decaySpeed == FOURTYEIGHT_DB) {

	}
	else {
		errorExit("Decay speed is not known!");
	}
}

