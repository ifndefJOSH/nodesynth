#include "Filter.hpp"
/**
 * Sets up IO ports for filter node.
 * 
 * The filter node has 2 inputs and one outputs. The inputs are:
 * - The signal to be modified
 * - The filter to modify it with
 * */
void Filter::setUpIO() {
   this->numInputs = 2;
   this->numOutputs = 1;
   this->inputTypes = new uint8_t[2];
   inputTypes[0] = IOTypes::AUDIO;
   inputTypes[1] = IOTypes::AUDIO;
   this->outputBuffers = new (void *)[1];
   this->bufferTypes = new uint8_t[1];
   bufferTypes[0] = IOTypes::AUDIO;
}
/**
 * Updates the forward buffers
 * */
void Filter::updateBuffer() {
   for (int i = 0; i < this->_bufsize; i++) {
      // TODO: set output buffer as inputs[0][i] * inputs[1][i]
   }
}