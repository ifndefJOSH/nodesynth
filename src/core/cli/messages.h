#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED

#include <string> 	// For all functions
#include <cstdint> 	// For uint8_t
#include <fstream> 	// For log file
#include <iostream>	// For log file operator overloading
#include <memory>	// For std::shared_ptr

namespace nodesynth {
	/**
	 * Function name: good
	 *
	 * Prints a positive message in green to std::cerr, and to log if specified.
	 *
	 * @param msg The message to print
	 * */
	void good(std::string msg);
	/**
	 * Function name: neutral
	 *
	 * Prints a neutral message in purple to std::cerr, and to log if specified.
	 *
	 * @param msg The message to print
	 * */
	void neutral(std::string msg);
	/**
	 * Function name: info
	 *
	 * Prints an informative message in blue to std::cerr, and to log if specified.
	 *
	 * @param msg The message to print
	 * */
	void info(std::string msg);
	/**
	 * Function name: warning
	 *
	 * Prints a warning message in yellow to std::cerr, and to log if specified.
	 *
	 * @param msg The message to print
	 * */
	void warning(std::string msg);
	/**
	 * Function name: error
	 *
	 * Prints an error message in red to std::cerr, and to log if specified.
	 *
	 * @param msg The message to print
	 * */
	void error(std::string msg);
	/**
	 * Function name: errorExit
	 *
	 * Prints an error message in red to std::cerr, and to log if specified.
	 * Then, exits using a specified exit code.
	 *
	 * @param msg The message to print
	 * @param exitCode The exit code to exit with
	 * */
	void errorExit(std::string msg, uint8_t exitCode = 1);
	/**
	 * Function name: debug
	 *
	 * Prints a debug message in purple to std::cerr, and to log if specified.
	 * Only prints if debug statement printing is on (PRINT_DEBUG_STATEMENTS
	 * directive in preprocessor)
	 *
	 * @param msg Message to print.
	 * */
	void debug(std::string msg);

	class LogFile {
	public:
		LogFile();
		~LogFile();
		void initializeLog(std::string filename);
		const bool hasLogFile();
		std::shared_ptr<std::ofstream> getLogFile();
	private:
		std::shared_ptr<std::ofstream> logFile;
	};

} // namespace nodesynth

#endif // MESSAGES_H_INCLUDED
