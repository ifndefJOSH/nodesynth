#include "Arguments.h"

#include "core/Options.h"

using namespace nodesynth;

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
