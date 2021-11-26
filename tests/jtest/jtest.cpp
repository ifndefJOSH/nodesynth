#include "jtest.h"

#include <stdint.h>
#include <iostream>

uint32_t passed_tests = 0;
uint32_t failed_tests = 0;

template <typename T>
void
assert_equal(T a, T b) {
	if (a == b) {
		std::cout << "[PASSED] Passed assert equal test " << a << " == " << b << std::endl;
		passed_tests++;
	}
	else {
		std::cout << "[FAILED] FAILED assert equal test " << a << " != " << b << std::endl;
		failed_tests++;
	}
}

template <typename T>
void
assert_not_null(T * a) {
	if (a) {
		std::cout << "[PASSED] Pointer is not null: " << a << std::endl;
		passed_tests++;
	}
	else {
		std::cout << "[FAILED] Pointer is null!" << std::endl;
		failed_tests++;
	}
}

template <typename T>
void
assert_null(T * a) {
	if (a) {
		std::cout << "[FAILED] Pointer is not null: " << a << std::endl;
		failed_tests++;
	}
	else {
		std::cout << "[PASSED] Pointer is null!" << std::endl;
		passed_tests++;
	}
}

template <typename T>
void
assert_gt(T a, T b) {
	if (a > b) {
		std::cout << "[PASSED] Passed assert greater than test " << a << " > " << b << std::endl;
		passed_tests++;
	}
	else {
		std::cout << "[FAILED] FAILED assert greater than test " << a << " !> " << b << std::endl;
		failed_tests++;
	}
}

template <typename T>
void
assert_gte(T a, T b) {
	if (a >= b) {
		std::cout << "[PASSED] Passed assert greater than or equal test " << a << " >= " << b << std::endl;
		passed_tests++;
	}
	else {
		std::cout << "[FAILED] FAILED assert greater than or equal test " << a << " !>= " << b << std::endl;
		failed_tests++;
	}
}

template <typename T>
void
assert_lt(T a, T b) {
	if (a < b) {
		std::cout << "[PASSED] Passed assert less than test " << a << " < " << b << std::endl;
		passed_tests++;
	}
	else {
		std::cout << "[FAILED] FAILED assert less than test " << a << " !< " << b << std::endl;
		failed_tests++;
	}

}

template <typename T>
void
assert_lte(T a, T b) {
	if (a <= b) {
		std::cout << "[PASSED] Passed assert less than or equal test " << a << " <= " << b << std::endl;
		passed_tests++;
	}
	else {
		std::cout << "[FAILED] FAILED assert less than or equal test " << a << " !<= " << b << std::endl;
		failed_tests++;
	}

}


