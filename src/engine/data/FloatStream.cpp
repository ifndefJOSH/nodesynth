#include "FloatStream.h"
#include "../../core/NodeSynthMessage.h"

#include <stdlib.h> // For memcpy

using namespace nodesynth;

FloatStream::FloatStream(uint32_t bufSize) 
    : DataStream(bufSize)
    , type(datatypes::FLOAT)
{
    allocate();
}

FloatStream::~FloatStream() {
    deallocate();
}

void
FloatStream::updateForward() {
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
FloatStream::connect(FloatStream * next) {
    this->next = next;
    connected = true;
}

FloatStream * 
FloatStream::disconnect() {
    this->next = nullptr;
    connected = false;
}

FloatStream * 
FloatStream::getNext() {
    return next;
}

void
FloatStream::allocate() {
    // Prevent memory leaks
    if (allocated) {
        deallocate();
    }
    buffer = new float[bufSize];
    allocated = true;
}

void
FloatStream::deallocate() {
    delete buffer;
    allocated = false;
}