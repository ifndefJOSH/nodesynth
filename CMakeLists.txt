cmake_minimum_required(VERSION 3.16)
project(nodesynth)

set(CMAKE_SOURCE_DIR src)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FFTW_MIN_VERSION "3.3.9")
find_package(FFTW3 ${FFTW_MIN_VERSION} REQUIRED)
include_directories(${FFTW_INCLUDES})

set(SOURCE_FILES
	src/main.cpp
	src/Arguments.cpp
	src/Arguments.h
	src/core/NodeGraph.cpp
	src/core/NodeGraph.h
	src/core/NodeSynth.cpp
	src/core/NodeSynth.h
	src/core/PresetParser.cpp
	src/core/PresetParser.h
	src/core/Options.cpp
	src/core/Options.h
	src/core/cli/messages.cpp
	src/core/cli/messages.h
	src/core/cli/ANSIColors.h
)

set(NODE_FILES
	src/node/AMModulatorNode.cpp
	src/node/AMModulatorNode.h
	src/node/ChorusNode.cpp
	src/node/ChorusNode.h
	src/node/CompressorNode.cpp
	src/node/CompressorNode.h
	src/node/EnvelopeNode.cpp
	src/node/EnvelopeNode.h
	src/node/EQNode.cpp
	src/node/EQNode.h
	src/node/FilterNode.cpp
	src/node/FilterNode.h
	src/node/FMModulatorNode.cpp
	src/node/FMModulatorNode.h
	src/node/FormantNode.cpp
	src/node/FormantNode.h
	src/node/LimiterNode.cpp
	src/node/LimiterNode.h
	src/node/ModulatorNode.cpp
	src/node/Node.cpp
	src/node/Node.h
	src/node/OscillatorNode.cpp
	src/node/OscillatorNode.h
	src/node/PanningNode.cpp
	src/node/PanningNode.h
	src/node/PrimitiveFilterNode.cpp
	src/node/PrimitiveFilterNode.h
	src/node/PrimitiveOscillatorNode.cpp
	src/node/PrimitiveOscillatorNode.h
	src/node/ResamplerNode.cpp
	src/node/ResamplerNode.h
	src/node/SamplerNode.cpp
	src/node/SamplerNode.h
	src/node/WavetableOscillatorNode.cpp
	src/node/WavetableOscillatorNode.h
)

set(FILTER_FILES
	src/filter/Filter.h
	src/filter/Filter.cpp
)

set(DATASTREAM_FILES
      src/datastream/AudioDataStream.cpp
      src/datastream/AudioDataStream.h
      src/datastream/ChanneledAudioDataStream.cpp
      src/datastream/ChanneledAudioDataStream.h
      src/datastream/DataStream.cpp
      src/datastream/DataStream.h
      src/datastream/MidiStream.cpp
      src/datastream/MidiStream.h
      src/datastream/PrimitiveDataStream.cpp
      src/datastream/PrimitiveDataStream.h
      src/datastream/TimeDomainAudioStream.cpp
      src/datastream/TimeDomainAudioStream.h
)

# To be added when GUI is done
#set(GUI_FILES
#	gui/MainWindow.h
#	gui/MainWindow.cpp
#)

add_executable(nodesynth ${SOURCE_FILES} ${NODE_FILES} ${FILTER_FILES} ${DATASTREAM_FILES})

target_link_libraries(${PROJECT_NAME} ${FFTW_LIBRARIES})

# add_executable(xnodesynth ${SOURCE_FILES} ${NODE_FILES} ${FILTER_FILES} ${DATASTREAM_FILES} ${GUI_FILES})
