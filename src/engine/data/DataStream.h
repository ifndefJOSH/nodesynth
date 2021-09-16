/**
 * Class Definition for DataStream, a casing for certain types of pointers
 * 
 * Created by Josh Jeppson on 8/31/2021
 * */
#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <stdint.h>
/******************************************
 * Rationale for this:
 * 
 * I'm doing a templated base class with
 * forward-declared subclasses. This allows
 * there to be a declaration that is type-specific for each  
 * 
 *****************************************/
namespace nodesynth {
    /**
     * Enumeration for all datatypes we are going to use
     * 
     * AUDIO: Monaural audio
     * */
    enum datatypes {
        MONAURAL_AUDIO = 0
        , STEREO_AUDIO = 1
        , MIDI = 2
        , GAIN = 3
        , FLOAT = 4
        , INTEGER = 5
    };
    typedef uint8_t streamtype;

    class DataStream {
    public:
        DataStream(uint32_t bufSize);
        streamtype getStreamType();
        void setStreamType(streamtype type);
    protected:
        virtual void allocate() = 0;
        virtual void deallocate() = 0;
        static streamtype type;
        bool allocated;
        bool connected;
        uint32_t bufSize;
    };
}

#endif // DATASTREAM_H