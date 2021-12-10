#include "TimeDomainAudioStream.h"
#include "../core/Options.h"

using namespace nodesynth;

TimeDomainAudioStream::TimeDomainAudioStream(std::string name)
	: DataStream(name)
{
	// Allocate time-domain audio
	audio = new std::complex<double>[Options::getBufferSize()];
}

TimeDomainAudioStream::~TimeDomainAudioStream() {
	if (audio) {
		delete audio;
	}
}
void
TimeDomainAudioStream::update() {

}
