cmake_minimum_required(VERSION 3.16)
project(nodesynth_fft_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
	fft_test.cpp
	fft_test.h
	# Test files
	../jtest/jtest.cpp
	../jtest/jtest.h
	# FFT files
	../../src/lib/fft.h
	../../src/lib/fft.c
)

add_executable(fft_test ${SOURCE_FILES})
