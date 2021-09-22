#include "AudioDataStream.h"

using namespace nodesynth;

AudioDataStream::AudioDataStream(const std::string name)
	: DataStream(name, streamtype::AUDIO)
{

}
