#include "AudioDataStream.h"

using namespace nodesynth;

AudioDataStream::AudioDataStream(const std::string name)
	: DataStream(name, streamtype::AUDIO)
{
	this->bufSize = Options::getBufferSize();
	this->audio = new fftw_complex[bufSize];
}

AudioDataStream::~AudioDataStream() {
	delete this->audio;
}
