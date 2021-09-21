cmake_minimum_required(VERSION 3.16)
project(nodesynth)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FFTW_MIN_VERSION "3.3.10")
find_package(fftw ${FFTW_MIN_VERSION} REQUIRED)

set(SOURCE_FILES
	src/main.cpp
)

set(NODE_FILES
	src/Node.h
	src/Node.cpp
)

set(FILTER_FILES
	filter/Filter.h
	filter/Filter.cpp
)

# To be added when GUI is done
#set(GUI_FILES
#	gui/MainWindow.h
#	gui/MainWindow.cpp
#)

add_executable(nodesynth ${SOURCE_FILES} ${NODE_FILES} ${FILTER_FILES})

# add_executable(xnodesynth ${SOURCE_FILES} ${NODE_FILES} ${FILTER_FILES} ${GUI_FILES})
