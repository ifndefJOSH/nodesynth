#include "NodeSynthMessage.h"
#include "ANSIColors.h"

#include <iostream>

using namespace nodesynth;

void error(std::string msg) {
    std::cout << BOLD(FRED("[ERROR]: ")) << msg << std::endl; 
}

void warning(std::string msg) {
    std::cout << BOLD(FYEL("[WARNING]: ")) << msg << std::endl;
}

void message(std::string msg) {
    std::cout << BOLD(FGRN("[MESSAGE]: ")) << msg << std::endl;
}

void debug(std::string msg) {
#ifdef PRINT_DEBUG_STATEMENTS
    std::cout << BOLD(FMAG("[DEBUG]: ")) << msg << std::endl;
#endif // PRINT_DEBUG_STATEMENTS
}