cmake_minimum_required(VERSION 3.16)
project(nodesynth)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FFTW_MIN_VERSION "3.3.9")
find_package(FFTW3 ${FFTW_MIN_VERSION} REQUIRED)

set(SOURCE_FILES
	src/main.cpp
	src/Arguments.c
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
	AMModulatorNode.cpp
	AMModulatorNode.h
	ChorusNode.cpp
	ChorusNode.h
	CompressorNode.cpp
	CompressorNode.h
	EnvelopeNode.cpp
	EnvelopeNode.h
	EQNode.cpp
	EQNode.h
	FilterNode.cpp
	FilterNode.h
	FMModulatorNode.cpp
	FMModulatorNode.h
	FormantNode.cpp
	FormantNode.h
	LimiterNode.cpp
	LimiterNode.h
	ModulatorNode.cpp
	Node.cpp
	Node.h
	OscillatorNode.cpp
	OscillatorNode.h
	PanningNode.cpp
	PanningNode.h
	PrimitiveFilterNode.cpp
	PrimitiveFilterNode.h
	PrimitiveOscillatorNode.cpp
	PrimitiveOscillatorNode.h
	ResamplerNode.cpp
	ResamplerNode.h
	SamplerNode.cpp
	SamplerNode.h
	WavetableOscillatorNode.cpp
	WavetableOscillatorNode.h
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

# add_executable(xnodesynth ${SOURCE_FILES} ${NODE_FILES} ${FILTER_FILES} ${DATASTREAM_FILES} ${GUI_FILES})
