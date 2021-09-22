# Nodesynth Language Syntax

Nodesynth language will be *kind of inspired by* verilog/prolog. Nodetypes are delcared as follows:

```
begin OscillatorNode
	type: sawtooth
end
```

Comment lines will start with a `#`, so with comments, we will have:

```
begin OscillatorNode
	# Use a sawtooth wave
	name: saw_osc
	type: sawtooth
end
```

`connect` will be a keyword, and the access operator will be `.` The syntax of `connect` will be `connect [Source] [Destination]`

`connect saw_osc.midi_in global.midi`
