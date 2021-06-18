#ifndef FILTER_HPP_
#define FILTER_HPP_

#include <fftw.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "lv2/core/lv2.h"

class Filter {
public:
	/**
	 * Creates an fftw plan and sets the buffer size
	 * 
	 * @param bufsize Buffer size. Select from available
	 * @return New `Filter()` object.
	 * */
	Filter(uint64_t bufsize) : outbuf(_outbuf) {
		this->plan = fftw_create_plan(bufsize, FFTW_FORWARD, FFTW_ESTIMATE);
		this->bufsize = bufsize;
		this->outbuf = new double(bufsize);
	}
	/*
	 * Destroys the `Filter()` object and cleans up memory leaks.
	 * */
	~Filter() {
		fftw_destroy_plan(this->plan);
		delete this->outbuf;
	}
	void setImpulseResponse(double * impulseResponse);
	
	uint64_t getBufferSize();
	void setBufferSize(uint64_t bufsize);
	
protected:
	
private:
	fftw_plan plan;
	double * _outbuf;
	double * _fftImpulseResponse;
	uint64_t _bufsize;
}


#endif /* #define FILTER_HPP_ */
