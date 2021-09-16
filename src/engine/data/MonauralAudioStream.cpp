#include "MonauralAudioStream.h"
#include "../../core/NodeSynthMessage.h"

#include <stdlib.h> // For memcpy

using namespace nodesynth;

MonauralAudioStream::MonauralAudioStream(uint32_t bufSize) 
    : DataStream(bufSize)
    , type(datatypes::FLOAT)
{
    allocate();
}

MonauralAudioStream::~MonauralAudioStream() {
    deallocate();
}

void
MonauralAudioStream::updateForward() {
    if (connected && allocated) {
        // Copy memory into connected stream
        memcpy(next->buffer, buffer, sizeof(float) * bufSize);
    }
    else if (allocated) {
        warning("Forward update failed as not connected!");
    }
    else {
        error("Not allocated!");
    }
}

void
MonauralAudioStream::connect(MonauralAudioStream * next) {
    this->next = next;
    connected = true;
}

MonauralAudioStream * 
MonauralAudioStream::disconnect() {
    this->next = nullptr;
    connected = false;
}

MonauralAudioStream * 
MonauralAudioStream::getNext() {
    return next;
}

void
MonauralAudioStream::allocate() {
    // Prevent memory leaks
    if (allocated) {
        deallocate();
    }
    buffer = new MonauralAudioStream[bufSize];
    allocated = true;
}

void
MonauralAudioStream::deallocate() {
    delete buffer;
    allocated = false;
}