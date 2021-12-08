#ifndef ARGUMENTS_H_INCLUDED
#define ARGUMENTS_H_INCLUDED

/**
 * This file is written in more the C style to be constistent with
 * argp's coding style
 * */

#include <argp.h>
#include <stdlib.h>


// Arguments are given to static `Options` Class

/* Parses only one argument */
static error_t
parse_opt(
	int key
	, char * arg
	, struct argp_state * state
);
#endif // ARGUMENTS_H_INCLUDED
