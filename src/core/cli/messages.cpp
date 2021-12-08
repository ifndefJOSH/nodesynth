#include "messages.h"
#include "ANSIColors.h"

#include "../Options.h"

#include <iostream>

using namespace nodesynth;

std::ostream& operator<<(std::ostream& os, const LogFile& logFile) {
	if (!logFile.hasLogFile()) {
		return os;
	}
	else {
		return os;
	}
}

void
good(std::string msg){
	// Return if we want to be silent
	if (Options::getSilent()) {
		return;
	}
	std::cerr << BOLD(FGRN("[MESSAGE (GOOD)]:"));
	std::cerr << '(' << BOLD("Elapsed Time:") << Options::getElapsedTime().count() << " s)" << std::endl;
	std::cerr << '\t' << msg << std::endl;
}

void
neutral(std::string msg){
	// Return if we want to be silent
	if (Options::getSilent()) {
		return;
	}
	std::cerr << BOLD(FMAG("[MESSAGE (NEUTRAL)]:"));
	std::cerr << '(' << BOLD("Elapsed Time:") << Options::getElapsedTime().count() << " s)" << std::endl;
	std::cerr << '\t' << msg << std::endl;
}

void
info(std::string msg){
	std::cerr << BOLD(FBLU("[INFO]:"));
	std::cerr << '(' << BOLD("Elapsed Time:") << Options::getElapsedTime().count() << " s)" << std::endl;
	std::cerr << '\t' << msg << std::endl;
}

void
warning(std::string msg){
	// Return if we want to be silent
	if (Options::getSilent()) {
		return;
	}
	std::cerr << BOLD(FYEL("[WARNING]:"));
	std::cerr << '(' << BOLD("Elapsed Time:") << Options::getElapsedTime().count() << " s)" << std::endl;
	std::cerr << '\t' << msg << std::endl;
}

void
error(std::string msg){
	// Return if we want to be silent
	if (Options::getSilent()) {
		return;
	}
	std::cerr << BOLD(FRED("[ERROR]:"));
	std::cerr << '(' << BOLD("Elapsed Time:") << Options::getElapsedTime().count() << " s)" << std::endl;
	std::cerr << '\t' << msg << std::endl;
}

void
errorExit(std::string msg, uint8_t exitCode){
	error(msg);
	if (!Options::getSilent()) {
		std::cerr << "This error appears to be unrecoverable. Exiting with code " << exitCode << std::endl;
	}
	std::exit(exitCode);
}
