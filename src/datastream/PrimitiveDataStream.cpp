#include "PrimitiveDataStream.h"

using namespace nodesynth;

template <typename T>
PrimitiveDataStream<T>::PrimitiveDataStream(const std::string name)
	: DataStream(name)
{

}


template <typename T>
void
PrimitiveDataStream<T>::updateNext() {

}

template <typename T>
bool
PrimitiveDataStream<T>::wasUpdated() {
	return updated;
}

template <typename T>
T
PrimitiveDataStream<T>::getValueThisCycle() {
	return valueThisCycle;
}

template <typename T>
void
PrimitiveDataStream<T>::setValueThisCycle(T value) {
	valueThisCycle = value;
}

