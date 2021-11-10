#include "DataStream.h"

using namespace nodesynth;

DataStream::DataStream(const std::string name, streamtype type)
	: type(type)
	, name(name)
{
	// Intentionally left empty
}

void
DataStream::connect(const DataStream & ds) {
	if (ds.type == type) {
		next = ds;
	}
	else {
		// TODO: raise error
	}
}
