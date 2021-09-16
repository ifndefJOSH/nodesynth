/**
 * Class Definition for MidiStream, a casing for certain types of pointers
 * 
 * Created by Josh Jeppson on 8/31/2021
 * 
 * TODO: Change MIDI stream to round robin
 * */
#ifndef MIDI_STREAM_H
#define MIDI_STREAM_H

#include "DataStream.h"

namespace nodesynth {
    struct MidiNote {
        uint8_t note;
        float velocity;
        float pan;
    };

    class MidiStream : DataStream {
    public:
        MidiStream(uint32_t bufSize);
        ~MidiStream();
        MidiNote * buffer;
        void updateForward();
        void connect(MidiStream * next);
        MidiStream * disconnect();
        MidiStream * getNext();
    protected:
        void allocate();
        void deallocate();
    private:
        MidiStream * next;
    };
}

#endif // MIDI_STREAM_H