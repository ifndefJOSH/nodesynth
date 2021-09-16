/**
 * Class Definition for FloatStream, a casing for certain types of pointers
 * 
 * Created by Josh Jeppson on 8/31/2021
 * */
#ifndef FLOAT_STREAM_H
#define FLOAT_STREAM_H

#include "DataStream.h"

namespace nodesynth {
    class FloatStream : DataStream {
    public:
        FloatStream(uint32_t bufSize);
        ~FloatStream();
        float * buffer;
        void updateForward();
        void connect(FloatStream * next);
        FloatStream * disconnect();
        FloatStream * getNext();
    protected:
        void allocate();
        void deallocate();
    private:
        FloatStream * next;
    };
}

#endif // FLOAT_STREAM_H