#include "IntegerStream.h"
#include "../../core/NodeSynthMessage.h"

#include <stdlib.h> // For memcpy

using namespace nodesynth;

IntegerStream::IntegerStream(uint32_t bufSize) 
    : DataStream(bufSize)
    , type(datatypes::FLOAT)
{
    allocate();
}

IntegerStream::~IntegerStream() {
    deallocate();
}

void
IntegerStream::updateForward() {
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
IntegerStream::connect(IntegerStream * next) {
    this->next = next;
    connected = true;
}

IntegerStream * 
IntegerStream::disconnect() {
    this->next = nullptr;
    connected = false;
}

IntegerStream * 
IntegerStream::getNext() {
    return next;
}

void
IntegerStream::allocate() {
    // Prevent memory leaks
    if (allocated) {
        deallocate();
    }
    buffer = new int[bufSize];
    allocated = true;
}

void
IntegerStream::deallocate() {
    delete buffer;
    allocated = false;
}