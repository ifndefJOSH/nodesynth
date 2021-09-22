#include "messages.h"
#include "ANSIColors.h"

#include <iostream>

using namespace nodesynth;

std::ostream& operator<<(std::ostream& os, const LogFile& logFile) {
	if (!logFile.hasLogFile()) {
		return os;
	}
}

void good(std::string msg){
	std::cerr << BOLD(FGRN("[MESSAGE]:")) << msg;
}
void neutral(std::string msg){

}
void info(std::string msg){

}
void warning(std::string msg){

}
void error(std::string msg){

}
void errorExit(std::string msg, uint8_t exitCode){

}
