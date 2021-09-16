#include "MidiStream.h"
#include "../../core/NodeSynthMessage.h"

#include <stdlib.h> // For memcpy

using namespace nodesynth;

MidiStream::MidiStream(uint32_t bufSize) 
    : DataStream(bufSize)
    , type(datatypes::FLOAT)
{
    allocate();
}

MidiStream::~MidiStream() {
    deallocate();
}

void
MidiStream::updateForward() {
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
MidiStream::connect(MidiStream * next) {
    this->next = next;
    connected = true;
}

MidiStream * 
MidiStream::disconnect() {
    this->next = nullptr;
    connected = false;
}

MidiStream * 
MidiStream::getNext() {
    return next;
}

void
MidiStream::allocate() {
    // Prevent memory leaks
    if (allocated) {
        deallocate();
    }
    buffer = new MidiNote[bufSize];
    allocated = true;
}

void
MidiStream::deallocate() {
    delete buffer;
    allocated = false;
}