/**
 * Class Definition for StereoAudioStream, a casing for certain types of pointers
 * 
 * Created by Josh Jeppson on 8/31/2021
 * */
#ifndef STEREO_AUDIO_STREAM_H
#define STEREO_AUDIO_STREAM_H

#include "DataStream.h"

namespace nodesynth {
    struct stereoSample {
        double left;
        double right;
    };

    class StereoAudioStream : DataStream {
    public:
        StereoAudioStream(uint32_t bufSize);
        ~StereoAudioStream();
        stereoSample * buffer;
        void updateForward();
        void connect(StereoAudioStream * next);
        StereoAudioStream * disconnect();
        StereoAudioStream * getNext();
    protected:
        void allocate();
        void deallocate();
    private:
        StereoAudioStream * next;
    };
}

#endif // STEREO_AUDIO_STREAM_H