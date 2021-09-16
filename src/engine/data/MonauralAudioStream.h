/**
 * Class Definition for MonauralAudioStream, a casing for certain types of pointers
 * 
 * Created by Josh Jeppson on 8/31/2021
 * */
#ifndef MONAURAL_AUDIO_STREAM_H
#define MONAURAL_AUDIO_STREAM_H

#include "DataStream.h"

namespace nodesynth {
    class MonauralAudioStream : DataStream {
    public:
        MonauralAudioStream(uint32_t bufSize);
        ~MonauralAudioStream();
        double * buffer;
        void updateForward();
        void connect(MonauralAudioStream * next);
        MonauralAudioStream * disconnect();
        MonauralAudioStream * getNext();
    protected:
        void allocate();
        void deallocate();
    private:
        MonauralAudioStream * next;
    };
}

#endif // MONAURAL_AUDIO_STREAM_H