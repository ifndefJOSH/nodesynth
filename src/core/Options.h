#ifndef OPTIONS_H
#define OPTIONS_H

namespace nodesynth {
    class Options {
    public:
        static void setNumMIDIChannels(uint8_t numMIDIChannels);
    protected:

    private:
        static uint8_t MIDIChannels;
    };
}

#endif // OPTIONS_H
