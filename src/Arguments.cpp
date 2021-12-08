#include "Arguments.h"

#include "core/Options.h"

using namespace nodesynth;

/* Program metadata */
const char *argp_program_version = "nodesynth 0.0.1 alpha";

/* Email address to send bugs to */
const char *argp_program_bug_address = "<joshua.jeppson@usu.edu>";

/* Program documentation */
static char doc[] = "Nodesynth -- a modular nodal musical synthesizer";

/* Argument description */
static char args_doc[] = "PATCHFILE";

/* Options understood */
static struct argp_option options[] = {
	{"verbose", 'v', 0, 0, "Write verbose output to stderr"}
	, {"quiet", 'q', 0, 0, "Don't produce any output"}
	, {"output", 'o', "FILE", 0, "Sends data to log file in addition to standard output and standard error"}
	, {"sample", 's', "uint64_t", 0, "Sampling rate"}
	, {"buffer", 'b', "uint64_t", 0, "Buffer size"}
	, {0}
};



static error_t
parse_opt(
	int key
	, char * arg
	, struct argp_state * state
) {
	/* Gets input from argp_parse */
	struct arguments * arguments = (struct arguments * ) state->input;

	switch (key) {
		case 'v':
			Options::setVerbose(true);
			break;
		case 'q':
			Options::setSilent(true);
			break;
		case 'o':
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}
