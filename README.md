![Nodesynth Logo](nodesynthLogo.png)

# Nodesynth

Work in progress. This is a senior project which, when finished, will be a declarative, modular nodal synthesizer compatible (hopefully) with JACK (and maybe eventually VST3 and LV2 if I have time).

## Ways you'll be able to use Nodesynth

1. As an API (this will be the first thing finished)
  - This will be good for game developers who don't want to include tons of audio files, or people who want to write synthesizers.
3. By writing human-readable nodesynth patch files in a language that will be kind of similar to Verilog
4. As a GUI, similar to that in Bespokesynth (this will be the last thing I write)

## Building Nodesynth

**Nodesynth currently does not build**

Nodesynth uses `cmake` and `clang` to build. Simply use

```bash
mkdir build
cd build
cmake ..
make -j8
```
