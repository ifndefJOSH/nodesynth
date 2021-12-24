#include "../../../src/node/PrimitiveOscillatorNode.h"
#include "../../jtest/jtest.h"

void
testInstantiation() {
	try {
		PrimitiveOscillatorNode * p = new PrimitiveOscillatorNode("DUT");
		JTest<int>::assert_test_pass();
	}
	catch (std::exception e) {
		JTest<int>::assert_test_fail();
	}
	if (p) {
		delete p;
	}
}
