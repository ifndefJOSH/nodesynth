#ifndef NODESYNTH_MESSAGE_H
#define NODESYNTH_MESSAGE_H

#include <string>

namespace nodesynth {
    void error(std::string msg);
    void warning(std::string msg);
    void message(std::string msg);
    void debug(std::string msg);
}


#endif // NODESYNTH_MESSAGE_H