# Architecture of Nodesynth

## Classes and Descriptions:

1. `Node`: nodes which perform operations on data in buffers.
	- `OscillatorNode`: Node which creates sound, given MIDI Channels and a waveform
		- `PrimitiveOscillatorNode`: Contains code for primitive waveforms (Sine, Square, Saw, Triange, Noise)
		- `WavetableOscillatorNode`: Contains code for a user-defined wavetable with multiple frames
		- `SamplerNode`: Contains code for a sample to be played.
	- `FilterNode`: Node which contains a `Filter` object and performs filtering on a datastream
		- `EQNode`: Filter is user defined by certain band ranges
		- `PrimitiveFilterNode`: Contains high-pass, low-pass, band-pass, and other primitive filters
		- `FormantNode`: Contains vocal formant filters
	- `ModulatorNode`: Modulates two signals and produces an output
		- `FMModulatorNode`: Performs Frequency Modulation
			- This can also be used for vocoding
		- `AMModulatorNode`: Performs Amplitude Modulation
	- `EnvelopeNode`: Takes in MIDI data and outputs per-channel envelopes.
	- `PanningNode`: Takes a monaural input and transforms it multiplicitavely into stereo
	- `ChorusNode`: Takes in a monaural audio and adds a stereo chorus.
	- `ResamplerNode`: Resamples (and optionally lowpasses to below the Nyquist frequency) a signal
	- `CompressorNode`: "Compresses" audio with optional makeup gain.
	- `LimiterNode`: Limits audio to a certain Amplitude.
2. `Filter`: An object which filters, using `fftw`, an input stream with a filter shape, which is encased in its parent `Node`.
3. `DataStream`: contains buffers for certain types of data
	- `AudioDataStream`: Stream for monaural audio in `double` floating point precision
	- `ChanneledAudioDataStream`: Stream for monaural audio, separated by MIDI channel.
	- `MidiStream`: Stream for MIDI notes
	- `PrimitiveDataStream<Type>`: (templated) stream for primitive types
4. `NodeGraph`: Hashmap of all nodes by name.
5. `NodeSynth`: Main class instantiated.
6. `PresetParser`: Parses the preset file and adds nodes to graph

**Memory is exposed** between streams, so as much as OOP abstraction is *nice*, we're not doing it 100%

## Undecided questions

- Since MIDI channels are going to be separate buffers, (`N` buffers for `N` input nodes), should there be an auto-cast to single-channel audio? Or should there be a "channel compress" node that takes MIDI-separated audio and compresses it to monaural audio?
