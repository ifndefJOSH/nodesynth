#include "DataStream.h"

using namespace nodesynth;

DataStream::DataStream(uint32_t bufSize)
    : bufSize(bufSize)
    , allocated(true)
    , connected(false)
{
    // Intentionally left empty
}

streamtype
DataStream::getStreamType() {
    return type;
}

void
DataStream::setStreamType(streamtype type) {
    this->type = type;
}