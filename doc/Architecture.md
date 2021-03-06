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
	- `OnePoleFilter`: A simple single-pole filter. Can be lowpass, highpass or bandpass
	- `TwoPoleFilter`: A double-pole filter. Can be lowpass, highpass or bandpass
	- `IIRFilter`: Creates an infinite impulse response rectangular window filter
	- `FlangerFilter`: A filter that does flangering
	- `FormantFilter`: A filter that applies a vocal formant
3. `DataStream`: contains buffers for certain types of data
	- `AudioDataStream`: Stream for monaural audio in `double` floating point precision (in fourier domain)
	- `ChanneledAudioDataStream`: Stream for monaural audio, separated by MIDI channel.
	- `TimeDomainAudioStream`: Audio in the time domain
	- `MidiStream`: Stream for MIDI notes
	- `PrimitiveDataStream<Type>`: (templated) stream for primitive types
	3. 05. `DataStreamReader<Type=DataStream>`: Reads data stream. Used for input into nodes.
		- I think how it's going to work is that `DataStreamReader`s will request direct access to the datastream's buffers, and will be hosted by a node.
4. `NodeGraph`: Hashmap of all nodes by name.
5. `NodeSynth`: Main class instantiated.
6. `PresetParser`: Parses the preset file and adds nodes to graph

**Memory is exposed** between streams, so as much as OOP abstraction is *nice*, we're not doing it 100%

## Decided questions

- Datastreams are stored in nodes in a `std::map` by name. This allows, in the eventual declarative language, to have us connect nodes by port name. This is in stark contrast to my previous method (see my *messy* commit history) where it was a bunch of `void**` pointers to buffers of different types. Now, we use `std::shared_ptr<DataStream>` for memory management.

- Filters/Amplifiers/any parameter that isn't audio/etc. only update *once* per audio buffer change

## Undecided questions

- Since MIDI channels are going to be separate buffers, (`N` buffers for `N` input nodes), should there be an auto-cast to single-channel audio? Or should there be a "channel compress" node that takes MIDI-separated audio and compresses it to monaural audio?

- How should we deal with MIDI?
	+ First frame is a MIDI note, and second frame is velocity, with subsequent frames being duration the MIDI note has lasted, with `0` being no note?
		- **Advantages**:
			+ Makes the amplitude envelope (or envelope node in general) super easy to do.
			+ Oscillator node would only have to get the MIDI note from the first nonzero frame, and ignore all subsequent frames until a zero was detected (note off)
		- **Disadvantages**:
			+ Unnecessary holding of memory?
	+ Holds only current MIDI note and start time (MIDI note includes velocity)
		- **Advantages**:
			+ Less use of memory
			+ Quicker update times, less memory copying.
			+ More intuitive routing to filters.
		- **Disadvantages**:
			+ More calculations in amplitude envelope, but since the envelope only updates once per buffer change, we should be fine.
