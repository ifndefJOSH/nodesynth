/**
 * Class Definition for IntegerStream, a casing for certain types of pointers
 * 
 * Created by Josh Jeppson on 8/31/2021
 * */
#ifndef INTEGER_STREAM_H
#define INTEGER_STREAM_H

#include "DataStream.h"

namespace nodesynth {
    class IntegerStream : DataStream {
    public:
        IntegerStream(uint32_t bufSize);
        ~IntegerStream();
        int * buffer;
        void updateForward();
        void connect(IntegerStream * next);
        IntegerStream * disconnect();
        IntegerStream * getNext();
    protected:
        void allocate();
        void deallocate();
    private:
        IntegerStream * next;
    };
}

#endif // INTEGER_STREAM_H